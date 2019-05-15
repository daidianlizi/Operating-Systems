#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  /* Insert your code here */
  //buf maybe too limited?
  char buf[1024];
  char *sf = argv[1];
  char *tf = argv[2];
  int sfid = open(sf,O_RDONLY);
  int n = read(sfid, buf, sizeof buf);
  printf("bytes: %d", n);
  int tfid = open(tf,O_CREAT|O_WRONLY);
  write(tfid,buf,n);
  close(sfid);
  close(tfid);
  exit(0);
}
