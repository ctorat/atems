/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#ifndef IO_ROM_H
#define IO_ROM_H 1

#include <common/lazybuf.h>

/*
 * Represents a common ROM device, it is to be flashed
 * on startup.
 *
 * @data:    Actual data buffer
 */
struct romdev {
    struct lazybuf data;
};

/*
 * Initialize a rom device
 *
 * @romdev:     ROM device to initialize
 * @capacity:   Maximum capacity of ROM to initialize
 *
 * Returns zero on success
 */
int rom_init_dev(struct romdev *romdev, size_t capacity);

/*
 * Flash a ROM device
 *
 * @romdev:   ROM device to flash
 * @src:      Source buffer to copy from
 * @len:      Number of bytes to flash
 * @off:      ROM offset to flash to
 *
 * Returns zero on success
 */
int rom_flash_dev(struct romdev *romdev, void *src, size_t len, size_t off);

#endif  /* !IO_ROM_H */
