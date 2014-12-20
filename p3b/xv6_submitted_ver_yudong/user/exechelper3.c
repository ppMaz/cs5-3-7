/* stack should not grow into heap (program must terminate) */
#include "types.h"
#include "user.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE 4096
#define PGROUNDUP(sz) (((sz)+PGSIZE-1) & ~(PGSIZE-1))

#define assert(x) if (x) {} else { \
  printf(1, "%s: %d ", __FILE__, __LINE__); \
  printf(1, "assert failed (%s)\n", # x); \
  printf(1, "TEST FAILED\n"); \
  exit(); \
}

void
growstack(int n) 
{
  char filler[4096];
  filler[0] = filler[0]; // must use or compiler error...
  if(n > 1)
    growstack(n-1);
}

int
main(int argc, char *argv[])
{
  //Called with 5 page for max stack
  printf(1, " EC 3 before grow 4\n"); 
  // should succeed
  growstack(4);
  printf(1, " EC 3TEST PASSED\n");

  int pid = fork();
  if(pid == 0) {
    // should fail
    growstack(5);
    printf(1, "TEST FAILED\n");
    exit();
  } else {
    wait();
  }

  exit();
}
