/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#ifndef COMMON_COMDEF_H
#define COMMON_COMDEF_H 1

/* Compiler wrapper macros */
#define ATTR(x)     __attribute__((x))
#define ALIGN(n)    ATTR(aligned((n)))
#define NOTHING     (void)0

#endif  /* !COMMON_COMDEF_H */
