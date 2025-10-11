# Makefile para PROJETO_C (Windows / PowerShell)

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g

# Pasta de build
BUILD_DIR = build

# Executável final
TARGET = programa.exe

# Garante que todas as pastas necessárias existam
prepare:
	@if not exist build mkdir build
	@if not exist build\dados mkdir build\dados
	@if not exist build\users mkdir build\users
	@if not exist build\equipes mkdir build\equipes
	@if not exist build\hackathons mkdir build\hackathons
	@if not exist build\votacao mkdir build\votacao

# Lista todos os arquivos .c
SRC = $(wildcard src/*.c) \
      $(wildcard src/dados/*.c) \
      $(wildcard src/users/*.c) \
      $(wildcard src/equipes/*.c) \
      $(wildcard src/hackathons/*.c) \
      $(wildcard src/votacao/*.c)

# Gera os nomes dos .o correspondentes
OBJ = $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRC))

# Alvo padrão: prepara as pastas e compila o projeto
all: prepare $(TARGET)

# Linka o executável final
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compila cada .c em .o (cria subpastas conforme necessário)
$(BUILD_DIR)/%.o: src/%.c
	@if not exist $(BUILD_DIR)\$(subst /,\,$(dir $@)) mkdir $(BUILD_DIR)\$(subst /,\,$(dir $@))
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa arquivos compilados
clean:
	@if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
	@if exist $(TARGET) del $(TARGET)

# Executa o programa
run: $(TARGET)
	./$(TARGET)
