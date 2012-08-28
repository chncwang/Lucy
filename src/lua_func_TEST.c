#include "lucy.h"

#ifdef LUCY_DEBUG

static lucy_List Sum(const lucy_List *args)
{
    lucy_Data a = lucy_Num(1);
    lucy_Data b = lucy_Num(2);
    return lucy_GetList(2, &a, &b);
}


lucy_GenLuaCFunction(Sum, 2, 0);


void lucy_CFunc_TEST()
{
    lucy_File file = lucy_CreateFile();
    lucy_OpenFile(&file, "/Users/wangqiansheng/Code/a.lua");
    lucy_SetCFunc(&file, "Sum", Sum);
    lucy_Run(&file);
}

#endif
