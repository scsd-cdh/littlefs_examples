# LittleFS Test

This document provides a sample code for running LittleFS. It is planned to be the file system for the SC-Freyer project.

## Usage

To implement LittleFS, the following functions need to be provided:

- `read`
- `prog`
- `erase`
- `sync`


In the `lfs_impl` folder, you will find four pre-implemented versions of LittleFS, along with one custom implementation.

## Deployment

Before deploying LittleFS in the `Hades` repository, drivers for MRAM chips must be built. Once the drivers are ready, specific implementations of LittleFS can be applied based on the project's needs.






