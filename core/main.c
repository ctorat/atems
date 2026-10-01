/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <cul/chipcom.h>

/*
 * Represents a ROM file
 *
 * @data:  Data buffer created by mmap()
 * @len:   Length of data buffer
 */
struct rom_file {
    void *data;
    size_t len;
};

static void
help(void)
{
    printf("-- APTEL Emulation Suite --\n");
    printf("usage: ./atems [flags]\n");
    printf("[-h]    Display this help menu\n");
    printf("[-f]    Firmware path [required]\n");
}

/*
 * Begin virtual machine operation
 *
 * @rfp:  Pointer to ROM file descriptor
 */
static void
vm_run(const struct rom_file *rfp)
{
    struct soc_info soc;
    int error;

    /* Initialize the ROM */
    error = rom_init_dev(&soc.rom, CHIP_ROM_CAP);
    if (error < 0) {
        perror("rom_init_dev");
        return;
    }

    error = rom_flash_dev(&soc.rom, rfp->data, rfp->len, 0);
    if (error < 0) {
        perror("rom_flash_dev");
        return;
    }

    error = chip_init_io(&soc);
    if (error < 0) {
        perror("chip_init_io");
        return;
    }
}

/*
 * Close a ROM file
 *
 * @rfp:  ROM file to close
 */
static int
rom_file_close(struct rom_file *rfp)
{
    if (rfp == NULL) {
        return -1;
    }

    munmap(rfp->data, rfp->len);
    rfp->data = NULL;
    rfp->len = 0;
    return 0;
}

/*
 * Open a firmware ROM
 *
 * @rom_path:  Firmware ROM path
 * @res:       Resulting descriptor is written here
 */
static int
rom_file_open(const char *rom_path, struct rom_file *res)
{
    int fd;

    if (rom_path == NULL || res == NULL) {
        return -1;
    }

    if ((fd = open(rom_path, O_RDONLY)) < 0) {
        perror("open");
        return -1;
    }

    /* Obtain the file size */
    res->len = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    /* Map the ROM file into memory */
    res->data = mmap(
        NULL,
        res->len,
        PROT_READ,
        MAP_SHARED,
        fd,
        0
    );

    if (res->data == NULL) {
        perror("mmap");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

int
main(int argc, char **argv)
{
    const char *fw_path = NULL;
    struct rom_file rom_file;
    int opt, error;

    if (argc < 2) {
        printf("fatal: too few arguments\n");
        help();
        return -1;
    }

    if (argc < 2) {
        printf("fatal: too few arguments\n");
        return -1;
    }

    while ((opt = getopt(argc, argv, "hf:")) != -1) {
        switch (opt) {
        case 'h':
            help();
            return 0;
        case 'f':
            if ((fw_path = strdup(optarg)) == NULL) {
                printf("fatal: out of memory for fw path\n");
                return -1;
            }

            break;
        }
    }

    if (fw_path == NULL) {
        printf("fatal: Firmware path is required\n");
        help();
    }

    error = rom_file_open(fw_path, &rom_file);
    if (error < 0) {
        printf("fatal: failed to open ROM file\n");
        return -1;
    }

    vm_run(&rom_file);
    rom_file_close(&rom_file);
    return 0;
}
