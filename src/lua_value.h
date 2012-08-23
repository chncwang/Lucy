#ifndef LUA_VALUE_H_
#define LUA_VALUE_H_

#include "defs.h"
#include "lua_data.h"

lucy_Data lucy_Num(double num);

/* *****************************************************************************
 * description           : shallow copy the incoming c string.
 * str [char *]          : incoming c string.
 * return [lucy_LuaData] : lua data.
 * ****************************************************************************/
lucy_Data lucy_Str(const char *str);

lucy_Data lucy_Bool(bool boolean);
lucy_Data lucy_Nil();

#endif
