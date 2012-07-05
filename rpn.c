/* rpn.c */

#include <stdlib.h>
#include <stdio.h>
#include "rpn.h"

void rpn_push(rpn_stack *stack, double value) {
   rpn_stack tmp = malloc(sizeof(rpn_stack));
   if(*stack != NULL)
     tmp->p = *stack;
   else
     tmp->p = NULL;
   tmp->value = value;
   *stack = tmp;
}

double rpn_pop(rpn_stack *stack) {
   if(*stack == NULL) {
      printf("Stack empty\n");
      return 0;
   }
   double value = (*stack)->value;
   rpn_stack tmp = (*stack)->p;
   free(*stack);
   *stack = tmp;
   return value;
}

void rpn_dump(rpn_stack *stack) {
   rpn_stack tmp = *stack;
   int i = 1;
   while(tmp != NULL) {
      printf("%d:  %.2f", i, tmp->value);
      if(i++ == 1)
         printf("   <-- TOS\n");
      else
         printf("\n");
      tmp = tmp->p;
   }
   printf("\n");
}

double rpn_calc(rpn_stack *stack, char oper) {
   double v1 = 0;
   double v2 = 0;
   double value = 0;

   v1 = rpn_pop(stack);
   v2 = rpn_pop(stack);

   switch(oper) {
      case '+' : value = v1 + v2; break;
      case '-' : value = v1 - v2; break;
      case '*' : value = v1 * v2; break;
      case '/' : value = v1 / v2; break;
   }

   rpn_push(stack, value);
   return value;
}

void rpn_destroy(rpn_stack stack) {
   while(stack != NULL) {
      rpn_stack next = stack->p;
      free(stack);
      stack = next;
   }
}
