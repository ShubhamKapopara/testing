#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage_mgr.h"

#define PAGE_SIZE 4096

FILE *filePointer; // Global file pointer

void initStorageManager(void) {
    // Initialize the global file pointer to NULL.
    printf("Storage manager initialized.\n");
    printf("Creators:\n");
    printf("Yash Patel [A20547099]\n");
    printf("Denish Asodariya [A20525465]\n");
    printf("Devarshi Patel [A20553154]\n");
    printf("Helee Patel [A20551881]\n");
    filePointer = NULL;
}

RC createPageFile(char *fileName) {
    // Create a new page file with the given name.
    // Initialize it with a single empty page.
    FILE *fp = fopen(fileName, "wb");
    if (fp == NULL) {
        // Return a failure message if the file cannot be created.
        return RC_FILE_NOT_FOUND;
    }

    // Use fwrite to create an empty page.
    char emptyPage[PAGE_SIZE] = {0};
    fwrite(emptyPage, sizeof(char), PAGE_SIZE, fp);

    // Close the file.
    fclose(fp);

    // Return success.
    return RC_OK;
}

RC openPageFile(char *fileName, SM_FileHandle *fHandle) {
    // Open an existing page file and initialize its file handle.
    FILE *fp = fopen(fileName, "rb");
    if (fp == NULL) {
        // Return an error message if the file cannot be opened.
        return RC_FILE_NOT_FOUND;
    }

    // Set fields of fHandle.
    fHandle->fileName = strdup(fileName);
    fHandle->curPagePos = 0;
    fseek(fp, 0, SEEK_END);
    fHandle->totalNumPages = ftell(fp) / PAGE_SIZE;
    fclose(fp);

    // Return success.
    return RC_OK;
}

RC closePageFile(SM_FileHandle *fHandle) {
    free(fHandle->fileName); // Free the dynamically allocated fileName.
    fHandle->fileName = NULL;
    return RC_OK;
}

RC destroyPageFile(char *fileName) {
    if (remove(fileName) == 0) {
        return RC_OK;
    } else {
        // Return an error message if the file does not exist.
        return RC_FILE_NOT_FOUND;
    }
}

RC readBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage) {
    if (pageNum >= fHandle->totalNumPages || pageNum < 0) {
        // Return an error if the requested page is out of bounds.
        return RC_READ_NON_EXISTING_PAGE;
    }

    FILE *fp = fopen(fHandle->fileName, "rb");
    if (fp == NULL) {
        // Return an error message if the file cannot be opened.
        return RC_FILE_NOT_FOUND;
    }

    // Use fseek to move to the desired page and fread to read it.
    fseek(fp, pageNum * PAGE_SIZE, SEEK_SET);
    fread(memPage, sizeof(char), PAGE_SIZE, fp);
    fHandle->curPagePos = ftell(fp);
    fclose(fp);

    // Return success.
    return RC_OK;
}

int getBlockPos(SM_FileHandle *fHandle) {
    // Return the current page position.
    return fHandle->curPagePos / PAGE_SIZE;
}

RC readFirstBlock(SM_FileHandle *fHandle, SM_PageHandle memPage) {
    
    if (fHandle == NULL)
    {
        return RC_FILE_NOT_FOUND;
    }
    else{
        if(fHandle->totalNumPages <= 0)
            return RC_READ_NON_EXISTING_PAGE;
        else{
            FILE *file;
            file = fopen(fHandle->fileName, "r");
            //going to first block
            fseek(file,0,SEEK_SET);
            fread(memPage,1,PAGE_SIZE,file);
            fHandle->curPagePos = 0;
            fclose(file);
            return RC_OK;
        }
    }
}

RC readPreviousBlock(SM_FileHandle *fHandle, SM_PageHandle memPage) {
    if (fHandle->curPagePos <= 0) {
        return RC_READ_NON_EXISTING_PAGE;
    }
    //going to previousblock
    return readBlock(fHandle->curPagePos - 1, fHandle, memPage);
}

RC readCurrentBlock(SM_FileHandle *fHandle, SM_PageHandle memPage) {
    //for reading currentblock
    return readBlock(fHandle->curPagePos, fHandle, memPage);
}

RC readNextBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)
{
	if (fHandle->curPagePos >= fHandle->totalNumPages - 1)
	{
		return RC_READ_NON_EXISTING_PAGE;
	}
    //for nextblock
	return readBlock(fHandle->curPagePos + 1, fHandle, memPage);
}

RC readLastBlock(SM_FileHandle *fHandle, SM_PageHandle memPage)
{
	if (RC_OK == readBlock(fHandle->totalNumPages - 1, fHandle, memPage))
		return RC_OK;
	else
		return RC_READ_NON_EXISTING_PAGE;
}

RC writeBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage) {
    if (pageNum >= fHandle->totalNumPages || pageNum < 0) {
        // Return an error if the requested page is out of bounds.
        return RC_WRITE_FAILED;
    }

    FILE *fp = fopen(fHandle->fileName, "rb+");
    if (fp == NULL) {
        // Return an error message if the file cannot be opened.
        return RC_FILE_NOT_FOUND;
    }

    // Use fseek to move to the desired page and fwrite to write to it.
    fseek(fp, pageNum * PAGE_SIZE, SEEK_SET);
    fwrite(memPage, sizeof(char), PAGE_SIZE, fp);
    fHandle->curPagePos = ftell(fp);
    fclose(fp);

    return RC_OK;
}

RC writeCurrentBlock(SM_FileHandle *fHandle, SM_PageHandle memPage) {
    int currentPage = getBlockPos(fHandle);
    return writeBlock(currentPage, fHandle, memPage);
}

RC appendEmptyBlock(SM_FileHandle *fHandle) {
    char emptyPage[PAGE_SIZE] = {0};
    FILE *fp = fopen(fHandle->fileName, "ab");
    if (fp == NULL) {
        // Return an error message if the file cannot be opened.
        return RC_FILE_NOT_FOUND;
    }
    fwrite(emptyPage, sizeof(char), PAGE_SIZE, fp);
    fclose(fp);
    fHandle->totalNumPages++;

    return RC_OK;
}

RC ensureCapacity(int numberOfPages, SM_FileHandle *fHandle) {
    if (numberOfPages > fHandle->totalNumPages) {
        FILE *fp = fopen(fHandle->fileName, "ab");
        if (fp == NULL) {
            // Return an error message if the file cannot be opened.
            return RC_FILE_NOT_FOUND;
        }
        char emptyPage[PAGE_SIZE] = {0};
        int newBlocks = numberOfPages - fHandle->totalNumPages;
        for (int i = 0; i < newBlocks; i++) {
            fwrite(emptyPage, sizeof(char), PAGE_SIZE, fp);
        }
        fclose(fp);
        fHandle->totalNumPages += newBlocks;

        // Return success.
        return RC_OK;
    } else {
        // Return an error if the requested capacity is not greater than the current capacity.
        return RC_READ_NON_EXISTING_PAGE;
    }
}