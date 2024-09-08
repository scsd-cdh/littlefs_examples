cmake_minimum_required(VERSION 3.29)
project(c C)

set(CMAKE_C_STANDARD 11)

set(SOURCES main.c)

# Add LittleFS source files if they are included directly
set(LITTLEFS_SOURCES
        lfs/lfs.c
        lfs/lfs_util.c
        lfs_impl/custom_lfs.c
)

add_executable(${PROJECT_NAME} ${SOURCES} ${LITTLEFS_SOURCES})
