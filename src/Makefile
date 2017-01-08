CC = g++
CCFLAGS = -Wall -Werror -std=c++14 -ggdb3 -fPIC
AR = ar

HEADERS = $(wildcard *.hpp)
SRC     = $(wildcard *.cc)
OBJ     = $(subst .cc,.o,$(SRC))
NAME    = liblogger
SO      = $(NAME).so
A       = $(NAME).a

all: liblogger

clean:
	rm -f $(OBJ) $(SO) $(A)

liblogger: $(OBJ)
	$(CC) -shared -o $(SO) -Wl,-soname,$(SO) $(OBJ)
	$(AR) -cvq $(A) $(OBJ)

%.o: %.cc $(HEADERS) Makefile
	$(CC) $(CCFLAGS) -c $< -o $@


