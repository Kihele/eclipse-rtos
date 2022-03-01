/*
 ============================================================================
 Name        : pipes.c
 Author      : Paolo Torroni
 Version     :
 Copyright   : Use as you wish
 Description : Template for point 3 in RTSA lab#3
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for pipe
#include <signal.h> // for signals
#include <wait.h> // for wait

#define READ_END 0
#define WRITE_END 1

void sigpipe_handler(int signo) {
	puts(" -->o Got a SIGPIPE");
}

int compute_sum(int n) {
	int i,sum=0;
	for(i=0;i<n;i++,sum+=i);
	return sum;
}

int main(void) {
	int fd[2], // file descriptors for the pipe:
				   // fd[1] is the write-end of the pipe
				   // fd[0] is the read-end of the pipe
		buf=0, // 1-int-long buffer for parent/child communication
		child_pid; // for the fork system call

	signal(SIGPIPE,sigpipe_handler);

	/* put your code here */
	if(pipe(fd)<0){
		perror("Could not create pipe");
		exit(2);
	}




	child_pid=fork();
	if(child_pid<0) {
		perror("Could not fork child");
		exit(1);
	}
	else if(child_pid==0) //child
	{
		/* put your code here */
		//ONLY read FROM PIPE 1, CLOSE THE write END, 2, reaD AND 3 CLOSE THE Read END display terminate.
		close(fd[WRITE_END]);
		//buf (of type int) is my local buffer for reading from the pipe
		//depending on the number of bytes to be read> size of keyword.
		//size of is for only return type not the buff
		read(fd[READ_END], &buf, sizeof(int));
		close(fd[READ_END]);
		printf("child; %d\n", buf);
		//return 0 here is optional since exit success would be met afterward finally.
		// the child receives the computed value S from the parent, using a pipe,
		//then diplays that value on screen, and finally terminats
	}
	else //parent
	{
	int returnvalue; /* put your code here */
		//write sum to the pipe. onto "buf "; write "buf to the pipe
		//closing the read pipe 2.compute sum on s and  write 3 close the WRITE end.
		// the parent computes the sum  S of the first 10 integer numbers;
		// the parent waits for the child and then terminats.
	close(fd[READ_END]);
	buf = compute_sum(10);
   	returnvalue= write(fd[WRITE_END], &buf, sizeof(int));
	printf("parent writing %d", returnvalue);
   	close(fd[WRITE_END]);
	wait(NULL);

	}

	return EXIT_SUCCESS;
}
