#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include "SyncedMemory.h"
#include "pgm.h"
#include "lab3.h"
using namespace std;

#define CHECK {\
	auto e = cudaDeviceSynchronize();\
	if (e != cudaSuccess) {\
		printf("At " __FILE__ ":%d, %s\n", __LINE__, cudaGetErrorString(e));\
		abort();\
	}\
}

int main(int argc, char **argv)
{
	if (argc != 7) {
		printf("Usage: %s <background> <target> <mask> <offset x> <offset y> <output>\n", argv[0]);
		abort();
	}
	bool sucb, suct, sucm;
	int wb, hb, cb, wt, ht, ct, wm, hm, cm;
	auto imgb = ReadNetpbm(wb, hb, cb, sucb, argv[1]);
	auto imgt = ReadNetpbm(wt, ht, ct, suct, argv[2]);
	auto imgm = ReadNetpbm(wm, hm, cm, sucm, argv[3]);
	if (not (sucb and suct and sucm)) {
		puts("Something wrong with reading the input image files.");
		abort();
	}
	if (wt != wm or ht != hm) {
		puts("The mask and target image must have the same size.");
		abort();
	}
	if (cm != 1) {
		puts("The mask image must be mono-colored.");
		abort();
	}
	if (cb != 3 or ct != 3) {
		puts("The background and target image must be colored.");
		abort();
	}
	const int oy = atoi(argv[4]), ox = atoi(argv[5]);

	const int SIZEB = wb*hb*3;
	const int SIZET = wt*ht*3;
	const int SIZEM = wm*hm;
	MemoryBuffer<float> background(SIZEB), target(SIZET), mask(SIZEM), output(SIZEB);
	auto background_s = background.CreateSync(SIZEB);
	auto target_s = target.CreateSync(SIZET);
	auto mask_s = mask.CreateSync(SIZEM);
	auto output_s = output.CreateSync(SIZEB);

	float *background_cpu = background_s.get_cpu_wo();
	float *target_cpu = target_s.get_cpu_wo();
	float *mask_cpu = mask_s.get_cpu_wo();
	copy(imgb.get(), imgb.get()+SIZEB, background_cpu);
	copy(imgt.get(), imgt.get()+SIZET, target_cpu);
	copy(imgm.get(), imgm.get()+SIZEM, mask_cpu);

	PoissonImageCloning(
		background_s.get_gpu_ro(),
		target_s.get_gpu_ro(),
		mask_s.get_gpu_ro(),
		output_s.get_gpu_wo(),
		wb, hb, wt, ht, oy, ox
	);

	unique_ptr<uint8_t[]> o(new uint8_t[SIZEB]);
	const float *o_cpu = output_s.get_cpu_ro();
	transform(o_cpu, o_cpu+SIZEB, o.get(), [](float f) -> uint8_t { return max(min(int(f+0.5f), 255), 0); });
	WritePPM(o.get(), wb, hb, argv[6]);
	return 0;
}
