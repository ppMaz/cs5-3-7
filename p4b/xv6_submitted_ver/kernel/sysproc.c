#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"

int
sys_fork(void)
{
  return fork();
}
int
sys_clone(void){
  char *p;
  if(argptr(0,&p,4) < 0)
	return -1; 
  return clone((void*)p);
}
int
sys_lock(void){
	//TODO
	char *p;
	if(argptr(0,&p,4) < 0)
        	return -1;
	int *l = (int*)p;
	return lock(l);
}
int
sys_unlock(void){
	//TODO
	char *p;
	if(argptr(0,&p,4) < 0)
        	return -1;
	int *l = (int*)p;
	return unlock(l);
}
int
sys_join(void){
	return join();
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
sys_orphanage(void){
  int n;
  if(argint(0, &n) < 0)
	return -1;
  return orphanage(n);

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
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  acquire(proc->mem_lock_ptr);
  addr = proc->sz;
  if(growproc(n) < 0){
   	release(proc->mem_lock_ptr);
	 return -1;
 }
  release(proc->mem_lock_ptr);
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
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
