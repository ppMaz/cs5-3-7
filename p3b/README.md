---
Author: Xuyi Ruan  
Date:   10/27/2014  
Course: CS537  

---
##p3b partA:
Null-pointer Derefernece

TODO:  
1. check 'fork() and exec()' function    
2. change how programs are loaded so that it will not start @0x00  
3. make sure segfault(display err) when some tries to access @0x00  

Steps:
1. in kernel/exec.c, i chanted sz = 0 to sz= PGSIZE  
2. in kernel/vm.c, i changed i = 0 to i = PGSIZE  
3. in user/makefile.mk, changed ox0 to 0x1000  

Dont forget to 'make clean' after you make changes!
---
##p3b_partB:
Stack Rearrangement



