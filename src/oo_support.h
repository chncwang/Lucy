#ifndef OO_SUPPORT_H
#define	OO_SUPPORT_H

#include "defs.h"
#include "lua_data_array.h"
#include "stdarg.h"

struct lucy_File;

lucy_Data lucy_CallClassMethod(const struct lucy_File *file,
                               const char *class_name,
                               const char *method_name,
                               int ac,
                               ...);
lucy_List lucy_CallMethod(const lucy_Data *objc, const char *method_name,
                          int rc,
                          int ac,
                          ...);

#ifdef LUCY_DEBUG

void lucy_OO_TEST();

#endif

#endif
