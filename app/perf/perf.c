#include <ser.c>

struct perf perfs[] = {
  { string("simdjson (C/C++)"), string("exe/simdjson"), 50 },
  { string("serde (Rust)"),     string("exe/rust"),     30 },
  { string("json (Go)"),        string("exe/go"),       10 },
  { string("ion (C)"),          string("exe/ion"),      50 },
  { string("json (Ruby)"),      string("exe/ruby"),      5 },
  { string("json (Python)"),    string("exe/python"),    5 },
};
