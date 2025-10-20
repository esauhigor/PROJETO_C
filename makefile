# ==========================
# Makefile para PROJETO_C
# Compatível com Windows (CMD / PowerShell)
# ==========================

# Compilador
CC = gcc
CFLAGS = -Wall -g

# Pasta de build
BUILD_DIR = build

# Nome do executável
TARGET = programa.exe

# ==========================
# Subpastas do projeto
# ==========================
DIRS = dados users equipes hackathons votacao utils/files utils/result

# ==========================
# Fontes e objetos
# ==========================
SRC = $(wildcard src/*.c) \
      $(wildcard src/dados/*.c) \
      $(wildcard src/users/*.c) \
      $(wildcard src/equipes/*.c) \
      $(wildcard src/hackathons/*.c) \
      $(wildcard src/votacao/*.c) \
      $(wildcard src/utils/files/*.c) \
      $(wildcard src/utils/result/*.c) \
	  $(wildcard src/auth/*.c)

OBJ = $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRC))

# ==========================
# Alvo padrão
# ==========================
all: prepare $(TARGET)

# ==========================
# Linkagem final
# ==========================
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# ==========================
# Compilação dos .c em .o
# ==========================
$(BUILD_DIR)/%.o: src/%.c
	@if not exist $(BUILD_DIR)\$(subst /,\,$(dir $@)) mkdir $(BUILD_DIR)\$(subst /,\,$(dir $@))
	$(CC) $(CFLAGS) -c $< -o $@

# ==========================
# Preparação das pastas
# ==========================
prepare:
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	@if not exist $(BUILD_DIR)\dados mkdir $(BUILD_DIR)\dados
	@if not exist $(BUILD_DIR)\users mkdir $(BUILD_DIR)\users
	@if not exist $(BUILD_DIR)\equipes mkdir $(BUILD_DIR)\equipes
	@if not exist $(BUILD_DIR)\hackathons mkdir $(BUILD_DIR)\hackathons
	@if not exist $(BUILD_DIR)\votacao mkdir $(BUILD_DIR)\votacao
	@if not exist $(BUILD_DIR)\utils mkdir $(BUILD_DIR)\utils
	@if not exist $(BUILD_DIR)\utils\files mkdir $(BUILD_DIR)\utils\files
	@if not exist $(BUILD_DIR)\utils\result mkdir $(BUILD_DIR)\utils\result
	@if not exist $(BUILD_DIR)\auth mkdir $(BUILD_DIR)\auth

# ==========================
# Limpeza
# ==========================
clean:
	@if exist $(BUILD_DIR) rd /S /Q $(BUILD_DIR)
	@if exist $(TARGET) del $(TARGET)

# ==========================
# Executar o programa
# ==========================
run: all
	./$(TARGET)
