#include <stdlib.h>
#include <assert.h>
#include "lua_file.h"
#include "state_util.h"


lucy_File lucy_CreateFile()
{
    lucy_File r;
    r.state_ = luaL_newstate();
    luaL_openlibs(r.state_);
    return r;
}


void lucy_OpenFile(const lucy_File *lua_file, const char *name)
{
    if (luaL_loadfile(lua_file->state_, name)) {
        DPRINT("%s", lua_tostring(lua_file->state_, -1));
        DASSERT(false);
    }
}


void lucy_Run(const lucy_File *file)
{
    if (lua_pcall(file->state_, 0, 0, 0)) {
        DPRINT("%s", lua_tostring(file->state_, -1));
        DASSERT(false);
    }
}


void lucy_CloseFile(const lucy_File *lua_file)
{
    lua_close(lua_file->state_);
}


lucy_Data lucy_GetData(const lucy_File *lua_file,
                             const char *name)
{
    lua_State *state = lua_file->state_;
    lua_getglobal(state, name);
    lucy_Data r = GetLuaDataOnStack(state, -1);
    PopTop(state, &r);
    return r;
}


void lucy_SetData(const lucy_File *lua_file, const char *name,
                  const lucy_Data *data)
{
    lua_State *state = lua_file->state_;
    PushData(state, data);
    lua_setglobal(state, name);
}


#ifdef LUCY_DEBUG

#include "lua_value.h"

void lucy_LuaFile_TEST()
{
    lucy_File lua_file = lucy_CreateFile();
    lucy_OpenFile(&lua_file, "/Users/wangqiansheng/Code/a.lua");
    lucy_Data sum = lucy_GetData(&lua_file, "sum");
    lucy_Data five = lucy_Num(5);
    lucy_SetData(&lua_file, "sum", &five);
    sum = lucy_GetData(&lua_file, "sum");
    lucy_PrintData(&sum);
}

#endif
