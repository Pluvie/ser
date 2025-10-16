#include <ser.c>

struct perf json_perfs[] = {
  { string("C++     simdjson"),       string("cd app/perf/json && cgmemtime -t exe/simdjson 2>&1"), 7 },
  { string("Rust    serde"),          string("cd app/perf/json && cgmemtime -t exe/rust     2>&1"), 7 },
  { string("Go      encoding/json"),  string("cd app/perf/json && cgmemtime -t exe/go       2>&1"), 7 },
  { string("C       🗡️SER🛡️"),        string("cd app/perf/json && cgmemtime -t exe/ion      2>&1"), 7 },
  { string("Ruby    JSON"),           string("cd app/perf/json && cgmemtime -t exe/ruby     2>&1"), 7 },
  { string("Python  json"),           string("cd app/perf/json && cgmemtime -t exe/python   2>&1"), 7 },
};


void perf_exec (
    struct perf* perf
)
{
  for (int i = 0; i < perf->max_runs; i++) {
    struct perf_run run = perf_run_exec(perf);

    if (run.status != 0) {
      perf->status = run.status;
      return;
    }

    list_push(&(perf->runs), run);
  }

  for list_each(&(perf->runs), struct perf_run* run) {
    perf->average.time.user += run->time.user;
    perf->average.time.sys += run->time.sys;
    perf->average.time.total += run->time.total;
    perf->average.memory.child += run->memory.child;
    perf->average.memory.group += run->memory.group;
  }

  perf->average.time.user = perf->average.time.user / perf->runs.length;
  perf->average.time.sys = perf->average.time.sys / perf->runs.length;
  perf->average.time.total = perf->average.time.total / perf->runs.length;
  perf->average.memory.child = perf->average.memory.child / perf->runs.length;
  perf->average.memory.group = perf->average.memory.group / perf->runs.length;
}

struct perf_run perf_run_exec (
    struct perf* perf
)
{
  struct perf_run result = { 0 };

  void* channel = popen(perf->command.chars, "r");
  if (channel == nullptr) {
    fail("cannot open channel", strerror(errno));
    result.status = 127;
    return result;
  }

  char output_buffer[1024] = { 0 };
  while (fgets(output_buffer, sizeof(output_buffer), channel) != nullptr);

  str output = { output_buffer, strlen(output_buffer) };
  for (int i = 0; i < 5; i++) {
    dec value = str_to_dec(&output);
    switch (i) {
    case 0:
      result.time.user = value;
      break;
    case 1:
      result.time.sys = value;
      break;
    case 2:
      result.time.total = value;
      break;
    case 3:
      result.memory.child = (int) value;
      break;
    case 4:
      result.memory.group = (int) value;
      break;
    }

    if (i == 4)
      break;

    while (*output.chars != ';')
      output.chars++;
    output.chars++;
  }

  result.status = pclose(channel);
  return result;
}

int0 perf_cmp_by_speed (
    const void* p1,
    const void* p2
)
{
  const struct perf* perf1 = p1;
  const struct perf* perf2 = p2;

  if (perf1->average.time.total == perf2->average.time.total)
    return 0;

  if (perf1->average.time.total > perf2->average.time.total)
    return 1;

  return -1;
}

int0 perf_cmp_by_memory (
    const void* p1,
    const void* p2
)
{
  const struct perf* perf1 = p1;
  const struct perf* perf2 = p2;

  if (perf1->average.memory.child == perf2->average.memory.child)
    return 0;

  if (perf1->average.memory.child > perf2->average.memory.child)
    return 1;

  return -1;
}
