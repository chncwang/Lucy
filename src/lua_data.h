#ifndef LUA_DATA_H
#define LUA_DATA_H

#include <stdbool.h>
#include "defs.h"
#include "lua_headers.h"


typedef enum {
    lucy_TypeNum = 0,
    lucy_TypeStr = 1,
    lucy_TypeBool = 2,
    lucy_TypeFunc = 3,
    lucy_TypeTbl = 4,
    lucy_TypeNil = 5
} lucy_Type;

#define lucy_TypesCount (6)


/* *****************************************************************************
 * description          : reference type in lua, which means function and table.
 * state_ [lua_State *] : weak pointer of the lua state.
 * index_ [int]         : the LuaRef value's index on the lua state.
 * ****************************************************************************/
typedef struct {
    lua_State *state_;
    int index_;
} lucy_Ref;


typedef union {
    double num_;
    const char* str_;
    bool boolean_;
    lucy_Ref ref_;
} lucy_Content;


/* *****************************************************************************
 * description                  : present data in lua program.
 * type_ [lucy_LuaDataType]     : type of data.
 * cntnt_ [lucy_LuaDataContent] : content of data.
 * ****************************************************************************/
typedef struct {
    lucy_Type type_;
    lucy_Content cntnt_;
} lucy_Data;


#define lucy_GetIndex(data) ((data).cntnt_.ref_.index_)
#define lucy_GetState(data) ((data).cntnt_.ref_.state_)

#define lucy_ShoudLeaveOnStack(data) \
    (((data).type_ == lucy_TypeStr || (data).type_ == lucy_TypeFunc || \
            (data).type_ == lucy_TypeTbl) ? true : false)

#ifdef LUCY_DEBUG

void lucy_PrintData(const lucy_Data *luadata); /* for test. */

#endif

#endif
