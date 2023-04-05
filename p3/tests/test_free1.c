// a few allocations in multiples of 4 bytes followed by frees
#include <assert.h>
#include <stdlib.h>
#include "p3Heap.h"

int main()
{
   assert(init_heap(4096) == 0);
   void *ptr[4];
   ptr[0] = balloc(4);
   ptr[1] = balloc(8);

   assert(bfree((void *)ptr[0] - 1) == -1);
   assert(bfree(NULL) == -1);
   assert(bfree((void *)ptr[0] + 4084) == -1);
   assert(bfree((void *)ptr[0] + 4083) == -1);
   assert(bfree((void *)ptr[0] + 4082) == -1);
   assert(bfree((void *)ptr[0] + 4081) == -1);
   disp_heap();

   assert(bfree(ptr[0]) == 0);
   assert(bfree(ptr[1]) == 0);
   disp_heap();

   ptr[2] = balloc(16);
   ptr[3] = balloc(4);
   disp_heap();

   assert(bfree(ptr[2]) == 0);
   assert(bfree(ptr[3]) == 0);
   assert(bfree(ptr[2]) == -1);
   assert(bfree(ptr[3]) == -1);
   disp_heap();

   exit(0);
}
