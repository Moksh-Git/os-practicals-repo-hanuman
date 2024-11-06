#include<sys/types.h> // for standard data types like key_t
#include<sys/ipc.h>   // for IPC_CREAT flag and key generation
#include<sys/shm.h>   // for shared memory functions
#include<stdio.h>     // for input-output functions
#include<stdlib.h>    // for exit function
#include<wait.h>      // for wait functions
#include<unistd.h>    // for sleep function

#define MAXSIZE 27    // This defines the size of the shared memory block as 27 bytes, which is enough to store 26 letters (A-Z) and a terminating character.
void die(char *s)     //if there’s an error (like failing to create shared memory), this function prints an error message and exits the program.
{
	perror(s);
	exit(1);
}

int main()
{
	char c;          
	int shmid;
	key_t key;
	char *shm,*s;
	
	key=5678;       //This is a unique identifier for the shared memory segment. Both client and server use the same key to access the same memory.
	
	if((shmid=shmget(key,MAXSIZE,IPC_CREAT|0666))<0)  /*shmget function creates the shared memory segment of size MAXSIZE with the specified key. IPC_CREAT tells the system to create the segment    												 if it doesn’t exist, and 0666 sets the permissions so both reading and writing are allowed.*/
		die("shmget");
		
	if((shm=shmat(shmid,NULL,0))==(char *)-1)  /*shmat function attaches the shared memory segment to the server's address space. shm is now a pointer to this memory area.*/
		die("shmat");
		
	s=shm;
	
	for(c='A';c<='Z';c++)  //Writing data to shared memory: This loop writes each letter from 'A' to 'Z' into the shared memory segment.
		*s++=c;
	
	while(*shm!='*')       //Waiting for the client to signal completion: The server waits until the client sets the first character in shared memory to '*', indicating that it has read the data.
		sleep(1);
		
	exit(0);
}
