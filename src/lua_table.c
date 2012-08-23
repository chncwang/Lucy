#include <assert.h>
#include "lua_table.h"
#include "state_util.h"


lucy_Data lucy_TblData(const lucy_Data *tbl, const char *key)
{
    DASSERT(tbl->type_ == lucy_TypeTbl);
    lua_State *state = lucy_GetState(*tbl);
    lua_getfield(state, lucy_GetIndex(*tbl), key);
    lucy_Data v = GetLuaDataOnStack(state, -1);
    PopTop(state, &v);
    return v;
}


lucy_Data lucy_ArrData(const lucy_Data *tbl, int index)
{
    DASSERT(tbl->type_ == lucy_TypeTbl);
    lua_State *state = lucy_GetState(*tbl);
    lua_pushinteger(state, index);
    lua_gettable(state, lucy_GetIndex(*tbl));
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
    lucy_Data Hello = lucy_GetData(&file, "Hello");
    lucy_Data ne = lucy_TblData(&Hello, "new");
    lucy_List args = lucy_GetList(1, &Hello);
    lucy_Data hello = (lucy_CallWithList(&ne, 1, &args)).datas_[0];
    lucy_Data sayhello = lucy_TblData(&hello, "sayhello");
    lucy_List args2 = lucy_GetList(1, &hello);
    lucy_Data str = (lucy_CallWithList(&sayhello, 1, &args2)).datas_[0];
    lucy_PrintData(&str);
    lucy_Data arr = lucy_GetData(&file, "arr");
    lucy_Data two = lucy_ArrData(&arr, 2);
    lucy_PrintData(&two);
    int len = lucy_ArrLen(&arr);
    DPRINT("len = %d", len);
    lucy_CloseFile(&file);
}

#endif
