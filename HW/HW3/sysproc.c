#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


//backtrace
int read_ebp(void)
{
    int my_ebp;
    __asm __volatile("movl (%%ebp), %0":"=r"(my_ebp));
    return my_ebp;
}

int read_eip(void)
{
  int my_eip;
  __asm __volatile("movl 4(%%ebp), %0" : "=r" (my_eip));
  return my_eip;
}

//1.the system call prints all registers of the user program, 
//2.walks the stack frame by frame printing the return addresses saved on the stack on the console.
int
sys_backtrace(void)
{
  cprintf("test_backtrace\n");
  uint ebp, eip, last_ebp, retaddr;
  //uint arg0, arg1, arg2, arg3, arg4;
  uint i = 0;
  ebp = (uint)read_ebp();
  eip = (uint)sys_backtrace;//(uint)read_eip();//
  struct proc* current_p = myproc();
  struct trapframe* current_tf = current_p->tf;
  uint current_eax, current_ebx, current_ecx, current_edx, current_edi, current_esi, current_eflags, current_esp;
  ushort current_cs;
  current_eax = current_tf->eax;
  current_ebx = current_tf->ebx;
  current_ecx = current_tf->ecx;
  current_edx = current_tf->edx;
  current_edi = current_tf->edi;
  current_esi = current_tf->esi;
  current_eflags = current_tf->eflags;
  current_cs = current_tf->cs;
  current_esp = current_tf->esp;
  cprintf("eax:0x%x\nebx:0x%x\necx:0x%x\nedx:0x%x\nedi:0x%x\nesi:0x%x\neflags:0x%x\ncs:0x%x\nesp:0x%x\neip:0x%x\nebp:0x%x\n", current_eax, current_ebx, current_ecx, current_edx, current_edi, current_esi, current_eflags, current_cs, current_esp, eip, ebp);

  while( eip != 0xffffffff ) //eip<?
  {
    last_ebp  = *(uint *)ebp;
    retaddr = *(uint *)(ebp+4);
    /*
    arg0 = *(uint *)(ebp + 8);
    arg1 = *(uint *)(ebp + 12);
    arg2 = *(uint *)(ebp + 16);
    arg3 = *(uint *)(ebp + 20);
    arg4 = *(uint *)(ebp + 24);
    cprintf("ebp %x eip %x args %x %x %x %x %x\n", ebp, eip, arg0, arg1, arg2, arg3, arg4);
    */
    ebp = last_ebp;
    eip = retaddr;
    //cprintf("#%x  0x%x\n", i, eip);
    cprintf("#%x  eip:0x%x, ebp:0x%x\n", i, eip, ebp);
    i++;
  }
 return 0;
}


//ps tool

int getprocinfo(int proc_num, struct uproc* up)
{
  struct proc* p;
  for (p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if (p->pid == proc_num) {
      up->pid = p->pid;
      up->sz = p->sz;
      up->state = p->state;
      up->killed = p->killed;
      up->parent_id = (int)p->parent == 0 ? 0 : p->parent->pid;
      up->chan = (int)p->chan != 0 ? 1 : 0;
      safestrcpy(up->name, p->name, sizeof(p->name));
      return 0;
    }
  }
  return -1;
}

int sys_getprocinfo(void)
{
  int proc_num;
  char* up;
  if (argint(0, &proc_num) < 0)
      cprintf("%s\n", "argint(pid) error");
  if (argptr(1, &up, 4) < 0)
      cprintf("%s\n", "argptr(up) error");
  return  getprocinfo(proc_num, (struct uproc*)up) == 0 ? 0 : -1;
}
