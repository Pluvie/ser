<div align="center">
  <h1>🗡️SER🛡️</h1>
  <h3>Knight of Data Formats</h3>
</div>

## Introduction

🗡️SER🛡️ is a serialization library to convert to and from various data formats.

It is designed to be a single header to be included directly in your source code. The
main goals are efficiency and performance. The only dependency is the ⚡️ION⚡️ system,
to which this library is built upon, for its native support for reflection.

## Features

🗡️SER🛡️ shall provide serialization for:

| Format | Implementation | Specification |
|--------|----------------|---------------|
| JSON   |       🟢       |       🟢      |
| XML    |       🔴       |       🔴      |
| CSV    |       🔴       |       🔴      |

## Benchmarks

### JSON

Below some benchmarks on JSON parsing. The code is based on [kostya](
https://github.com/kostya/benchmarks?tab=readme-ov-file#json) benchmarks. We utilized
the exact same JSON as source and the same benchmarking mechanism.

Results by execution speed:

| Name                    | Speed         |
|-------------------------|---------------|
| C++     simdjson        | 303 ms        |
| **C     🗡️SER🛡️**       | **395 ms**    |
| Rust    serde           | 454 ms        |
| Go      encoding/json   | 2470 ms       |
| Python  json            | 3674 ms       |
| Ruby    JSON            | 5262 ms       |

Results by memory consumption:

| Name                    | Memory    |
|-------------------------|-----------|
| Rust    serde           | 13 MB     |
| **C     🗡️SER🛡️**       | **25 MB** |
| C++     simdjson        | 63 MB     |
| Go      encoding/json   | 69 MB     |
| Ruby    JSON            | 255 MB    |
| Python  json            | 336 MB    |

Memory consumption is the actual memory overhead that the program uses to parse the
JSON file, therefore deducing the ~110MB of raw file bytes.

### CSV

TODO

### XML

TODO
