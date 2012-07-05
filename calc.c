/* calc.c */

#include <stdio.h>
#include <stdlib.h>

#include "forms.h"
#include "perms.h"
#include "rpn.h"

double compute(int size, unsigned int form, double_string *ds, counter *ops) {
   rpn_stack s = malloc(sizeof(rpn_stack));

   unsigned int shift = form;
   int ops_p = 0;
   double v = 0.0;

   int i = 0;
   for(i = 0 ; i < size; i++) {
      if((shift & 0x01) == 1) {
         rpn_push(&s, ds->value);
         ds = ds->next;
      } else {
         switch(ops->values[ops_p++]) {
            case 0 : v = rpn_calc(&s, '+'); break;
            case 1 : v = rpn_calc(&s, '-'); break;
            case 2 : v = rpn_calc(&s, '*'); break;
            case 3 : v = rpn_calc(&s, '/'); break;
         }
      }
      shift = shift >> 1;
   }
   rpn_destroy(s);
   return v;
}

double compute_verbose(int size, unsigned int form, double_string *ds, counter *ops) {
   rpn_stack s = malloc(sizeof(rpn_stack));

   unsigned int shift = form;
   int ops_p = 0;
   double v = 0.0;

   double p1, p2;

   int op_last = 0;

   int i = 0;
   for(i = 0 ; i < size; i++) {
      if((shift & 0x01) == 1) {
         rpn_push(&s, ds->value);
         ds = ds->next;
         op_last = 0;
      } else {
         switch(ops->values[ops_p++]) {
            case 0 : p1 = s->value;
                     p2 = s->p->value;
                     v = rpn_calc(&s, '+');
                     if(op_last == 0)
                        printf("%.2f + %.2f = %.2f\n", p1, p2, v);
                     else
                        printf("     + %.2f = %.2f\n", p2, v);
                     op_last = 1;
                     break;
            case 1 : p1 = s->value;
                     p2 = s->p->value;
                     v = rpn_calc(&s, '-');
                     if(op_last == 0)
                        printf("%.2f - %.2f = %.2f\n", p1, p2, v);
                     else
                        printf("     - %.2f = %.2f\n", p2, v);
                     op_last = 1;
                     break;
            case 2 : p1 = s->value;
                     p2 = s->p->value;
                     v = rpn_calc(&s, '*');
                     if(op_last == 0)
                        printf("%.2f * %.2f = %.2f\n", p1, p2, v);
                     else
                        printf("     * %.2f = %.2f\n", p2, v);
                     op_last = 1;
                     break;
            case 3 : p1 = s->value;
	             p2 = s->p->value;
                     v = rpn_calc(&s, '/');
                     if(op_last == 0)
                        printf("%.2f / %.2f = %.2f\n", p1, p2, v);
                     else
                        printf("     / %.2f = %.2f\n", p2, v);
                     op_last = 1;
                     break;
         }
      }
      shift = shift >> 1;
   }
   rpn_destroy(s);
   return v;
}
