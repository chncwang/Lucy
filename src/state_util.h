#ifndef STATE_UTIL_H_
#define STATE_UTIL_H_

#include "defs.h"
#include "lua_headers.h"
#include "lua_data.h"

lucy_Data GetLuaDataOnStack(lua_State *state, int index);
bool PopTop(lua_State *state, const lucy_Data *data);

#endif
