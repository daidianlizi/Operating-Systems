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
 char *argv[2]; 
 argv[0] = "ls";
 argv[1] = 0;
 if(fork() == 0)
 {
   close(1);
   int fid = open("y",O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR);
   //exec("/bin/ls", argv);
   execvp("ls", argv);
   close(fid);
   exit(0);
 }
}
