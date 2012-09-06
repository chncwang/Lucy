#include <assert.h>
#include "lua_table.h"
#include "state_util.h"
#include "lua_func.h"


lucy_Data lucy_TblData(const lucy_Data *tbl, const char *key)
{
    DASSERT(tbl->type_ == lucy_TypeTbl);
    lua_State *state = lucy_GetState(*tbl);
    lua_rawgeti(state, LUA_REGISTRYINDEX, lucy_GetIndex(*tbl));
    lua_getfield(state, -1, key);
    lucy_Data v = GetLuaDataOnStack(state, -1);
    PopTop(state, &v);
    return v;
}


lucy_Data lucy_ArrData(const lucy_Data *tbl, int index)
{
    DASSERT(tbl->type_ == lucy_TypeTbl);
    lua_State *state = lucy_GetState(*tbl);
    lua_rawgeti(state, LUA_REGISTRYINDEX, lucy_GetIndex(*tbl));
    lua_pushinteger(state, index);
    lua_gettable(state, -2);
    lucy_Data v = GetLuaDataOnStack(state, -1);
    PopTop(state, &v);
    return v;
}


int lucy_ArrLen(const lucy_Data *tbl)
{
    DASSERT(tbl->type_ == lucy_TypeTbl);
    for (int i=1; ; ++i) {
        lucy_Data v = lucy_ArrData(tbl, i);
        if (v.type_ == lucy_TypeNil) {
            return i - 1;
        }
    }
    return -1;
}


lucy_Data lucy_TblDataF(const lucy_Data *tbl, const char *key, ...)
{
    DASSERT(tbl->type_ == lucy_TypeTbl);
    lucy_Data t = lucy_TblData(tbl, key);

    va_list arg;
    va_start(arg, key);
    while (true) {
        const char *next = va_arg(arg, const char*);
        if (next == NULL) {
            break;
        } else {
            lucy_Data data = lucy_TblData(&t, next);
            t = data;
        }
    }

    return t;
}


lucy_List lucy_TblCall(const lucy_Data *tbl, const char *fname, int rc,
                       int argsc,
                       ...)
{
    lucy_Data func = lucy_TblData(tbl, fname);
    
    va_list arg;
    va_start(arg, argsc);
    return lucy_VCall(func, rc, argsc, arg);
}


#ifdef LUCY_DEBUG

#include "lua_file.h"
#include "lua_func.h"

void lucy_Table_TEST()
{
    lucy_File file = lucy_CreateFile();
    lucy_OpenFile(&file, "/Users/wangqiansheng/Code/b.lua");
    lucy_Run(&file);
    lucy_Data a = lucy_GetData(&file, "a");
    DPRINT("got a");
    lucy_Data d = lucy_TblDataF(&a, "b", "c", "d", NULL);
    lucy_PrintData(&d);
}

#endif
