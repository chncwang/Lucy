#include <assert.h>
#include <stdarg.h>
#include "lua_func.h"
#include "state_util.h"
#include "lua_value.h"
#include "lua_file.h"


lucy_List lucy_CallWithList(const lucy_Data *func, int rc,
                            const lucy_List *args)
{
    DASSERT(func->type_ == lucy_TypeFunc);
    lua_State *state = lucy_GetState(*func);
    lua_pushvalue(state, lucy_GetIndex(*func));

    int i;
    size_t args_c = args->len_;
    for (i=0; i<args_c; ++i) {
        const lucy_Data *dp = args->datas_ + i;
        PushData(lucy_GetState(*func), dp);
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


void lucy_CallCFunc(lua_State *state, lucy_CFuncWithList cfunc, int rc, int ac)
{
    int top = lua_gettop(state);
    lucy_List args = lucy_GetList(0);

    int i;
    DASSERT(MAX_LUADATA_ARRAY_LEN >= ac);
    for (i=0; i<ac; ++i) {
        int index = top - i;
        lucy_Data arg = GetLuaDataOnStack(state, index);
        args.datas_[ac - 1 - i] = arg;
        PopTop(state, &arg);
    }

    lucy_List results = cfunc(&args);

    for (i=0; i<results.len_; ++i) {
        PushData(state, &results.datas_[i]);
    }
}


#ifdef LUCY_DEBUG

#include "lua_file.h"

void lucy_LuaFunc_TEST()
{
    lucy_File file = lucy_CreateFile();
    lucy_OpenFile(&file, "/Users/wangqiansheng/Code/a.lua");
    lucy_Run(&file);
    lucy_Data ab = lucy_GetData(&file, "ab");
    lucy_List r = lucy_Call(&ab, 2, 0);
    DPRINT("%lf, %lf", r.datas_[0].cntnt_.num_, r.datas_[1].cntnt_.num_);
}

#endif
