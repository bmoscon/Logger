CC = g++
CCFLAGS = -Wall -Werror -std=c++14 -ggdb3 -fPIC

HEADERS = $(wildcard *.hpp)
SRC     = $(wildcard *.cc)
OBJ     = $(subst .cc,.o,$(SRC))
SO      = liblogger.so


all: liblogger

clean:
	rm -f $(OBJ) $(SO)

liblogger: $(OBJ)
	$(CC) -shared -o $(SO) -Wl,-soname,$(SO) $(OBJ) $(LIBS)

%.o: %.cc $(HEADERS) Makefile
	$(CC) $(CCFLAGS) -c $< -o $@


