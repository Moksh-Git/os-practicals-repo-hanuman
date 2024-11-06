#include <stdio.h>
int required[100], allocate[100], need[100];
int main(){
 int n;
 int max = 12; // Total resources available
 int allocateCount = 0;
 printf("Enter the number of processes: \n");
 scanf("%d", &n);
 printf("Enter the required resources for each process:\n");
 for (int i = 0; i < n; i++) {
	 printf("Requirement for Process %d: ", i + 1);
	 scanf("%d", &required[i]);
 }
 printf("Enter the allocated resources for each process:\n");
 for (int i = 0; i < n; i++) {
 	printf("Allocation for Process %d: ", i + 1);
 	scanf("%d", &allocate[i]);
 	allocateCount += allocate[i]; 
 	need[i] = required[i] - allocate[i]; 
 }
 int available = max - allocateCount; 
 int count = n, sequence = 0;
 int ans[100], ind = 0;
 // Banker's Algorithm to check for safe state
 while (sequence < n) {
 	int found = 0; 
 	for (int j = 0; j < n; j++) {
 	if (need[j] != 0) { 
 	if (need[j] > available) {
 		continue; 
 	}
 	else {
 		ans[ind++] = j + 1;
 		sequence++;
 		available += allocate[j]; 
		need[j] = 0; 
 		found = 1; 
 	}
 }
}
 if (!found) {
 	break; 
 }
 }
 // Output results
 if (sequence == n) {
 printf("The system is in a safe state.\nSafe sequence: ");
 for (int i = 0; i < n; i++) {
 printf("P%d ", ans[i]);
 }
 printf("\n");
 } else {
 printf("The system is in an unsafe state.\n");
 }
 return 0;
}
