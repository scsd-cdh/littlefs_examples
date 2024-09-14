#include "custom_lfs.h"

// Function to find the file and return the full path
char* findFile(const char* file_name) {
    // Get the current working directory
    char cwd[1024] = {};
    if (GetCurrentDirectory(sizeof(cwd), cwd) == 0) {
        printf("GetCurrentDirectory() error\n");
        return NULL;
    }

    // Remove Build file
    char *last_separator = strrchr(cwd, '\\');
    if (last_separator) {
        *last_separator = '\0'; // Replace the last separator with null terminator
    }

    // Calculate the length of the full path
    size_t cwd_len = strlen(cwd);
    size_t file_name_len = strlen(file_name);
    size_t full_path_len = cwd_len + file_name_len + 2; // +2 for PATH_SEPARATOR and null terminator

    // Allocate memory for the full path
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        perror("malloc() error");
        return NULL;
    }

    // Construct the full path
    snprintf(full_path, full_path_len, "%s\\%s", cwd, file_name);

    return full_path;
}

int block_device_read(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size) {
    // Calculate the file offset (block index * block size + offset within block)
    size_t file_offset = block * cfg->block_size + off;

    char *full_path = findFile("my_file.txt");
    if (!full_path) {
        perror("findFile() error");
        return -1;
    }

    FILE *file = fopen(full_path, "rb");
    free(full_path);

    if (!file) {
        perror("Failed to open file for reading");
        return -1;
    }

    fseek(file, file_offset, SEEK_SET);

    // Read the data into the buffer
    size_t bytesRead = fread(buffer, 1, size, file);
    if (bytesRead != size) {
        if (feof(file)) {
            printf("End of file reached.\n");
        } else {
            perror("Failed to read the expected amount of data");
        }
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
}

int block_device_prog(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size) {
    char *full_path = findFile("my_file.txt");
    if (!full_path) {
        perror("findFile() error");
        return -1;
    }

    FILE *file = fopen(full_path, "r+b");
    free(full_path);

    if (!file) {
        perror("Failed to open file for writing");
        return -1;
    }

    fseek(file, block * cfg->block_size + off, SEEK_SET);

    // Read the data into the buffer
    size_t bytesRead = fread(buffer, 1, size, file);
    if (bytesRead != size) {
        if (feof(file)) {
            printf("End of file reached.\n");
        } else {
            perror("Failed to read the expected amount of data");
        }
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
}

// Corrected block_device_erase function
int block_device_erase(const struct lfs_config *cfg, lfs_block_t block) {
    char *full_path = findFile("my_file.txt");
    if (!full_path) {
        perror("findFile() error");
        return -1;
    }

    FILE *file = fopen(full_path, "r+b");
    free(full_path);

    if (!file) {
        perror("Failed to open file for erasing");
        return -1;
    }

    // Seek to the start of the block
    if (fseek(file, block * cfg->block_size, SEEK_SET) != 0) {
        perror("Failed to seek to block");
        fclose(file);
        return -1;
    }

    // Create an empty buffer to simulate erased block
    char *empty = (char *)calloc(cfg->block_size, 1);
    if (!empty) {
        perror("Failed to allocate memory for empty buffer");
        fclose(file);
        return -1;
    }

    // Write the empty buffer to the block
    size_t written = fwrite(empty, 1, cfg->block_size, file);
    if (written != cfg->block_size) {
        perror("Failed to write the full block");
        free(empty);
        fclose(file);
        return -1;
    }

    // Clean up and close the file
    free(empty);
    fclose(file);
    return 0;
}

int block_device_sync(const struct lfs_config *cfg) {
    // No operation needed for file-based simulation
    return 0;
}
