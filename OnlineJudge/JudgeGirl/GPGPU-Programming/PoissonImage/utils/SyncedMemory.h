#pragma once
#include <cstddef>
#include <cassert>

template <typename T>
class SyncedMemory {
	enum MemoryState {
		GPU_IS_NEW,
		CPU_IS_NEW,
		SYNCED
	} state_ = SYNCED;
	T *cpu_, *gpu_;
	size_t n_;

	void Sync()
	{
		switch (state_) {
			case CPU_IS_NEW:
				cudaMemcpy(gpu_, cpu_, sizeof(T)*n_, cudaMemcpyHostToDevice);
				break;
			case GPU_IS_NEW:
				cudaMemcpy(cpu_, gpu_, sizeof(T)*n_, cudaMemcpyDeviceToHost);
				break;
		}
		state_ = SYNCED;
	}
public:
	void Reset(T* cpu, T *gpu, const size_t n) { cpu_ = cpu; gpu_ = gpu; n_ = n; }
	SyncedMemory() { Reset(nullptr, nullptr, 0); }
	SyncedMemory(T* cpu, T *gpu, const size_t n) { Reset(cpu, gpu, n); }
	SyncedMemory& operator=(const SyncedMemory&) = delete;
	SyncedMemory(const SyncedMemory&) = delete;
	SyncedMemory& operator=(SyncedMemory &&mem)
	{
		if (this != &mem) {
			this->cpu_ = mem.cpu_;
			this->gpu_ = mem.gpu_;
			this->n_ = mem.n_;
			mem.cpu_ = mem.gpu_ = nullptr;
		}
		return *this;
	}
	SyncedMemory(SyncedMemory &&mem)
	{
		this->cpu_ = mem.cpu_;
		this->gpu_ = mem.gpu_;
		mem.cpu_ = mem.gpu_ = nullptr;
	}

	T *get_cpu_wo() { state_ = CPU_IS_NEW; return cpu_; }
	T *get_gpu_wo() { state_ = GPU_IS_NEW; return gpu_; }
	const T* get_cpu_ro() { if (state_ != CPU_IS_NEW) { Sync(); } return cpu_; }
	const T* get_gpu_ro() { if (state_ != GPU_IS_NEW) { Sync(); } return gpu_; }
	T *get_cpu_rw() { get_cpu_ro(); return get_cpu_wo(); }
	T *get_gpu_rw() { get_gpu_ro(); return get_gpu_wo(); }
};

template <typename T>
class MemoryBuffer {
	T *cpu_ = nullptr, *gpu_ = nullptr;
	void Alloc(const size_t n)
	{
		if (n != 0) {
			cpu_ = new T[n];
			cudaMalloc(&gpu_, sizeof(T)*n);
		}
	}
public:
	void Free()
	{
		assert((gpu_ == nullptr) == (cpu_ == nullptr));
		delete[] cpu_;
		cudaFree(gpu_);
		cpu_ = gpu_ = nullptr;
	}

	void Realloc(const size_t n)
	{
		Free();
		Alloc(n);
	}

	MemoryBuffer(const size_t n = 0)
	{
		Alloc(n);
	}

	~MemoryBuffer()
	{
		Free();
	}

	MemoryBuffer& operator=(const MemoryBuffer&) = delete;
	MemoryBuffer(const MemoryBuffer&) = delete;
	MemoryBuffer& operator=(MemoryBuffer &&buf)
	{
		if (this != &buf) {
			this->cpu_ = buf.cpu_;
			this->gpu_ = buf.gpu_;
			buf.cpu_ = buf.gpu_ = nullptr;
		}
		return *this;
	}
	MemoryBuffer(MemoryBuffer &&buf)
	{
		this->cpu_ = buf.cpu_;
		this->gpu_ = buf.gpu_;
		buf.cpu_ = buf.gpu_ = nullptr;
	}

	SyncedMemory<T> CreateSync(const size_t n, const size_t offset = 0) {
		return SyncedMemory<T>(cpu_+offset, gpu_+offset, n);
	}
};
