/*
 * Fil-C prefixes external symbols ("pizlonation"). Provide minimal shims so
 * BoxFort can still link against the system's unprefixed loader APIs.
 */

#include <link.h>

int pizlonated_dl_iterate_phdr(int (*callback)(struct dl_phdr_info *info, size_t size, void *data), void *data)
{
    return dl_iterate_phdr(callback, data);
}

