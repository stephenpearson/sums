/* rpn.h */

#ifndef _RPN_H
#define _RPN_H

typedef struct _rpn_stack {
   double value;
   struct _rpn_stack *p;
} *rpn_stack;

void rpn_push(rpn_stack *stack, double value);
double rpn_pop(rpn_stack *stack);
void rpn_dump(rpn_stack *stack);
double rpn_calc(rpn_stack *stack, char oper);
void rpn_destroy(rpn_stack stack);

#endif
