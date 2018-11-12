//
// Created by peauc on 11/9/18.
//

#ifndef MULTICOREGALAXY_STARCONTAINER_HPP
#define MULTICOREGALAXY_STARCONTAINER_HPP
#include <cstddef>
#include <vector>
#include <cuda_runtime_api.h>
#include "Star.hpp"

class StarContainer {
public:
	__device__ __host__ StarContainer(class Star &star);
	__device__ __host__ ~StarContainer();
private:
	Star &star;
	std::vector<std::size_t> _parentIdToCompute;
};

#endif //MULTICOREGALAXY_STARCONTAINER_HPP
