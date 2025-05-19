cmake_minimum_required(VERSION 3.25)

project(BenchmarkAndTest)

set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)
add_subdirectory(benchmark)

enable_testing()
add_subdirectory(naming_requirements)
add_subdirectory(virtual_method)

add_subdirectory(my_benchmarks)



