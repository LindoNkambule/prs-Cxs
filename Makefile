#COMPILER
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic

#DYNAMIC LIBRARIES
#DYN_LIBS=-lz -lbz2 -lm -lpthread -llzma -lcurl

#prs-Csx sources & binary
PROG=prs
HFILE=$(shell find src -name "*.h")
CFILE=$(shell find src -name "*.c")
OFILES=main.o min_max.o gigrnd.o random_number.o
VPATH=$(shell for file in `find src -name "*.c"`; do echo $$(dirname $$file); done)

# COMPILATION RULES
all: $(PROG) clean

$(PROG): $(OFILES)
	$(CC) $(OFILES) -Isrc -o $(PROG)

OFILES%.o: %.c $(HFILE)
	$(CC) $(CFLAGS) -Isrc -c $<

clean:
	rm -rf *.o

# NB: once program is ready, include -Wno-unused-variable in CFLAGS, there's a variable we don't use
# CFLAGS = -std=c99 -Wall -Wextra -pedantic -Wno-unused-variable