 #
 # @file GTK.mk
 # @author Maurício Spinardi (mauricio.spinardi@setis.com.br)
 # @platform cygwin64
 # @brief Makefile
 # @date 2020-07-20
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
libitudev

PROJECT_VERSION := \
01.00.00

PROJECT_INC := \
-I"include"

BIN_DIR := \
./lib/$(CFG_NAME)

BUILD_DIR := \
./lib/$(CFG_NAME)/build

SRC_DIR := \
./src/gtk

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

AR := \
ar

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
$(PROJECT_INC) \
-Wall \
-Wextra \
-fPIC \
-fvisibility=hidden

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
$(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%.o,$(wildcard $(SRC_DIR)/*.c*))

# Regras de compilação e instalação

.PHONY: all
all:
	@$(MAKE) -f GTK.mk --no-print-directory -j4 -Orecurse prebuild build

.PHONY: build
build: prebuild $(OBJS)
	@echo Generating static $(PROJECT_NAME) library...
	@$(AR) rc $(BIN_DIR)/$(PROJECT_NAME).a $(OBJS)

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
	@echo - compiling with gcc $<...
	@$(CC) -std=c99 $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	@echo - compiling with g++ $<...
	@$(CPP) -std=c++11 $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@rm -fr ./lib

.PHONY: prebuild
prebuild:
	@echo Starting build $(PROJECT_NAME) in $(CFG_NAME) mode...
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(BUILD_DIR)
