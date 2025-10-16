/*
  Lists.
*/

#define list_of struct perf_run
#include <ion/containers/list.h>

#if standard(>= C11)
#define list_function(type, func, ...)                        \
  _Generic(type,                                              \
    list<struct perf_run>  : list<struct perf_run>_ ## func   \
  )
#endif
