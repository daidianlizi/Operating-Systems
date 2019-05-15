#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(void)
{
  /* Insert your code here */
  // the goal of this scripts is equal to: 
 // ls |grep "main"|wc

 // create two pipes:
 int pid;
 int p1[2],p2[2];
 if ( pipe(p1) == -1) {
	 fprintf(stderr, "Pipe Error.\n");
	 exit(1);
 }
	 
 if ( pipe(p2) == -1) {
	 fprintf(stderr, "Pipe Error.\n");
	 exit(1);
 }
 //create two sibling pid using fork:
 int i;
 for (i = 0; i < 2; i++){
    if ( (pid = fork()) == 0) break;
 }

 if( i == 0)   //bigger sibling
 {
   //printf("exec in pid = 0\n");
   close(1); // write for "ls", close read.
   dup(p1[1]);
   close(p1[0]);
   //char *argv[] = {"ls",0};
   //execvp(argv[0],argv);
   execlp("ls","ls",NULL);
   //delete the other pipes
 }
 else if(i == 1) //younger sibling
 {
   //printf("exec in pid = 1\n");
   close(0); // read for "ls", close write
   dup(p1[0]);
   close(p1[1]);
   //delete p1's other pipe

   close(1);// write for "grep",close read
   dup(p2[1]);
   close(p2[0]);
   //char *argv[] = {"grep","main",0};
   //execvp(argv[0],argv);
   execlp("grep","grep","main",NULL);
 }
 else 
 {
   //printf("come to parent\n");
   //printf("exec in parent\n");
   close(p1[0]);
   close(p1[1]);
   close(0); //read for "wc",close write
   dup(p2[0]);
   close(p2[1]);
   //char *argv[] = {"wc",0};
   //execvp(argv[0],argv);
   execlp("wc","wc",NULL);
   close(p2[0]);
   for(i = 0; i < 2; i++){
      wait(NULL);
   }
 }	
}
