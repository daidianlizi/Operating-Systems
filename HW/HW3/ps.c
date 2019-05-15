#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

struct uproc {
	uint sz;
	enum procstate state;
	int pid;
	int parent_id;
	int chan;
	int killed;
	char name[16];
};


int main(int argc, char *argv[])
{
	printf(1, "%s\n", "now in ps");
	struct uproc p;
	struct uproc* up = &p;
	
	int pid = 0;
	printf(1, "%s\n", "pid   name  parent_id  mem_size   state      wait?    killed?");
	// loop through pid = 0 to INT_MAX
	do {
		pid++;
		if (getprocinfo(pid, up) == 0) {
			printf(1, "%s", "  ");
			printf(1, "%d\t", up->pid);
			printf(1, "%s\t", up->name);
			printf(1, "%d\t", up->parent_id);
			printf(1, "%d\t", up->sz);
			switch (up->state) {
				case UNUSED:
					printf(1, "%s\t", "UNUSED");
					break;
				case EMBRYO:
					printf(1, "%s\t", "EMBRYO");
					break;
				case SLEEPING:
					printf(1, "%s\t", "SLEEPING");
					break;
				case RUNNABLE:
					printf(1, "%s\t", "RUNNABLE");
					break;
				case RUNNING:
					printf(1, "%s\t\t", "RUNNING");
					break;
				case ZOMBIE:
					printf(1, "%s\t", "ZOMBIE");
			}
			
			if (up->chan == 0)
				printf(1, "%s\t", "No");
			else
				printf(1, "%s\t", "Yes");
			if (up->killed == 0)
				printf(1, "%s\t", "No");
			else
				printf(1, "%s\t", "Yes");
				
			printf(1, "\n");
			
		}
	} while (pid != 5);
	
	printf(1, "%s\n", "loop finishes");
	exit();
}
