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
      $(wildcard src/utils/result/*.c)

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
	@for %%d in ($(DIRS)) do if not exist $(BUILD_DIR)\%%d mkdir $(BUILD_DIR)\%%d

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
