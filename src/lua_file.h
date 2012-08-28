#ifndef LUA_FILE_H
#define LUA_FILE_H

#include "defs.h"
#include "lua_data.h"


/* *****************************************************************************
 * description          : the lua file which runs the lua program.
 * state_ [lua_State *] : the global lua state.
 * ****************************************************************************/
typedef struct lucy_File{
    lua_State *state_;
} lucy_File;


lucy_File lucy_CreateFile();

/* *****************************************************************************
 * description               : open a lua file.
 * lua_file [lucy_LuaFile *] : the lua file.
 * name [char *]             : lua file's path.
 * ****************************************************************************/
void lucy_OpenFile(const lucy_File *lua_file, const char *name);

void lucy_Run(const lucy_File *file);
void lucy_CloseFile(const lucy_File *lua_file);

/* *****************************************************************************
 * description               : get global variable from lua program.
 * lua_file [lucy_LuaFile *] : the lua file, which runs the lua program.
 * name [char *]             : the variable's name.
 * ****************************************************************************/
lucy_Data lucy_GetData(const lucy_File *lua_file,
                       const char *name);

void lucy_SetData(const lucy_File *lua_file, const char *name,
                  const lucy_Data *data);

#ifdef LUCY_DEBUG

void lucy_LuaFile_TEST();

#endif

#endif
