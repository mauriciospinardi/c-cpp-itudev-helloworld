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

.EXPORT_ALL_VARIABLES:

ROOT_DIR := \
$(subst \,/,$(ROOT_DIR))

# Definições básicas

CFG_NAME := \
$(if $(CFG_NAME),$(CFG_NAME),release)

PROJECT_NAME := \
helloworld

PROJECT_VERSION := \
01.00.00

BIN_DIR := \
./bin/$(CFG_NAME)

BUILD_DIR := \
./build/$(CFG_NAME)

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

# ItuDevelopers

ITUDEV_VERSION := \
01.00.00

ITUDEV_DIR := \
./lib/$(CFG_NAME)

ITUDEV_INC := \
-I"include"

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
$(ITUDEV_INC) \
-Wall \
-Wextra

# Opções de vinculação

LDFLAGS += \
-L$(GTK_DIR)/lib \
-L$(ITUDEV_DIR)

LDFLAGS += \
-Wl,-Map=$(BUILD_DIR)/$(PROJECT_NAME).map \
-Wl,-rpath-link=$(GTK_DIR)/lib

LDFLAGS += \
-l:libgio-2.0.dll.a \
-l:libglib-2.0.dll.a \
-l:libgobject-2.0.dll.a \
-l:libgtk-3.dll.a \
-l:libitudev.a

# Objetos de saída

OBJS := \
$(patsubst src/%,$(BUILD_DIR)/%.o,$(wildcard src/*.c*))

# Regras de compilação e instalação

.PHONY: all
all:
	@$(MAKE) --no-print-directory -f GTK.mk
	@$(MAKE) --no-print-directory -j4 -Orecurse build

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
	@$(MAKE) --no-print-directory -f GTK.mk clean
	@rm -fr ./bin
	@rm -fr ./build

.PHONY: prebuild
prebuild:
	@echo Starting build $(PROJECT_NAME) in $(CFG_NAME) mode...
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(BUILD_DIR)
