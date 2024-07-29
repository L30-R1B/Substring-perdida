# Compilador
CC = gcc

# Opções de compilação
CFLAGS = -Wall -Wextra -g

# Nome do executável
TARGET = tp1

# Diretório de saída para os arquivos objeto
OBJDIR = obj

# Lista de arquivos fonte
SOURCES = src/main.c src/kmp.c

# Lista de cabeçalhos
HEADERS = include/kmp.h

# Gera os nomes dos arquivos objeto
OBJECTS = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Regra principal para construir o executável
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

# Regra para construir arquivos objeto a partir de arquivos fonte
$(OBJDIR)/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos intermediários e o executável
clean:
	rm -f $(OBJECTS) $(TARGET)

# Crie o diretório de objetos se não existir
$(shell mkdir -p $(OBJDIR))