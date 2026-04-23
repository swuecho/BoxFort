/*
 * Fil-C does not support assembling BoxFort's handwritten trampolines.
 *
 * For Fil-C builds we provide the trampoline as raw machine code bytes in C.
 * This file is intentionally minimal and only covers the CI target: Linux x86-64.
 */

#include <stdint.h>
#include <stddef.h>

#include "config.h"

#if !defined(BXF_ARCH_X86_64)
#error "Fil-C trampoline is only implemented for x86_64."
#endif

/*
 * x86-64 trampoline used by `bxfi_exe_patch_main`:
 *   jmp *addr_data(%rip)        ; opcode: FF 25 00 00 00 00
 *   .align 8
 * addr_data:
 *   .quad 0
 *
 * `bxfi_exe_patch_main` copies these bytes and overwrites the 8-byte slot at
 * `bxfi_trampoline_addr` with the new main function pointer.
 */
struct bxfi_trampoline_blob {
    uint8_t jmp_indirect_rip[6];
    uint8_t pad_to_align8[2];
    uintptr_t addr_data;
};

const struct bxfi_trampoline_blob bxfi_trampoline_blob = {
    .jmp_indirect_rip = {0xFF, 0x25, 0x00, 0x00, 0x00, 0x00},
    .pad_to_align8 = {0x00, 0x00},
    .addr_data = 0,
};

void *bxfi_trampoline_filc_begin(void)
{
    return (void *) (uintptr_t) &bxfi_trampoline_blob;
}

void *bxfi_trampoline_filc_addr(void)
{
    return (void *) (uintptr_t) &bxfi_trampoline_blob.addr_data;
}

void *bxfi_trampoline_filc_end(void)
{
    return (void *) (uintptr_t) ((const uint8_t *) &bxfi_trampoline_blob + sizeof bxfi_trampoline_blob);
}

