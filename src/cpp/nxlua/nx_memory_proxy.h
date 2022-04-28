#ifndef NXLUA_NX_MEMORY_PROXY_H
#define NXLUA_NX_MEMORY_PROXY_H

#define NX_ALLOC(t, size) malloc(sizeof(t) * size)
#define NX_FREE(ptr)      free(ptr)

#endif