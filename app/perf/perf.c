#include <ser.c>

struct perf json_perfs[] = {
  { string("simdjson (C/C++)"), string("json/exe/simdjson"),  50 },
  { string("serde (Rust)"),     string("json/exe/rust"),      30 },
  { string("json (Go)"),        string("json/exe/go"),        10 },
  { string("ion (C)"),          string("json/exe/ion"),       50 },
  { string("json (Ruby)"),      string("json/exe/ruby"),       5 },
  { string("json (Python)"),    string("json/exe/python"),     5 },
};
