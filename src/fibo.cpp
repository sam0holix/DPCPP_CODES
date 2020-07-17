#include<CL/sycl.hpp>
using namespace sycl;

static const int N = 20;

int main() {
	queue q;
	std::cout << "Device: " <<q.get_device().get_info<info::device::name>() <<std::endl;

	int* data = static_cast<int*>(malloc_shared(N*sizeof(int),q));

	q.parallel_for(range<1>(N), [=] (id<1> i) {
			if(i==0) data[i] = 0;
			else if(i==1) data[i] = 1;
			else data[i] = data[i-1] + data[i-2];	
			}).wait();

	for(int i=0;i<N;i++) std::cout << data[i] << std::endl;
	free(data,q);
	return 0;
}
