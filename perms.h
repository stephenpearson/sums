/* perms.h */

#ifndef _PERMS_H
#define _PERMS_H

typedef struct _double_string {
   double value;
   struct _double_string *next;
} double_string;

typedef struct _counter {
   int qty;
   int values[20];
   int limits[20];
} counter;

void print_double_string(double_string *ds);
void destroy_double_string(double_string *ds);
double_string *dup_double_string(double_string *ds);
double_string *add_double_string(double_string *ds, double value);
double get_double_string(double_string **ds, int pos);
counter *make_counter(int qty, int size);
counter *make_operator_counter(int qty);
int inc_counter(counter *c);
void print_counter(counter *c);
void gen_perms(double_string *ds, int qty, int size);
double_string *gen_perm(double_string *ds, int qty, counter *c);

#endif
