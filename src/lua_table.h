#ifndef LUA_TABLE_H_
#define LUA_TABLE_H_

#include "defs.h"
#include "lua_data.h"
#include "lua_data_array.h"
#include <stdarg.h>

lucy_Data lucy_TblData(const lucy_Data *tbl, const char *key);
lucy_Data lucy_ArrData(const lucy_Data *tbl, int index);
int lucy_ArrLen(const lucy_Data *tbl);
lucy_Data lucy_TblDataF(const lucy_Data *tbl, const char *key, ...);
lucy_List lucy_TblCall(const lucy_Data *tbl, const char *fname, int rc,
                       int argsc,
                       ...);

#ifdef LUCY_DEBUG

void lucy_Table_TEST();

#endif

#endif
