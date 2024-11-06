#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Function for selection sort
void selectionSort(int arr[], int n) {
    int i, j, minIdx, temp;
    for (i = 0; i < n - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        // Swap the found minimum element with the first element
        temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

// Function for bubble sort
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements if they are in the wrong order
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    pid_t pid;
    int parentArray[] = {64, 34, 25, 12, 22, 11, 90};  // Array for parent (bubble sort)
    int childArray[] = {29, 10, 14, 37, 13, 40, 8};   // Array for child (selection sort)
    int parentSize = sizeof(parentArray) / sizeof(parentArray[0]);
    int childSize = sizeof(childArray) / sizeof(childArray[0]);

    pid = fork();  // Create child process

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process - performs Selection Sort
        printf("Child Process (Selection Sort):\n");
        printf("Before sorting: ");
        printArray(childArray, childSize);
        
        selectionSort(childArray, childSize);
        
        printf("After sorting: ");
        printArray(childArray, childSize);
        
        // Creating a pause to keep the child process alive (orphan example)
        sleep(10);
        
        printf("Child process completed.\n");
        exit(0);  // Exit child process
    }
    else {
        // Parent process - to create a zombie process
        printf("Parent process sleeping for 5 seconds to create zombie state.\n");
        sleep(5);  // Delay to create a zombie state

        printf("\nParent Process (Bubble Sort):\n");
        printf("Before sorting: ");
        printArray(parentArray, parentSize);
        
        bubbleSort(parentArray, parentSize);
        
        printf("After sorting: ");
        printArray(parentArray, parentSize);
        
        // Wait for the child process to prevent it from becoming a zombie
        wait(NULL);
        printf("Parent process finished.\n");
    }

    return 0;
}
