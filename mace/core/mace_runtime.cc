//
// Copyright (c) 2017 XiaoMi All rights reserved.
//

#include "mace/public/mace_runtime.h"
#include "mace/core/runtime/cpu/cpu_runtime.h"
#include "mace/core/runtime/opencl/opencl_runtime.h"

namespace mace {

std::shared_ptr<KVStorageFactory> kStorageFactory = nullptr;

void ConfigOpenCLRuntime(GPUPerfHint gpu_perf_hint,
                         GPUPriorityHint gpu_priority_hint) {
  VLOG(1) << "Set GPU configurations, gpu_perf_hint: " << gpu_perf_hint
          << ", gpu_priority_hint: " << gpu_priority_hint;
  OpenCLRuntime::Configure(gpu_perf_hint, gpu_priority_hint);
}

void ConfigKVStorageFactory(std::shared_ptr<KVStorageFactory> storage_factory) {
  VLOG(1) << "Set internal KV Storage Engine";
  kStorageFactory = storage_factory;
}

void ConfigOmpThreads(int omp_num_threads) {
  VLOG(1) << "Config CPU omp_num_threads: " << omp_num_threads;
  SetOmpThreads(omp_num_threads);
}

void ConfigCPUPowerOption(CPUPowerOption power_option) {
  VLOG(1) << "Config CPU power option" << power_option;
  SetThreadsAffinity(power_option);
}

};  // namespace mace