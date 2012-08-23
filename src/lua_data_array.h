#ifndef LUA_DATA_ARRAY_H_
#define LUA_DATA_ARRAY_H_

#include <stddef.h>
#include "defs.h"
#include "lua_data.h"

#define MAX_LUADATA_ARRAY_LEN (10)


typedef struct {
    size_t len_;
    lucy_Data datas_[MAX_LUADATA_ARRAY_LEN];
} lucy_List;


lucy_List lucy_GetList(size_t len, ...);

#ifdef LUCY_DEBUG

void lucy_PrintList(const lucy_List *arr);
void lucy_LuaDataArray_TEST();

#endif

#endif
