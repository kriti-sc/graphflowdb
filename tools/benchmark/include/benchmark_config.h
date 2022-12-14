#pragma once

#include <string>

using namespace std;

namespace graphflow {
namespace benchmark {

/**
 * Benchmark config should be shared for a suite of benchmarks
 */
struct BenchmarkConfig {
    bool enableProfile = false;
    // number of warm up runs
    uint32_t numWarmups = 1;
    // number of actual runs
    uint32_t numRuns = 5;
    // number of threads to execute benchmark
    uint32_t numThreads = 1;
    // output benchmark log to file
    string outputPath;
    // in-memory mode
    bool isInMemoryMode = false;
    uint64_t defaultBufferPoolSize = 1 << 22;
    uint64_t largeBufferPoolSize = 1 << 22;
};

} // namespace benchmark
} // namespace graphflow
