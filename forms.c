/* forms.c */

#include <stdio.h>
#include <stdlib.h>
#include "forms.h"

form_string *generate_forms(int numcount) {
   form_string *fs = malloc(sizeof(form_string));

   /* Must have at least one number to be valid */
   if(numcount < 1) return NULL;

   /* Trivial case, single number */
   if(numcount == 1) {
      fs->size = 1;
      fs->form = 0x01;
      fs->next = NULL;
      return fs;
   }

   /* Trivial case, two numbers with one operator */
   if(numcount == 2) {
      fs->size = 3;
      fs->form = 0x03;
      fs->next = NULL;
      return fs;
   }

   free(fs);

   /* Non trivial, find all valid forms */
   fs = iterate_forms(numcount);
   return fs;
}

form_string *iterate_forms(int numcount) {
   form_string *start = NULL;
   form_string *last = NULL;
   form_string *fs = NULL;

   int symcount = numcount * 2 - 1;
   if(symcount > 32) return NULL;  /* Make sure we don't overflow a uint */

   unsigned int subpattern = 0;
   unsigned int pattern = 0;
   int limit = 1 << ((numcount * 2) - 4);

   for(subpattern = 0; (int)subpattern < limit; subpattern++) {
      pattern = ( subpattern << 2 ) | 0x03;
      if(check_pattern(symcount, numcount, pattern)) {
         fs = malloc(sizeof(form_string));
         if(start == NULL) start = fs;

         fs->size = symcount;
         fs->form = pattern;
         fs->next = NULL;
         if(last != NULL) last->next = fs;
         last = fs;
      }
   }
   return start;
}

int check_pattern(int symcount, int numcount, unsigned int pattern) {
   /* Must begin with two numbers */
   if((pattern & 0x03) != 0x03) return 0;

   /* Must end with operator */
   if(((pattern >> symcount) & 0x01) != 0x00) return 0;

   /* Stack must never underflow */
   int o_count = 0;
   int n_count = 0;
   unsigned int shift = pattern;
   int i = 0;
   for(i = 0; i < symcount; i++) {
      if((shift & 0x01) == 0x01)
         n_count ++;
      else
         o_count ++;
      if(o_count >= n_count) return 0;
      shift = shift >> 1;
   }

   /* Must be correct qty of numbers */
   if(n_count != numcount) return 0;

   return 1;
}

void print_pattern(int symcount, unsigned int pattern) {
   unsigned int shift = pattern;

   int i = 0;
   for(i = 0 ; i < symcount; i++) {
      if((shift & 0x01) == 1) {
         printf("n");
      } else {
         printf("x");
      }
      shift = shift >> 1;
   }
   printf("\n");
}

void print_form_string(form_string *fs) {
   while(fs != NULL) {
      print_pattern(fs->size, fs->form);
      fs = fs->next;
   }
}

void destroy_form_string(form_string *fs) {
   while(fs != NULL) {
      form_string *tmp = fs;
      fs = fs->next;
      free(tmp);
   }
}
