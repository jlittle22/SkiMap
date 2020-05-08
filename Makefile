CC = gcc # The compiler being used

# Updating include path. 
#IFLAGS = -I/h/jlittl04/comp/Projects/Sources/


CFLAGS = -g -Wall -Werror -Wextra -pedantic # $(IFLAGS)

#source code path
#VPATH=/h/jlittl04/comp/Projects/Sources/


INCLUDES = $(shell echo *.h)

############### Rules ###############

all: SkiMap

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

SkiMap: main.o LinkedList.o Edge.o Vertex.o Errors.o SkiMap.o MinHeap.o SmallFloat.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)


clean:
	rm -f SkiMap *.o

