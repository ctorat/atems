/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#ifndef BUS_MAINBUS_H
#define BUS_MAINBUS_H 1

#include <stdint.h>
#include <stddef.h>

/*
 * Represents a mainbus endpoint
 *
 * @start:  Start address of endpoint
 * @end:    Non-inclusive end address of endpoint
 * @data:   Endpoint specific data
 * @read:   Read hook
 */
struct mainbus_endpoint {
    uintptr_t start;
    uintptr_t end;
    void *data;
    int(*read)(void *data, void *buf, size_t off, size_t len);
};

/*
 * Resolve an endpoint on the mainbus by using its address
 *
 * @addr:   Address to resolve into endpoint
 * @ep_res: Endpoint result is written here
 *
 * Returns zero on success
 */
int mainbus_resolve(uintptr_t addr, struct mainbus_endpoint **ep_res);

#endif  /* !BUS_MAINBUS_H */
