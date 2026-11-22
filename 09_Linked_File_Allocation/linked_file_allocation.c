
#include <stdio.h>

#define MAX_BLOCKS 50
#define MAX_FILES 10

int disk[MAX_BLOCKS];
int fileCount = 0;

struct File {
    int fileID;
    int startBlock;
    int endBlock;
    int blockCount;
    int blocks[MAX_BLOCKS];
};

struct File files[MAX_FILES];

void allocateFile() {
    int id, count;

    if (fileCount == MAX_FILES) {
        printf("Maximum number of files reached.\n");
        return;
    }

    printf("Enter file ID: ");
    scanf("%d", &id);

    for (int i = 0; i < fileCount; i++) {
        if (files[i].fileID == id) {
            printf("File ID already exists.\n");
            return;
        }
    }

    printf("Enter number of blocks required: ");
    scanf("%d", &count);

    if (count <= 0 || count > MAX_BLOCKS) {
        printf("Invalid block count.\n");
        return;
    }

    int selected[MAX_BLOCKS];
    int available = 0;

    printf("\nAvailable blocks:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (disk[i] == 0) {
            printf("%d ", i);
            available++;
        }
    }
    printf("\n");

    if (available < count) {
        printf("Not enough free blocks.\n");
        return;
    }

    printf("Enter %d distinct block numbers:\n", count);

    for (int i = 0; i < count; i++) {
        int block;
        scanf("%d", &block);

        if (block < 0 || block >= MAX_BLOCKS ||
            disk[block] != 0) {
            printf("Invalid or already allocated block. Try again.\n");
            i--;
            continue;
        }

        int duplicate = 0;
        for (int j = 0; j < i; j++) {
            if (selected[j] == block) {
                duplicate = 1;
                break;
            }
        }

        if (duplicate) {
            printf("Duplicate block. Enter another block.\n");
            i--;
            continue;
        }

        selected[i] = block;
    }

    struct File *f = &files[fileCount];

    f->fileID = id;
    f->startBlock = selected[0];
    f->endBlock = selected[count - 1];
    f->blockCount = count;

    for (int i = 0; i < count; i++) {
        f->blocks[i] = selected[i];
        disk[selected[i]] = 1;
    }

    fileCount++;

    printf("\nFile allocated successfully.\n");
    printf("Linked block sequence:\n");

    for (int i = 0; i < count; i++) {
        printf("[%d] -> ", selected[i]);
    }
    printf("NULL\n");
}

void displayFiles() {
    if (fileCount == 0) {
        printf("No files allocated.\n");
        return;
    }

    printf("\n--- FILE ALLOCATION TABLE ---\n");

    for (int i = 0; i < fileCount; i++) {
        printf("\nFile ID: %d\n", files[i].fileID);
        printf("Start Block: %d\n", files[i].startBlock);
        printf("End Block: %d\n", files[i].endBlock);
        printf("Number of Blocks: %d\n", files[i].blockCount);

        printf("Block Chain: ");
        for (int j = 0; j < files[i].blockCount; j++) {
            printf("%d -> ", files[i].blocks[j]);
        }
        printf("NULL\n");
    }
}

void displayDisk() {
    printf("\n--- DISK BLOCK STATUS ---\n");
    printf("Block\tStatus\n");

    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("%d\t%s\n", i,
               disk[i] == 0 ? "Free" : "Allocated");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n===== LINKED FILE ALLOCATION =====\n");
        printf("1. Allocate file\n");
        printf("2. Display allocated files\n");
        printf("3. Display disk status\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                allocateFile();
                break;
            case 2:
                displayFiles();
                break;
            case 3:
                displayDisk();
                break;
            case 4:
                printf("Program terminated.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}
