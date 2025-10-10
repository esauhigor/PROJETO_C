# Makefile para PROJETO_C (Windows / PowerShell)

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g

# Pasta de build
BUILD_DIR = build

# Executável
TARGET = programa.exe

# Lista todos os arquivos .c do projeto
SRC = $(wildcard src/*.c) \
      $(wildcard src/dados/*.c) \
      $(wildcard src/users/*.c) \
      $(wildcard src/equipes/*.c) \
      $(wildcard src/hackathons/*.c) \
      $(wildcard src/votacao/*.c)

# Converte cada src/arquivo.c para build/arquivo.o mantendo hierarquia
OBJ = $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRC))

# Target padrão
all: $(TARGET)

# Linka o executável
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compila cada .c em .o
# Cria pastas automaticamente no Windows
$(BUILD_DIR)/%.o: src/%.c
	@if not exist $(BUILD_DIR)\$(subst /,\,$(dir $@)) mkdir $(BUILD_DIR)\$(subst /,\,$(dir $@))
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	del /Q $(BUILD_DIR)\*.o 2>nul
	if exist $(TARGET) del $(TARGET)

# Rodar o programa
run: $(TARGET)
	./$(TARGET)
