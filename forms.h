/* forms.h */

#ifndef _FORMS_H
#define _FORMS_H

typedef struct _form_string {
   int size;
   unsigned int form;
   struct _form_string *next;
} form_string;

form_string *generate_forms(int numcount);
form_string *iterate_forms(int symcount);
void print_pattern(int symcount, unsigned int pattern);
int check_pattern(int symcount, int numcount, unsigned int pattern);
void print_form_string(form_string *fs);

#endif
