<div align="center">
  <h1>🗡️SER🛡️</h1>
  <h3>Knight of Data Formats</h3>
</div>

## Introduction

**Ser** is a serialization library to convert to and from various data formats.

It is designed to be a single header to be included directly in your source code. The
main goals are efficiency and performance. The only dependency is the [⚡️ION⚡️](
https://github.com/Pluvie/ion) system library, because of its native support for
reflection.

## Features

The target data formats that **Ser** shall provide support for are listed here, along
with their development status.

| Format | Implementation | Specification |
|--------|----------------|---------------|
| JSON   |       🟢       |       🟢      |
| XML    |       🔴       |       🔴      |
| CSV    |       🔴       |       🔴      |
| gRPC   |       🔴       |       🔴      |

Other than these formats, Ser shall provide a binary C serialization format which
can help trasferring code objects on networked machines.

## Benchmarks

All benchmarks are run on an Intel(R) Xeon(R) CPU E3-1241 v3 @ 3.50GHz, built on
Haswell architecture.

### JSON

We utilized the exact same process of [kostya JSON benchmarks](
https://github.com/kostya/benchmarks?tab=readme-ov-file#json). Our results are
consistent with theirs, so you can consider reliable the rankings of **Ser** as they
emerge from the lists below.

Results by execution speed:

| Name                    | Speed       |
|-------------------------|-------------|
| C++     simdjson        | 143 ms      |
| **C     Ser**           | **177 ms**  |
| Rust    serde           | 228 ms      |
| Go      encoding/json   | 1285 ms     |
| Python  json            | 1881 ms     |
| Ruby    JSON            | 2640 ms     |

Results by memory consumption:

| Name                    | Memory    |
|-------------------------|-----------|
| Rust    serde           | 13 MB     |
| **C     Ser**           | **25 MB** |
| C++     simdjson        | 63 MB     |
| Go      encoding/json   | 69 MB     |
| Ruby    JSON            | 255 MB    |
| Python  json            | 336 MB    |

Memory consumption is the actual memory overhead that the program uses to parse the
JSON file, therefore deducing the ~110MB of raw file bytes which are always included
in the program memory.

Another thing that we measured, which is not often found in benchmark, is compilation
time. The cost of a software is the sum of the cost of its runtime plus the cost of its
development. During development the compilation speed can take a substantial amount of 
time, therefore we feel that it's important to mention this aspect as well.

Results by compilation speed:

| Name                    | Speed       |
|-------------------------|-------------|
| Go      encoding/json   | 140 ms      |
| **C     Ser**           | **480 ms**  |
| C++     simdjson        | 6800 ms     |
| Rust    serde           | 7350 ms     |

In conclusion, we would like to point out another aspect of software development which
is maintainability. This is of course by definition a non-scientific benchmark, as it
involves subjective judgment on code quality and organization. However, we encourage
you to take a look at **Ser** `json_decode` function and its internals. Hopefully you
will find everything extremely explicit and consequential. You will not find intricate
performance squeezing code, convoluted and unexplicable logics or syntax and language
magics. Everything should be direct, plain and simple.

This is to point out two things:

  1. C, with its simplicity, can achieve top-level performance in all measurements
    without complicated code. Simple, explicit, procedural logic, along with some
    experience on hardware principles, are enough to reach important goals and empower
    everyone to write beautiful, maintainable and performant software. This is pretty
    much what the [⚡️ION⚡️](https://github.com/Pluvie/ion) system strives for.
  2. There is plenty of opportunity to improve the performance of **Ser** on the above
    benchmarks, such as using SIMD instructions. However, tor the reason listed in the
    above point, we are more interested in keeping the code as it is, therefore we will
    not take this endeavour in the near future. Still, at some point we might release a
    performance focused version of **Ser** just for the sake of it.

### CSV

TODO

### XML

TODO
