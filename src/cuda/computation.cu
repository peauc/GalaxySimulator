#include "cuda/cuda.hpp"
#include "utils/SpacialInformations.hpp"
#include "logic/Quadrant.hpp"

void apply_accel(std::vector<std::shared_ptr<Star>> &starList)
{
	for (auto &it: starList) {
		it->setX(it->getX() + it->getAccx());
		it->setY(it->getY() + it->getAccy());
	}
}

void compute_accel_cuda(SpacialInformations *vec, Quadrant *quadrant, float *res, size_t vecSize, size_t quadrantSize) {
	__compute_accel_cuda<<<1, 256>>>(vec, quadrant, res, vecSize, quadrantSize);
}

__global__ void __compute_accel_cuda(SpacialInformations *infoVec, Quadrant *quadrantVec, float *res, size_t infoVecSize, size_t quadrantVecSize)
{
	int id = blockIdx.x * blockDim.x + threadIdx.x;
	int gid = blockDim.x * gridDim.x;
	for (; id < infoVecSize; id += gid) {
		for (int j = 0; j < quadrantVecSize; j++) {
			auto d = quadrantVec[j]._width;
			auto r = sqrt(pow(infoVec[id]._x - quadrantVec[j]._cmx, 2) +
				      pow(infoVec[id]._y - quadrantVec[j]._cmy, 2) +
				      SOFTENER);
			if (d / r <= THETA) {
				auto k = quadrantVec[j]._mass * G / (pow(r + 5, 3));
				res[id * 2] = k * (quadrantVec[j]._cmx - infoVec[id]._x);
				res[id * 2 + 1] = k * (quadrantVec[j]._cmx - infoVec[id]._y);
			}
			
		}
	}
}
