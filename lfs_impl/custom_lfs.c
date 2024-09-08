//
// Created by amir on 9/8/2024.
//

#include <stdio.h>
#include "custom_lfs.h"

int block_device_read(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size){

    FILE *file = fopen("littlefs_flash.img", "rb");
    if(!file){
        return -1;
    }

    fseek(file, block * cfg->block_size + off, SEEK_SET);

    size_t res = fread(buffer, 1, size, file);
    fclose(file);

    return (res == size) ? 0 : -1;
}

int block_device_erase(const struct lfs_config *cfg, lfs_block_t block) {
    FILE *file = fopen("littlefs_flash.img", "rb+");
    if (!file) {
        return -1; // Failed to open the file
    }

    // Seek to the block's start position
    fseek(file, block * cfg->block_size, SEEK_SET);

    // Write zeros to the entire block (simulate erase)
    char empty[4096] = {0};  // Adjust size to fit your block size
    for (int i = 0; i < cfg->block_size / sizeof(empty); i++) {
        fwrite(empty, sizeof(empty), 1, file);
    }

    fclose(file);
    return 0;
}

int block_device_sync(const struct lfs_config *cfg) {
    return 0;
}

int block_device_prog(const struct lfs_config *cfg, lfs_block_t block,
                      lfs_off_t off, const void *buffer, lfs_size_t size) {
    FILE *file = fopen("littlefs_flash.img", "rb+");
    if (!file) {
        return -1; // Failed to open the file
    }

    // Calculate the file offset (block index * block size + offset within block)
    fseek(file, block * cfg->block_size + off, SEEK_SET);

    // Write data from the buffer to the file
    size_t res = fwrite(buffer, 1, size, file);
    fclose(file);

    // Return 0 on success, or a negative error code if something went wrong
    return (res == size) ? 0 : -1;
}