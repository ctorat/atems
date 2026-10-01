/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#ifndef IO_ROMVAR_H
#define IO_ROMVAR_H 1

/*
 * Used by the platform bus to read the ROM
 *
 * @romdev:  ROM device to read
 * @dest:    Buffer to read into
 * @off:     Offset to read at
 * @len:     Number of bytes to read
 *
 * Returns zero on success
 */
int rom_bus_read(void *romdev, void *dest, size_t off, size_t len);

#endif  /* !IO_ROMVAR_H */
