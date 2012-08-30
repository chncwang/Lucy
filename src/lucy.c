#include <stdio.h>
#include <stdlib.h>
#include "lucy.h"

int main(void) {
#ifdef LUCY_DEBUG
/*    lucy_CFunc_TEST();*/
/*    lucy_LuaFunc_TEST();*/
/*    lucy_OO_TEST();*/
    lucy_Table_TEST();
#endif
    return 0;
}
