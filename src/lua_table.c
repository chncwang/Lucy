#include <assert.h>
#include "lua_table.h"
#include "state_util.h"


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


#ifdef LUCY_DEBUG

#include "lua_file.h"
#include "lua_func.h"

void lucy_Table_TEST()
{
    lucy_File file = lucy_CreateFile();
    lucy_OpenFile(&file, "/Users/wangqiansheng/Code/a.lua");
    lucy_Run(&file);
    lucy_Data arr = lucy_GetData(&file, "arr");
    int n = lucy_ArrData(&arr, 3).cntnt_.num_;
    int len = lucy_ArrLen(&arr);
    DPRINT("%d, %d", n, len);
}

#endif
