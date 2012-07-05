/* perms.c */

#include <stdio.h>
#include <stdlib.h>
#include "perms.h"

void print_double_string(double_string *ds) {
   while(ds != NULL) {
      printf("%.2f\n", ds->value);
      ds = ds->next;
   }
}

void destroy_double_string(double_string *ds) {
   while(ds != NULL) {
      double_string *last = ds;
      ds = ds->next;
      free(last);
   }
}

double_string *dup_double_string(double_string *ds) {
   double_string *first = NULL;
   double_string *last = NULL;
   while(ds != NULL) {
      double_string *tmp = malloc(sizeof(double_string));
      if(first == NULL)
         first = tmp;
      tmp->value = ds->value;
      if(last != NULL)
         last->next = tmp;
      last = tmp;
      ds = ds->next;
   }
   last->next = NULL;
   return first;
}

double_string *add_double_string(double_string *ds, double value) {
   double_string *first = ds;

   if(ds == NULL) {
      ds = malloc(sizeof(double_string));
      ds->value = value;
      ds->next = NULL;
      return ds;
   }

   double_string *last;
   while(ds != NULL) { 
      last = ds;
      ds = ds->next;
   }

   last->next = malloc(sizeof(double_string));
   last->next->value = value;
   last->next->next = NULL;
   return first;
}

double get_double_string(double_string **ds, int pos) {
   double value = 0.0;
   if(pos == 0) {
      value = (*ds)->value;
      *ds = (*ds)->next;
      return value;
   }

   double_string *current = (*ds)->next;
   double_string *last = *ds;
   int i = 1;

   while(current != NULL) {
      if(i == pos) {
         value = current->value;
         last->next = current->next;
         free(current);
         return value;
      }
      last = current;
      current = current->next;
      i++;
   }
   return 0.0;
}

counter *make_counter(int qty, int size) {
   counter *c = malloc(sizeof(counter));
   c->qty = qty;
   int i = 0;
   for(i = 0; i < qty; i++) {
      c->values[i] = 0;
      c->limits[i] = size - i;
   }
   return c;
}

counter *make_operator_counter(int qty) {
   counter *c = malloc(sizeof(counter));
   c->qty = qty;
   int i = 0;
   for(i = 0; i < qty; i++) {
      c->values[i] = 0;
      c->limits[i] = 4;
   }
   return c;
}

int inc_counter(counter *c) {
   int i = 0;
   int overflow = 1;
   while(overflow && (i < (c->qty))) {
      (c->values[i])++;
      if((c->values[i]) >= (c->limits[i])) {
         overflow = 1;
         c->values[i] = 0;
      } else {
         overflow = 0;
      }
      i++;
   }
   return overflow;
}

void print_counter(counter *c) {
   int i = 0;
   for(i = 0; i < (c->qty); i++) {
      printf("%d ", c->values[i]);
   }
   printf("\n");
}

void gen_perms(double_string *ds, int qty, int size) {
   counter *c = make_counter(qty, size);
   int i = 0;

   for(;;) {
      double_string *tmp = dup_double_string(ds);
      for(i = 0; i < qty; i++) {
         double v = get_double_string(&tmp, c->values[i]);
         printf("%.2f ", v);
      }
      printf("\n");
      destroy_double_string(tmp);
      if(inc_counter(c)) {
         break;
      }
   }
   free(c);
}

double_string *gen_perm(double_string *ds, int qty, counter *c) {
   double_string *result = NULL;
   int i = 0;
   double_string *tmp = dup_double_string(ds);
   for(i = 0; i < qty; i++)
      result = add_double_string(result, get_double_string(&tmp, c->values[i]));
   destroy_double_string(tmp);
   return result;
}
