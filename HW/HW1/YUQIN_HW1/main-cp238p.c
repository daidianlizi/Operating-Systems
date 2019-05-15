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
  if (sfid == -1) {
  	fprintf(stderr, "Source File open failed.\n");
	exit(1);
  }
  int tfid = open(tf, O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR);
  if (tfid == -1) {
     fprintf(stderr, "Target File open failed.\n");
     exit(1);
  }
  int nflag;
  while ( (nflag = read(sfid, buf, sizeof buf)) > 0){
  	//printf("bytes: %d\n", nflag);
	write(tfid,buf,nflag);
  }
  close(sfid);
  close(tfid);
  exit(0);
  //return 0;
}
