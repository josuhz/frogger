# Compiler
CXX ?= g++
CROSS_COMPILE ?=

# Target architecture:
#   make              -> native build
#   make pi4-a32     -> Raspberry Pi 4 AArch32 build
TARGET_ARCH ?= native

ifeq ($(TARGET_ARCH),pi4-a32)
CXX := $(if $(CROSS_COMPILE),$(CROSS_COMPILE)g++,g++)
ARCH_CXXFLAGS := -march=armv8-a+crc -mtune=cortex-a72 -mfpu=neon-fp-armv8 -mfloat-abi=hard
else
ARCH_CXXFLAGS :=
endif

# Build options
CPPFLAGS += -Iinclude
CXXFLAGS += -std=c++17 -Wall -Wextra -O0 $(ARCH_CXXFLAGS)

# Libraries. pkg-config is preferred on Raspberry Pi OS, with a simple fallback.
PKG_CONFIG ?= pkg-config
PKG_DEPS := ncursesw sdl2 SDL2_mixer
PKG_CFLAGS := $(shell $(PKG_CONFIG) --cflags $(PKG_DEPS) 2>/dev/null)
PKG_LIBS := $(shell $(PKG_CONFIG) --libs $(PKG_DEPS) 2>/dev/null)

CPPFLAGS += $(PKG_CFLAGS)
LDLIBS := $(if $(strip $(PKG_LIBS)),$(PKG_LIBS),-lncursesw -lSDL2 -lSDL2_mixer)

# Executable name
TARGET = frogger

# Source files
SRC = main.cpp \
      interfaz/tableroNcurses.cpp \
      logica/rana.cpp \
      logica/carro.cpp \
      controlador/revisionEntradas.cpp \
      logica/movCarros.cpp \
      controlador/cicloPrincipal.cpp \
      logica/agua.cpp \
      logica/lilyPad.cpp \
      logica/tronco.cpp

BUILD_DIR = build/$(TARGET_ARCH)
OBJ = $(SRC:%.cpp=$(BUILD_DIR)/%.o)
DEP = $(OBJ:.o=.d)
LEGACY_OBJ = $(SRC:.cpp=.o)
ASM_SRC = include/contiene.s
ASM_OBJ = $(ASM_SRC:%.s=$(BUILD_DIR)/%.o)

.PHONY: all pi4-a32 run clean

# Main rule
all: $(TARGET)

# Raspberry Pi 4, 32-bit ARM/AArch32
pi4-a32:
	$(MAKE) TARGET_ARCH=pi4-a32

# Link
$(TARGET): $(OBJ) $(ASM_OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(ASM_OBJ) -o $(TARGET) $(LDLIBS)

# Compile
$(BUILD_DIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(AS) -o $@ $<

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Run
run: $(TARGET)
	./$(TARGET)

# Clean
clean:
	rm -rf build $(TARGET) $(LEGACY_OBJ) $(ASM_OBJ)

-include $(DEP)
