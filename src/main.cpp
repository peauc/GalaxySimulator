
#include <iostream>
#include <vector>
#include <display/Display.hpp>
#include <tbb/task_group.h>
#include <tbb/task_scheduler_init.h>
#include "logic/RootQuadrant.hpp"
#include "logic/Star.hpp"
#include <OpenCL/cl.hpp>
#include <fstream>
#include <sstream>

void initOpenCL(cl::Program **program, cl::Context **context,cl::Device **default_device)
{
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);
	if (all_platforms.size() == 0) {
		std::cout << " No platforms found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Platform default_platform = all_platforms[0];
	std::cout << "Using platform: " << default_platform.getInfo<CL_PLATFORM_NAME>() << "\n";
	
	//get default device of the default platform
	std::vector<cl::Device> all_devices;
	default_platform.getDevices(CL_DEVICE_TYPE_GPU, &all_devices);
	if (all_devices.size() == 0) {
		std::cout << " No devices found. Check OpenCL installation!\n";
		exit(1);
	}
	*default_device = &all_devices[1];
	std::cout << "Using device: " << (*default_device)->getInfo<CL_DEVICE_NAME>() << "\n";
	std::cout << "Precision " << (*default_device)->getInfo<CL_DEVICE_DOUBLE_FP_CONFIG>() << std::endl;
	
	
	
	*context = new cl::Context({**default_device});
	
	cl::Program::Sources sources;
	
	// kernel calculates for each element C=A+B
	// kernel calculates for each element C=A+B
	std::ifstream t("../src/opencl/computation.cl");
	std::stringstream buffer;
	buffer << t.rdbuf();
	std::string kernel_code = buffer.str();
	sources.push_back({kernel_code.c_str(),kernel_code.length()});
	
	*program = new cl::Program(**context, sources);
	if ((*program)->build({**default_device}) != CL_SUCCESS) {
		std::cout << " Error building: " << (*program)->getBuildInfo<CL_PROGRAM_BUILD_LOG>(**default_device) << "\n";
		std::cout << " Error building: " << (*program)->getBuildInfo<CL_PROGRAM_BUILD_STATUS>(**default_device) << "\n";
		exit(1);
	}
}

void runTestKernel()
{
	//get all platforms (drivers)
	cl::Program *program;
	cl::Context *context;
	cl::Device *default_device;
	
//	initOpenCL(&program, &context, &default_device);
	
	// create buffers on the device
	cl::Buffer buffer_A(*context, CL_MEM_READ_WRITE, sizeof(int) * 10);
	cl::Buffer buffer_B(*context, CL_MEM_READ_WRITE, sizeof(int) * 10);
	cl::Buffer buffer_C(*context, CL_MEM_READ_WRITE, sizeof(int) * 10);
	
	int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int B[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};
	
	//create queue to which we will push commands for the device.
	cl::CommandQueue queue(*context, *default_device);
	
	//write arrays A and B to the device
	queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int) * 10, A);
	queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, sizeof(int) * 10, B);
	
	
	//run the kernel
//    cl::KernelFunctor simple_add(cl::Kernel(program,"simple_add"),queue,cl::NullRange,cl::NDRange(10),cl::NullRange);
//    simple_add(buffer_A,buffer_B,buffer_C);
//    clCreateKernel(program, "simple_add", nullptr)
	//alternative way to run the kernel
	cl::Kernel kernel_add = cl::Kernel(*program, "simple_add");
	kernel_add.setArg(0, buffer_A);
	kernel_add.setArg(1, buffer_B);
	kernel_add.setArg(2, buffer_C);
	queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(10), cl::NullRange);
	queue.finish();
	
	int C[10];
	//read result C from the device to array C
	queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(int) * 10, C);
	
	std::cout << " result: \n";
	for (int i = 0; i < 10; i++) {
		std::cout << C[i] << " ";
	}
}

int main(int ac, char **av) {

	std::cout << "Start of the main thread" << '\n';

	//Set the random seed
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	//Create a vector of shared_ptr<Star>, this allow us to fit the stars into the quadtree while still having a strong reference on them
	std::vector<std::shared_ptr<Star>> vec;
	vec.emplace_back(std::make_shared<Star>(500, 500, 140000));
	for(int i = 0; i < STAR_NB; ++i) {
		vec.emplace_back(std::make_shared<Star>(
			250 + std::rand() % 500,
			250 + std::rand() % 500,
			10000));
	}
	auto rq = std::make_shared<RootQuadrant>(1000, vec);
	initOpenCL(&rq->program, &rq->context, &rq->defaultDevice);
	rq->getQuadrant().addToStarList(vec);
	rq->getQuadrant().balance();
	tbb::task_group g;
	auto d = Display(1000, rq, vec);
	d.init(ac, av, g, rq);
	return (0);
}


