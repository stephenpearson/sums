CFLAGS = -W -O2
LDFLAGS = -lm

sums:		sums.o rpn.o forms.o perms.o calc.o

sums.o:		sums.c

rpn.o:		rpn.c rpn.h

forms.o:	forms.c forms.h

perms.o:	perms.c perms.h

calc.o:		calc.c calc.h

.PHONY:		clean

clean:
		rm -f *.o sums
