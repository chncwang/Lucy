#include "lua_value.h"


lucy_Data lucy_Num(double num)
{
    lucy_Data r = {lucy_TypeNum};
    r.cntnt_.num_ = num;
    return r;
}


lucy_Data lucy_Str(const char *str)
{
    lucy_Data r = {lucy_TypeStr};
    r.cntnt_.str_ = str;
    return r;
}


lucy_Data lucy_Bool(bool boolean)
{
    lucy_Data r = {lucy_TypeBool};
    r.cntnt_.boolean_ = boolean;
    return r;
}


lucy_Data lucy_Nil()
{
    lucy_Data r = {lucy_TypeNil};
    return r;
}
