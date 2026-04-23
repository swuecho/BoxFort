/*
 * Fil-C prefixes external symbols ("pizlonation"). Provide minimal shims so
 * BoxFort can still link against the system's unprefixed loader APIs.
 */

#include <link.h>

/*
 * Force the exported symbol name to exactly `pizlonated_dl_iterate_phdr`.
 * Fil-C may otherwise apply its own renaming to this definition.
 */
int bxfi_filc_dl_iterate_phdr(int (*callback)(struct dl_phdr_info *info, size_t size, void *data), void *data)
    __asm__("pizlonated_dl_iterate_phdr");

int bxfi_filc_dl_iterate_phdr(int (*callback)(struct dl_phdr_info *info, size_t size, void *data), void *data)
{
    return dl_iterate_phdr(callback, data);
}

