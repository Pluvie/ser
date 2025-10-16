#define _POSIX_C_SOURCE 200809L
#include "perf.h"
#include "perf.c"

int0 main (
    int0 argc,
    char** argv
)
{
  for (int i = 0; i < countof(json_perfs); i++) {
    struct perf* perf = json_perfs + i;
    printl("Running: ", f(perf->name));

    struct allocator allocator = allocator_init(0);
    perf->runs = list_alloc(struct perf_run, perf->max_runs, &allocator);

    perf_exec(perf);

    allocator_release(&allocator);

    if (unlikely(perf->status != 0)) {
      printl(perf->name, " exited abnormally");
      if (failure.occurred)
        printl("failure: ", failure.message);
      return EXIT_FAILURE;
    }

    struct perf_run average = perf->average;
    printl("time: ", f(average.time.total), ", memory: ", f(average.memory.child));
  }

  return EXIT_SUCCESS;
}
