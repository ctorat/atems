/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#ifndef COMMON_TRACE_H
#define COMMON_TRACE_H 1

#include <common/comdef.h>
#include <stdio.h>

/*
 * Some helper macros that can be used for diagnostics, important
 * information or errors.
 */
#define trace_info(fmt, ...) \
    printf("[info]: " fmt, ##__VA_ARGS__)
#define trace_error(fmt, ...) \
    printf("[error]: " fmt, ##__VA_ARGS__)
#define trace_fatal(fmt, ...) \
    printf("[fatal]: " fmt, ##__VA_ARGS__)

/*
 * For debug messsage, you'll need to define ATEMS_DEBUG
 * for this to work...
 */
#ifdef ATEMS_DEBUG
#define trace_debug(fmt, ...) \
    printf("[debug]: " fmt, ##__VA_ARGS__)
#else
#define trace_debug(fmt, ...) NOTHING
#endif

#endif  /* !COMMON_TRACE_H */
