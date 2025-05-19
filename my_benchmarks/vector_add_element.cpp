#include <benchmark/benchmark.h>

#include <vector>
#include <array>
#include <memory>

constexpr size_t rangeMin = 1 << 10;
// wider ranges cause time outs. Run this locally on your machine.
// constexpr size_t rangeMax = 1 << 20;
constexpr size_t rangeMax = 1 << 15;
constexpr size_t rangeMultiplier = 2;

struct SmallData
{
    bool visible;
};

struct BigData
{
    bool visible;
    std::array<int, 1024> data;
};

static void bench_iter_big_data(benchmark::State &state)
{
    const size_t howMany = state.range(0);
    for (auto _ : state)
    {
        std::vector<BigData> result(howMany);
        for (int i = 0; i < howMany; ++i)
        {
            result[i].visible = true;
        }
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(bench_iter_big_data)->RangeMultiplier(rangeMultiplier)->Range(rangeMin, rangeMax);

static void bench_iter_small_data(benchmark::State &state)
{
    const size_t howMany = state.range(0);
    for (auto _ : state)
    {
        std::vector<SmallData> result(howMany);
        for (int i = 0; i < howMany; ++i)
        {
            result[i].visible = true;
        }
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(bench_iter_small_data)->RangeMultiplier(rangeMultiplier)->Range(rangeMin, rangeMax);

static void bench_pushBack(benchmark::State &state)
{
    const size_t howMany = state.range(0);
    for (auto _ : state)
    {
        std::vector<int> result;
        result.reserve(howMany);
        for (int ii = 0; ii < howMany; ++ii)
        {
            result.push_back(ii * ii);
        }
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(bench_pushBack)->RangeMultiplier(rangeMultiplier)->Range(rangeMin, rangeMax);

static void bench_prealloc(benchmark::State &state)
{
    const size_t howMany = state.range(0);
    for (auto _ : state)
    {
        std::vector<int> result(howMany);
        for (int ii = 0; ii < howMany; ++ii)
        {
            result[ii] = ii * ii;
        }
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(bench_prealloc)->RangeMultiplier(rangeMultiplier)->Range(rangeMin, rangeMax);

struct IntArray
{
    std::unique_ptr<int[]> arr;
    size_t length;
};

static void bench_myArray(benchmark::State &state)
{
    const size_t howMany = state.range(0);
    for (auto _ : state)
    {
        IntArray result = {std::unique_ptr<int[]>{new int[howMany]}, howMany};
        for (int ii = 0; ii < howMany; ++ii)
        {
            result.arr[ii] = ii * ii;
        }
    }
}
BENCHMARK(bench_myArray)->RangeMultiplier(rangeMultiplier)->Range(rangeMin, rangeMax);
// Run the benchmark
BENCHMARK_MAIN();