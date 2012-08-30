#include "oo_support.h"
#include "lua_file.h"
#include "lua_func.h"
#include "lua_table.h"


lucy_Data lucy_CallClassMethod(const struct lucy_File *file,
                               const char *class_name,
                               const char *method_name,
                               int ac,
                               ...)
{
    lucy_Data lua_class = lucy_GetData(file, class_name);
    DPRINT("b0");
    lucy_Data method = lucy_TblData(&lua_class, method_name);
    DPRINT("ba");

    lucy_List list = lucy_GetList(1, &lua_class);
    va_list arg;
    va_start(arg, ac);
    int i;
    for (i=0; i<ac; ++i) {
        lucy_AddDataToList(&list, va_arg(arg, lucy_Data *));
    }
    va_end(arg);
    DPRINT("bb");

    return lucy_CallWithList(&method, 1, &list).datas_[0];
}


lucy_List lucy_CallMethod(const lucy_Data *objc, const char *method_name,
                          int rc,
                          int ac,
                          ...)
{
    lucy_Data method = lucy_TblData(objc, method_name);
    lucy_List list = lucy_GetList(1, objc);
    va_list arg;
    va_start(arg, ac);
    int i;
    for (i=0; i<ac; ++i) {
        lucy_AddDataToList(&list, va_arg(arg, lucy_Data *));
    }
    va_end(arg);

    return lucy_CallWithList(&method, rc, &list);
}


#ifdef LUCY_DEBUG

#include "lua_value.h"

void lucy_OO_TEST()
{
    lucy_File file = lucy_CreateFile();
    lucy_OpenFile(&file, "/Users/wangqiansheng/Code/a.lua");
    DPRINT("a");
    lucy_Run(&file);
    DPRINT("b");
    lucy_Data objc = lucy_CallClassMethod(&file, "Human", "new", 0);
    DPRINT("c");
    lucy_Data str = lucy_Str("Hello world!");
    lucy_CallMethod(&objc, "talk", 0, 1, &str);
}

#endif
