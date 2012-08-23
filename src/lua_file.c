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
    if (luaL_loadfile(lua_file->state_, name) ||
            lua_pcall(lua_file->state_, 0, 0, 0)) {
        DPRINT("%s", lua_tostring(lua_file->state_, -1));
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


#ifdef LUCY_DEBUG

void lucy_LuaFile_TEST()
{
    lucy_File lua_file = lucy_CreateFile();
    lucy_OpenFile(&lua_file, "/Users/wangqiansheng/Code/a.lua");
    lucy_Data data = lucy_GetData(&lua_file, "num");
    lucy_PrintData(&data);
    lucy_Data str = lucy_GetData(&lua_file, "str");
    lucy_PrintData(&str);
    lucy_Data boolean = lucy_GetData(&lua_file, "bool");
    lucy_PrintData(&boolean);
    lucy_Data table = lucy_GetData(&lua_file, "table");
    lucy_PrintData(&table);
    lucy_Data sum = lucy_GetData(&lua_file, "sum");
    lucy_PrintData(&sum);
    lucy_Data n = lucy_GetData(&lua_file, "n");
    lucy_PrintData(&n);
    lucy_CloseFile(&lua_file);
}

#endif
