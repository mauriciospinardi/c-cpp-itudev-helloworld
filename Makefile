 #
 # @file Makefile
 # @author Maurício Spinardi (mauricio.spinardi@setis.com.br)
 # @platform cygwin64
 # @brief Makefile
 # @date 2020-07-13
 #
 #

ifndef ROOT_DIR
$(error ROOT_DIR not defined!)
endif

ROOT_DIR := \
$(subst \,/,$(ROOT_DIR))

# Definições básicas

CFG_NAME := \
$(subst ,release,$(CFG_NAME))

PROJECT_NAME := \
gtk-hello-world

PROJECT_VERSION := \
01.00.00

BIN_DIR := \
bin/$(CFG_NAME)

BUILD_DIR := \
build/$(CFG_NAME)

DEF := \
-D_PROJECT_NAME_="\"$(PROJECT_NAME)\"" \
-D_PROJECT_VERSION_="\"$(PROJECT_VERSION)\""

# GTK

GTK_VERSION := \
3.0

GTK_DIR := \
$(ROOT_DIR)/usr/x86_64-w64-mingw32/sys-root/mingw

GTK_INC := \
-isystem "$(GTK_DIR)/include/atk-1.0" \
-isystem "$(GTK_DIR)/include/cairo" \
-isystem "$(GTK_DIR)/include/gdk-pixbuf-2.0" \
-isystem "$(GTK_DIR)/include/glib-2.0" \
-isystem "$(GTK_DIR)/include/gtk-3.0" \
-isystem "$(GTK_DIR)/include/pango-1.0" \
-isystem "$(GTK_DIR)/lib/glib-2.0/include"

# Executáveis

CC := \
gcc

CPP := \
g++

# Opções de compilação

CFLAGS := \
-O3

ifeq ($(CFG_NAME),debug)
CFLAGS := \
-O0 -g

DEF += \
-D_DEBUG_
endif

CFLAGS += \
$(DEF) \
$(GTK_INC) \
-Wall \
-Wextra

# Opções de vinculação

LDFLAGS += \
-L$(GTK_DIR)/lib

LDFLAGS += \
-Wl,-Map=$(BUILD_DIR)/$(PROJECT_NAME).map \
-Wl,-rpath-link=$(GTK_DIR)/lib

LDFLAGS += \
-l:libgio-2.0.dll.a \
-l:libglib-2.0.dll.a \
-l:libgobject-2.0.dll.a \
-l:libgtk-3.dll.a

# Objetos de saída

OBJS := \
$(patsubst src/%,$(BUILD_DIR)/%.o,$(wildcard src/*.c*))

# Regras de compilação e instalação

.PHONY: all
all:
	@$(MAKE) --no-print-directory -j4 -Orecurse prebuild build

.PHONY: build
build: prebuild $(OBJS)
	@echo - linking with g++...
	@$(CPP) $(OBJS) -Wl,--start-group $(LDFLAGS) -Wl,--end-group -o $(BIN_DIR)/$(PROJECT_NAME).exe
	@echo -n Finished building application at & date "+ %F %T"

$(BUILD_DIR)/%.c.o: src/%.c
	@echo - compiling with gcc $<...
	@$(CC) -std=c99 $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cpp.o: src/%.cpp
	@echo - compiling with g++ $<...
	@$(CPP) -std=c++11 $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@echo Cleaning...
	@rm -fr bin
	@rm -fr build
	@rm -fr dist

.PHONY: dist
dist:
	@echo Building distributable structure...
	@rm -fr ./dist
	@mkdir -p ./dist
	@mkdir -p ./dist/bin
	@cp ./*.md ./dist
	@cp ./$(BIN_DIR)/*.exe ./dist/bin
	@echo Finished building distributable structure at ./dist

.PHONY: prebuild
prebuild:
	@echo Starting build $(PROJECT_NAME) in $(CFG_NAME) mode...
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(BUILD_DIR)
