# name of the program (Minix service)
PROG=proj

# source code files to be compiled
SRCS = timer.c kbc.c utils.c

CFLAGS += -pedantic

DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
