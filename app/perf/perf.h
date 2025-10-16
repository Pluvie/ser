#include <ser.h>
#include "containers.h"

struct perf_run {
  struct {
    dec user;
    dec sys;
    dec total;
  } time;
  struct {
    int child;
    int group;
  } memory;
};

struct perf {
  str name;
  str path;
  int max_runs;
  struct perf_run average;
  list<struct perf_run> runs;
};
