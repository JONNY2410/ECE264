TARGET = test_maze
GCC = gcc
CFLAGS = -g -std=c99 -Wall -Wshadow -Wvla -Werror -pedantic
CC = $(GCC) $(CFLAGS)
SRCS = test_maze.c maze.c
OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

test: $(TARGET)
        $(VALGRIND)=./valgrind.log ./test_maze

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f $(OBJS) $(TARGET)

