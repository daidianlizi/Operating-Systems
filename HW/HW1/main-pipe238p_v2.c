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
  //ls |grep "main "|wc

 // create two pipes:
 int pid;
 int p1[2],p2[2];
 int stdout_cp = dup(1);
 if ( pipe(p1) == -1) printf("pipe error");
 if ( pipe(p2) == -1) printf("pipe error");
 char buf[1024]; 
 //create two sibling pid using fork:
 int i;
 for (i = 0; i < 2; i++){
    if ( (pid = fork()) == 0) break;
 }

 if( i == 0)   //big-brother
 {
   close(1);
   dup(p1[1]);
   close(p1[0]);
   //char *arg[] = {"ls", 0};
   //execvp(arg[0], arg);
   execlp("ls","ls",NULL);
 }
 else if(i == 1) //younger-bro
 {
   close(0);
   dup(p1[0]);
   close(p1[1]);

   close(1);// write for "grep",close read
   dup(p2[1]);
   close(p2[0]);
   char *arg[] = {"grep", "main", 0};
   execvp(arg[0], arg);
 }
 else 
 {
   close(p1[0]);
   close(p1[1]);
   close(0); //read for "wc",close write
   dup(p2[0]);
   close(p2[1]);
   dup2(stdout_cp, 1);
   close(stdout_cp);
   //int len = read(p2[0],buf,sizeof(buf));
   //write(1,buf,len);
   //char *argv[] = {"wc",0};
   //execvp(argv[0],argv);
   execlp("wc","wc");
   close(p2[0]);
 }
 exit(0);	
}
