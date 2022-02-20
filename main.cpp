#include <stdio.h>
#include <stdlib.h>
#include "include/queue.h"


int main() 
{
   queue me = {};
   queue_ctor(&me);
   int a = 3;
   push_head(&me, 5);
   push_head(&me, 7);
   //pop_tail(&me, &a);
   //pop_tail(&me, &a);
   queue_dump(&me);
   pop_tail(&me, &a);
   printf("%d\n", a);
   return 0;
}