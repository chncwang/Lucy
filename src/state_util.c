#include <assert.h>
#include <string.h>
#include "state_util.h"


static lucy_Type GetType(lua_State *state, int index)
{
    if (lua_isnumber(state, index)) {
        return lucy_TypeNum;
    } else if (lua_isstring(state, index)) {
        return lucy_TypeStr;
    } else if (lua_isboolean(state, index)) {
        return lucy_TypeBool;
    } else if (lua_isfunction(state, index)) {
        return lucy_TypeFunc;
    } else if (lua_istable(state, index)) {
        return lucy_TypeTbl;
    } else if (lua_isnil(state, index)) {
        return lucy_TypeNil;
    } else {
        DASSERT(false);
        return index;
    }
}


static lucy_Data GetNum(lua_State *state, int index)
{
    lucy_Data data = {lucy_TypeNum};
    data.cntnt_.num_ = lua_tonumber(state, index);
    return data;
}


static lucy_Data GetStr(lua_State *state, int index)
{
    lucy_Data data = {lucy_TypeStr};
    data.cntnt_.str_ = lua_tostring(state, index);
    return data;
}


static lucy_Data GetBool(lua_State *state, int index)
{
    lucy_Data data = {lucy_TypeBool};
    data.cntnt_.boolean_ = lua_toboolean(state, index);
    return data;
}


static lucy_Data GetRef(lua_State *state, int index)
{
    lucy_Data data = {GetType(state, index)};
    lucy_Ref *ref = &(data.cntnt_.ref_);
    ref->state_ = state;
    ref->index_ = lua_gettop(state);
    return data;
}


static lucy_Data GetNil(lua_State *state, int index)
{
    lucy_Data data = {lucy_TypeNil};
    return data;
}


lucy_Data GetLuaDataOnStack(lua_State *state, int index)
{
    static lucy_Data (*GetData[lucy_TypesCount])(lua_State *, int) = {
        &GetNum,
        &GetStr,
        &GetBool,
        &GetRef,
        &GetRef,
        &GetNil
    };

    lucy_Type type = GetType(state, index);
    lucy_Data r = GetData[type](state, index);
    return r;
}


bool PopTop(lua_State *state, const lucy_Data *data)
{
    if (lucy_ShoudLeaveOnStack(*data)) {
        return false;
    } else {
        lua_pop(state, 1);
        return true;
    }
}
