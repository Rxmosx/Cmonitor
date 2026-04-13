TARGET = cmonitor

# Compilador
CC = gcc

# Flags de compilação (mostra avisos e ajuda no debug)
CFLAGS = -Wall -Wextra -g

# Lista de todos os arquivos .c
SRCS = main.c display.c proc.c

# Converte a lista de .c para .o (arquivos de objeto)
OBJS = $(SRCS:.c=.o)

# Regra principal: compila o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar os arquivos .o individualmente
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa os arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)