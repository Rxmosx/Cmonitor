TARGET = cmonitor


CC = gcc


CFLAGS = -Wall -Wextra -g


sysmon: main.c cpu.c mem.c display.c proc.c
	$(CC) $(CFLAGS) -o Cmonitor main.c cpu.c mem.c display.c proc.c


clean:
	rm -f $(OBJS) $(TARGET)~