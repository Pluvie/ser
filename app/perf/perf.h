#include <errno.h>
#include <ser.h>
#include "containers.h"

struct perf_run {
  int status;
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
  str command;
  int max_runs;
  int status;
  struct perf_run average;
  list<struct perf_run> runs;
};


void perf_exec (
    struct perf* perf
);

struct perf_run perf_run_exec (
    struct perf* perf
);
