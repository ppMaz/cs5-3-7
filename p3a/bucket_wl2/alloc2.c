/* a few aligned allocations */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
   assert(Mem_Init(4096) == 0);
   assert(Mem_Alloc(80) != NULL);
   assert(Mem_Alloc(16) != NULL);
   assert(Mem_Alloc(256) != NULL);
   assert(Mem_Alloc(80) != NULL);
   exit(0);
}
