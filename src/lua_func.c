#include <assert.h>
#include <stdarg.h>
#include "lua_func.h"
#include "state_util.h"
#include "lua_value.h"


static void PushNum(lua_State *state, const lucy_Data *luadata)
{
    DASSERT(luadata->type_ == lucy_TypeNum);
    lua_pushnumber(state, luadata->cntnt_.num_);
}


static void PushStr(lua_State *state, const lucy_Data *luadata)
{
    DASSERT(luadata->type_ == lucy_TypeStr);
    lua_pushstring(state, luadata->cntnt_.str_);
}


static void PushBool(lua_State *state, const lucy_Data *luadata)
{
    DASSERT(luadata->type_ == lucy_TypeBool);
    lua_pushboolean(state, luadata->cntnt_.boolean_);
}


static void PushRef(lua_State *state, const lucy_Data *luadata)
{
    DASSERT(luadata->type_ == lucy_TypeFunc ||
            luadata->type_ == lucy_TypeTbl);
    lua_pushvalue(state, lucy_GetIndex(*luadata));
}


static void PushNil(lua_State *state, const lucy_Data *luadata)
{
    DASSERT(luadata->type_ == lucy_TypeNil);
    lua_pushnil(state);
}


lucy_List lucy_CallWithList(const lucy_Data *func, int rc,
                            const lucy_List *args)
{
    DASSERT(func->type_ == lucy_TypeFunc);
    lua_State *state = lucy_GetState(*func);
    lua_pushvalue(state, lucy_GetIndex(*func));

    static void
    (*PushData[lucy_TypesCount])(lua_State *, const lucy_Data *) = {
        &PushNum,
        &PushStr,
        &PushBool,
        &PushRef,
        &PushRef,
        &PushNil
    };

    int i;
    size_t args_c = args->len_;
    for (i=0; i<args_c; ++i) {
        const lucy_Data *dp = args->datas_ + i;
        PushData[dp->type_](state, dp);
    }

    if (lua_pcall(state, args_c, rc, 0) != 0) {
        DPRINT("%s", lua_tostring(state, -1));
        DASSERT(false);
    }
    lucy_List r = {rc};

    for (i=0; i<rc; ++i) {
        int index = i - rc;
        r.datas_[i] = GetLuaDataOnStack(state, index);
    }

    int index = lua_gettop(state);
    for (i=rc-1; i>=0; --i) {
        lucy_Data *dp = r.datas_ + i;
        *dp = GetLuaDataOnStack(state, index--);
        PopTop(state, dp);
    }

    return r;
}


lucy_List lucy_Call(const lucy_Data *func, int rc, int argsc, ...)
{
    DASSERT(func->type_ == lucy_TypeFunc);
    lucy_List list = {argsc};
    va_list arg;
    va_start(arg, argsc);
    int i;
    for (i=0; i<argsc; ++i) {
        list.datas_[i] = *(va_arg(arg, lucy_Data *));
    }
    va_end(arg);
    
    return lucy_CallWithList(func, rc, &list);
}


#ifdef LUCY_DEBUG

#include "lua_file.h"

void lucy_LuaFunc_TEST()
{
    lucy_File file = lucy_CreateFile();
    lucy_OpenFile(&file, "/Users/wangqiansheng/Code/a.lua");
    lucy_Data sum = lucy_GetData(&file, "sum");
    lucy_Data five = lucy_Num(5);
    lucy_List list = lucy_Call(&sum, 1, 2, &five, &five);
    lucy_PrintList(&list);
}

#endif
