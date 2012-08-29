#include "lucy.h"

#ifdef LUCY_DEBUG

static lucy_List Hello(const lucy_List *args)
{
    int times = args->datas_[0].cntnt_.num_;
    const lucy_Data *func = args->datas_ + 1;
    lucy_Data str = lucy_Str("Hello world!");
    int i;
    for (i=0; i<times; ++i) {
        lucy_Call(func, 0, 1, &str);
    }

    return lucy_GetList(0);
}


lucy_GenLuaCFunction(Hello, 0, 2);


void lucy_CFunc_TEST()
{
    lucy_File file = lucy_CreateFile();
    lucy_OpenFile(&file, "/Users/wangqiansheng/Code/a.lua");
    lucy_SetCFunc(&file, "Hello", Hello);
    lucy_Run(&file);
}

#endif
