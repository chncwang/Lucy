#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include "lua_data_array.h"


lucy_List lucy_GetList(size_t len, ...)
{
    DASSERT(len <= MAX_LUADATA_ARRAY_LEN);
    lucy_List r;
    r.len_ = len;

    va_list arg;
    va_start(arg, len);
    int i;
    for (i=0; i<len; ++i) {
        r.datas_[i] = *(va_arg(arg, lucy_Data *));
    }
    va_end(arg);

    return r;
}


#ifdef LUCY_DEBUG

#include "lua_file.h"


void lucy_PrintList(const lucy_List *arr)
{
    DPRINT("len = %lu", arr->len_);
    int i;
    for (i=0; i<arr->len_; ++i) {
        lucy_PrintData(&(arr->datas_[i]));
    }
}


void lucy_LuaDataArray_TEST()
{
    lucy_File lua_file = lucy_CreateFile();
    lucy_OpenFile(&lua_file, "/Users/wangqiansheng/Code/a.lua");
    lucy_Data data = lucy_GetData(&lua_file, "num");
    lucy_Data str = lucy_GetData(&lua_file, "str");
    lucy_Data boolean = lucy_GetData(&lua_file, "bool");
    lucy_Data table = lucy_GetData(&lua_file, "table");
    lucy_Data sum = lucy_GetData(&lua_file, "sum");
    lucy_List array = lucy_GetList(5, data, str, boolean,
                                                      table,
                                                      sum);
    lucy_PrintList(&array);
    lucy_CloseFile(&lua_file);
}


#endif
