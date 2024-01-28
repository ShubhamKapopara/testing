# Storage Manager CS-525 Assignment 1

## Introduction
The Storage Manager is a module designed to manage files on disk and provide operations for reading and writing blocks of data. This module deals with pages (blocks) of a fixed size (PAGE_SIZE), and it is a fundamental component of many database systems. This README provides an overview of the Storage Manager project, its functionalities, and how to use it.

## Group Members

- Yash Patel - [A20547099]
- Devarshi Patel - [A20553154]
- Helee Patel - [A20551881]
- Denish Asodariya - [A20525465]

### Aim
The goal of this assignment is to implement a storage manager capable of performing the following tasks:
- Creating, opening, and closing files.
- Reading blocks from a file into memory.
- Writing blocks from memory to a file.
- Navigating through blocks (e.g., moving to the next or previous block).
- Ensuring file capacity to accommodate a specified number of pages.

## Code running instructions
- Step 1: `make`
- Step 2: `./test1`
- Step 3: `make clean`

## About Test Cases

## Functions
The Storage Manager provides the following functions:

### Initialization
- ***void initStorageManager***: Initializes the storage manager.  `Author: Yash Patel`

### File Operations
- ***createPageFile***: Creates a new page file with the given name and initializes it with a single empty page.  `Author: Yash Patel`
- ***openPageFile***: Opens an existing page file and initializes its file handle.  `Author: Yash Patel`
- ***closePageFile***: Closes the opened file.  `Author: Yash Patel`
- ***destroyPageFile***: Removes the existing page file.  `Author: Devarshi Patel`

### Block Operations
- ***readBlock***: Reads a specific block into memory.  `Author: Devarshi Patel`
- ***getBlockPos***: Returns the current page position.  `Author: Devarshi Patel`
- ***readFirstBlock***: Reads the first block of the file into memory.  `Author: Devarshi Patel`
- ***readPreviousBlock***: Reads the previous block relative to the current page into memory.  `Author: Helee Patel`
- ***readCurrentBlock***: Reads the current block into memory.  `Author: Helee Patel`
- ***readNextBlock***: Reads the next block relative to the current page into memory.  `Author: Helee Patel`
- ***readLastBlock***: Reads the last block of the file into memory.  `Author: Helee Patel`
- ***writeBlock***: Writes a block from memory to a specific page.  `Author: Denish Asodariya`
- ***RC writeCurrentBlock***: Writes the current block from memory to its current position.  `Author: Denish Asodariya`
- ***appendEmptyBlock***: Appends an empty block to the end of the file.  `Author: Denish Asodariya`

### Capacity Management
- ***RC ensureCapacity***: Ensures that the file has a minimum capacity of 'numberOfPages' by appending empty blocks if necessary.  `Author: Denish Asodariya`

## Conclusion
The Storage Manager module provides essential file management and block manipulation functionalities, making it a valuable tool for database systems and file handling applications. You can use the provided functions to create, open, read, and write to page files efficiently.