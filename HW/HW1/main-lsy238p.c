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
 int pid = fork();
 if(pid == 0)
 {
   close(1);
   int fid = open("y",O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR);
   char *argv[2];
   argv[0] = "ls";
   argv[1] = 0;
   //exec("/bin/ls", argv);
   execvp("ls", argv);
   close(fid);
   exit(0);
 }
 else if( pid > 0)
 {
   pid = wait(0);
   exit(0);
 }
}
