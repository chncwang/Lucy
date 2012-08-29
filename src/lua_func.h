#ifndef LUA_FUNC_H_
#define LUA_FUNC_H_

#include "defs.h"
#include "lua_data_array.h"

/* ****************************************************************************
 * description                  : call the lua function with lucy_List value.
 * func [lucy_LuaData *]        : the lua function.
 * rc [int]                     : the count of return values.
 * args [lucy_LuaDataArray *]   : the arguments of the lua function.
 * return [lucy_LuaDataArray *] : like the lua function resturn.
 * ****************************************************************************/
lucy_List lucy_CallWithList(const lucy_Data *func, int rc,
                            const lucy_List *args);

/* *****************************************************************************
 * description           : call the lua function with arguments directly.
 * func [lucy_LuaData *] : the lua function.
 * rc [int]              : the count of return values.
 * argsc [int]           : the count of arguments.
 * ... [lucy_Data *]     : arguments.
 * ****************************************************************************/
lucy_List lucy_Call(const lucy_Data *func, int rc, int argsc, ...);

typedef lucy_List (*lucy_CFuncWithList)(const lucy_List *args);

void lucy_CallCFunc(lua_State *state, lucy_CFuncWithList cfunc, int ac);

#define LUA_CFUNCTION_NAME(name) lucy_LuaCFunction##name

#define lucy_GenLuaCFunction(cfunc, rc, ac) \
static int LUA_CFUNCTION_NAME(cfunc)(lua_State *state) \
{\
    lucy_CallCFunc(state, cfunc, ac);\
    return rc;\
}


#define lucy_SetCFunc(file, name, cfunc) \
    lua_pushcfunction((file)->state_, LUA_CFUNCTION_NAME(cfunc));\
    lua_setglobal((file)->state_, name)


#ifdef LUCY_DEBUG

void lucy_LuaFunc_TEST(); /* for test. */
void lucy_CFunc_TEST();

#endif

#endif
