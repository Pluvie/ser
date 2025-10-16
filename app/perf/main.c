#define _POSIX_C_SOURCE 200809L
#include "perf.h"
#include "perf.c"

int0 main (
    int0 argc,
    char** argv
)
{
  /* Running all perfs for JSON. */
  for (int i = 0; i < countof(json_perfs); i++) {
    struct perf* perf = json_perfs + i;
    printl("Running: ", f(perf->name));

    /* Creates an allocator to hold the result of all runs for this perf. */
    struct allocator allocator = allocator_init(0);
    perf->runs = list_alloc(struct perf_run, perf->max_runs, &allocator);

    /* Executes the perf! */
    perf_exec(perf);

    /* We don't need the memory anymore, we can just discard whatever that was
      allocated in a single statement. Pretty nifty isn't it? Imagine having now to
      recover all allocated objects and free them one by one. */
    allocator_release(&allocator);

    /* If for whatever reason the perf encountered an error, we must abort. */
    if (unlikely(perf->status != 0)) {
      printl(perf->name, " exited abnormally");
      if (failure.occurred)
        printl("failure: ", failure.message);
      return EXIT_FAILURE;
    }

    struct perf_run average = perf->average;
    printl("time: ", f(average.time.total), ", memory: ", f(average.memory.child));
  }

  /* Let's print all the results ordered by speed and the memory. */
  struct perf json_perfs_by_speed[countof(json_perfs)] = { 0 };
  struct perf json_perfs_by_memory[countof(json_perfs)] = { 0 };

  memory_copy(json_perfs_by_speed, json_perfs, sizeof(json_perfs));
  memory_copy(json_perfs_by_memory, json_perfs, sizeof(json_perfs));

  qsort(json_perfs_by_speed, countof(json_perfs), sizeof(struct perf), perf_cmp_by_speed);
  qsort(json_perfs_by_memory, countof(json_perfs), sizeof(struct perf), perf_cmp_by_memory);

  printl();
  printl("Results by speed:");
  for (int i = 0; i < countof(json_perfs); i++) {
    struct perf* perf = json_perfs_by_speed + i;
    print(f(perf->name));
    for (int i = perf->name.length; i < 32; i++)
      print(" ");
    printl(": ", f(perf->average.time.total * 1000), " ms");
  }

  printl();
  printl("Results by memory:");
  for (int i = 0; i < countof(json_perfs); i++) {
    struct perf* perf = json_perfs_by_memory + i;
    print(f(perf->name));
    for (int i = perf->name.length; i < 32; i++)
      print(" ");
    printl(": ", f((perf->average.memory.child - 112384) / 1024), " MB");
  }

  return EXIT_SUCCESS;
}
