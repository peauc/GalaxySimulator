//
// Created by peauc on 11/9/18.
//

#ifndef MULTICOREGALAXY_CUDA_HPP
#define MULTICOREGALAXY_CUDA_HPP
#include <cuda_runtime_api.h>
#include "logic/StarContainer.hpp"
#include "vector"
#include "memory"

#define THETA 0.5
#define G 0.0000066742
#define SOFTENER 1000

#ifdef __JETBRAINS_IDE__
	#define __host__
	#define __device__
	#define __shared__
	#define __constant__
	#define __global__
#endif

void compute_accel_cuda(SpacialInformations *vec, class Quadrant *quadrant, float *res, size_t vecSize, size_t quadrantSize);
__global__ void __compute_accel_cuda(SpacialInformations *infoVec, class Quadrant *quadrantVec, float *res, size_t infoVecSize, size_t quadrantVecSize);
void apply_accel(std::vector<std::shared_ptr<Star>> &starList);

#endif //MULTICOREGALAXY_CUDA_HPP
