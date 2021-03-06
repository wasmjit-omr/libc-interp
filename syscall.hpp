#ifndef LIBC_INTERP_SYSCALL_HPP
#define LIBC_INTERP_SYSCALL_HPP

#include <vector>

#include "src/interp/interp.h"

namespace wabt {

struct MmapFreeRegion {
    uint32_t start;
    uint32_t size;
};

class SyscallHandler {
  public:
    SyscallHandler(interp::Environment* env) : env_(env) {}

    void RegisterOnModule(interp::HostModule* module);
    interp::Result HandleSyscall(int n, const interp::TypedValue* args, Index num_args, uint32_t* return_value);
  private:
    interp::Result GetMemoryAddress(uint32_t src, uint32_t size, void** addr);

    interp::Result CopyFromMemory(void* dst, uint32_t src, uint32_t size);
    interp::Result StrcpyFromMemory(std::string* dst, uint32_t src);
    interp::Result CopyToMemory(const void* src, uint32_t dst, uint32_t size);

    interp::Result HandleRead(int fd, uint32_t buf, uint32_t size, uint32_t* return_value);
    interp::Result HandleWrite(int fd, uint32_t buf, uint32_t size, uint32_t* return_value);
    interp::Result HandleOpen(uint32_t filename, uint32_t flags, uint32_t mode, uint32_t* return_value);
    interp::Result HandleClose(int fd, uint32_t* return_value);
    interp::Result HandleBrk(uint32_t addr, uint32_t* return_value);
    interp::Result HandleIoctl(int fd, int cmd, const interp::TypedValue* args, Index num_args, uint32_t* return_value);
    interp::Result HandleLlseek(int fd, uint32_t off_hi, uint32_t off_lo, uint32_t result, uint32_t whence, uint32_t* return_value);
    interp::Result HandleReadv(int fd, uint32_t vecs, uint32_t num_vecs, uint32_t* return_value);
    interp::Result HandleWritev(int fd, uint32_t vecs, uint32_t num_vecs, uint32_t* return_value);
    interp::Result HandleMmap(uint32_t address, uint32_t length, uint32_t prot, uint32_t flags, int fd, uint32_t off, uint32_t* return_value);
    interp::Result HandleMunmap(uint32_t address, uint32_t length, uint32_t* return_value);
    interp::Result HandleMremap(uint32_t old_addr, uint32_t old_sz, uint32_t new_sz, uint32_t flags, uint32_t new_addr, uint32_t* return_value);
    interp::Result HandleClockGetTime(uint32_t clock_id, uint32_t res, uint32_t* return_value);

    std::vector<MmapFreeRegion> mmap_free_regions_;
    interp::Environment* env_;
};

}

#endif
