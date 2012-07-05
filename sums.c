/* sums.c */

#include <stdio.h>
#include <stdlib.h>
#include "rpn.h"
#include "calc.h"
#include "forms.h"
#include "perms.h"

int main(int argc, char *argv[]) {
   int i = 0;
   float tmp = 0.0;
   double best = 999999.99;

   if(argc < 3)
      return 0;

   printf("\nNumbers = ");
   double_string *ds = NULL;
   for(i = 1;i < argc - 1; i++) {
      sscanf(argv[i], "%f", &tmp);
      printf("%.0f ", tmp);
      ds = add_double_string(ds, (double)tmp);
   }
   printf("\n");

   int set_size = argc - 2;
   int select = 0;
   sscanf(argv[argc - 1], "%f", &tmp);
   printf("Target = %.0f\n", tmp);
   double target = (double)tmp;
   double v = 0.0;
   int solution = 0;
   int iterations = 0;

   for(select = 1; select <= set_size; select++) {

      counter *nc = make_counter(select, set_size);
      counter *oc = make_operator_counter(select - 1);
      form_string *fs = generate_forms(select);

      while(fs != NULL) {

         for(;;) {
            double_string *tmp = gen_perm(ds, select, nc);

            for(;;) {
               iterations++;
               v = compute(fs->size, fs->form, tmp, oc);
               if(v == target) {
                  printf("----Found Solution %d (exact) after %d iterations----\n", ++solution, iterations);
                  compute_verbose(fs->size, fs->form, tmp, oc);
                  printf("\n");
                  goto end;
               }
               double diff = v - target;
               if(diff < 0)
                  diff = - diff;
               if(diff < best) {
                  printf("----Found Solution %d (%.2f out) after %d iterations----\n", ++solution, diff, iterations);
                  compute_verbose(fs->size, fs->form, tmp, oc);
                  printf("\n");
                  best = diff;
               }
               if(inc_counter(oc))
                  break;
            }

            destroy_double_string(tmp);

            if(inc_counter(nc))
               break;
         }

      fs = fs->next;
      }

      free(nc);
      free(oc);

   }

   end:
   return 0;
}
