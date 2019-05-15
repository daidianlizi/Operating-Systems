Q1:
syscall.c 
	extern int sys_backtrace(void);
	[SYS_backtrace]   sys_backtrace,
//hint suggest implement the body of the backtrace() system call in [syscall.c], 
//but mine in sysproc.c
syscall.h
	#define SYS_backtrace 22
sysproc.c
	int sys_backtrace(void){...} //mainbody
def.h
	int sys_backtrace(void);
	
//--------------------
create bt.c
Makefile: UPROGS + 
user.h
	int backtrace(void);
usys.S 
	SYSCALL(backtrace)



//=======================================================//
//=======================================================//
Q2:
syscall.c 
	extern int sys_getprocinfo(void);
	[SYS_getprocinfo] sys_getprocinfo,
syscall.h
	#define SYS_getprocinfo  23
sysproc.c
	int sys_getprocinfo(void){...} 
	//call of mainbody & 
proc.h
	struct uproc {...};
	//define, match in sysproc.c
def.h
	struct uproc;
	int getprocinfo(int, struct uproc*);

//--------------------
create ps.c
Makefile: UPROGS +  
user.h
	int getprocinfo(int, void*);
usys.S 
	SYSCALL(getprocinfo)


