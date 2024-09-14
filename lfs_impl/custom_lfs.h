//
// Created by amir on 9/8/2024.
//

#ifndef CUSTOM_LFS_H
#define CUSTOM_LFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../lfs/lfs.h"
#include "../lfs_impl/custom_lfs.h"


char* findFile(const char* file_name);

int block_device_read(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size);

int block_device_prog(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size);

int block_device_erase(const struct lfs_config *c, lfs_block_t block);

int block_device_sync(const struct lfs_config *cfg);

#endif //CUSTOM_LFS_H
