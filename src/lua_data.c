#include "lua_data.h"


#ifdef LUCY_DEBUG


static void PrintNum(const lucy_Content *cntnt)
{
    DPRINT("value = %lf", cntnt->num_);
}


static void PrintStr(const lucy_Content *cntnt)
{
    DPRINT("value = %s", cntnt->str_);
}


static void PrintBool(const lucy_Content *cntnt)
{
    DPRINT("value = %d", cntnt->boolean_);
}


static void PrintRef(const lucy_Content *cntnt)
{
    DPRINT("ptr = %p, index = %d", cntnt->ref_.state_, cntnt->ref_.index_);
}


static void PrintNil(const lucy_Content *cntnt)
{
    DPRINT("value = nil");
}


void lucy_PrintData(const lucy_Data *luadata)
{
    static const char *type_name[lucy_TypesCount] = {
        "number",
        "string",
        "boolean",
        "function",
        "table",
        "nil"
    };
    DPRINT("type = %s", type_name[luadata->type_]);

    static void (*PrintValue[lucy_TypesCount])(const lucy_Content *) = {
        &PrintNum,
        &PrintStr,
        &PrintBool,
        &PrintRef,
        &PrintRef,
        &PrintNil
    };
    (*PrintValue[luadata->type_])(&(luadata->cntnt_));
}

#endif
