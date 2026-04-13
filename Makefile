TARGET = cmonitor


CC = gcc


CFLAGS = -Wall -Wextra -g


SRCS = main.c display.c


OBJS = $(SRCS:.c=.o)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)