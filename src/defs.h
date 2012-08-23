#ifndef DEFS_H
#define DEFS_H

#define LUCY_DEBUG

#ifdef LUCY_DEBUG
    #define DPRINT(...) {printf(__VA_ARGS__); printf("\n");}
    #define DASSERT(ARG) assert(ARG)
#endif

#endif
