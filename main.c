#include <stdio.h>
#include "lfs/lfs.h"
#include "lfs_impl/custom_lfs.h"

// Define a block device. This could be an array or any memory storage.
#define BLOCK_SIZE 512
#define BLOCK_COUNT 2048
uint8_t memory[BLOCK_SIZE * BLOCK_COUNT];

// Block device operations
/*
int block_device_read(const struct lfs_config *c, lfs_block_t block,
                      lfs_off_t offset, void *buffer, lfs_size_t size) {
    memcpy(buffer, &memory[block * c->block_size + offset], size);
    return 0;
}

int block_device_prog(const struct lfs_config *c, lfs_block_t block,
                      lfs_off_t offset, const void *buffer, lfs_size_t size) {
    memcpy(&memory[block * c->block_size + offset], buffer, size);
    return 0;
}

int block_device_erase(const struct lfs_config *c, lfs_block_t block) {
    memset(&memory[block * c->block_size], 0xFF, c->block_size);
    return 0;
}

int block_device_sync(const struct lfs_config *c) {
    return 0;
}
*/

const struct lfs_config cfg = {
    .read = block_device_read,
    .prog = block_device_prog,
    .erase = block_device_erase,
    .sync = block_device_sync,

    .read_size = 16,
    .prog_size = 16,
    .block_size = 4096,
    .block_count = 128,
    .cache_size = 128,
    .lookahead_size = 16,
    .block_cycles = 500,
};


int main(void) {

    lfs_t lfs;

    // mount the filesystem
    int err = lfs_mount(&lfs, &cfg);

    // reformat if we can't mount the filesystem
    // this should only happen on the first boot
    if (err) {
        lfs_format(&lfs, &cfg);
        err = lfs_mount(&lfs, &cfg);
    }

    lfs_file_t file;
    int res = lfs_file_open(&lfs, &file, "my_file.txt", LFS_O_CREAT | LFS_O_RDWR);
    if (res < 0) {
        // Handle error, res will be negative if the file couldn't be opened
        printf("Error opening file: %d\n", res);
    }
    // Write data to the file
    const char *message = "Hello, LittleFS!";
    lfs_file_write(&lfs, &file, message, strlen(message));


    // remember the storage is not updated until the file is closed successfully
    lfs_file_close(&lfs, &file);

    lfs_unmount(&lfs);

    return 0;
}
