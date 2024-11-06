#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void sort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter %d elements of the array: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Sort the array
    sort(arr, n);

    // Display the sorted array in ascending order
    printf("Ascending sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Create a child process using fork
    pid_t pid = fork();

    if (pid == 0) {
        // Child process: pass sorted array to another program using execve
        char *args[n + 2];
        args[0] = "./2b2";  // Assuming 2b2 is the compiled executable for the second program
        for (int i = 0; i < n; i++) {
            args[i + 1] = malloc(10 * sizeof(char)); 
            snprintf(args[i + 1], 10, "%d", arr[i]); 
        }
        args[n + 1] = NULL;  // Mark the end of arguments

        execve(args[0], args, NULL);  // Replace the process with ./2b2
        perror("execve failed");  // Error if execve fails
        exit(1);
    } else if (pid > 0) {
        // Parent process: wait for the child process to complete
        wait(NULL);
    } else {
        perror("fork failed");  // Error if fork fails
        exit(1);
    }

    return 0;
}
