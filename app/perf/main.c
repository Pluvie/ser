#include "perf.h"
#include "perf.c"

int0 main (
    int0 argc,
    char** argv
)
{
  for (int i = 0; i < countof(perfs); i++) {
    printl("Perf [", f(i), "] >>> ", f(perfs[i].name));
  }
  return EXIT_SUCCESS;
}
