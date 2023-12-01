CXX := g++

ifeq ($(OS),Windows_NT)
	detected_OS := Windows
	RM := rmdir /Q /S
	UN := del
	FixPath = $(subst /,\,$1)
	ext := .exe
else
	detected_OS := $(shell uname)
	RM := rm -f -r
	UN := $(RM)
	FLAGS := -p
	FixPath = $1
endif

MD := mkdir $(FLAGS)

# Compiler flags
CXXFLAGS += -std=c++17 -pedantic-errors
CXXFLAGS += -Wall -Wextra
CXXFLAGS += -g3 -O3

# Makefile arguments
CMD_ARGS := $(filter-out $@,$(MAKECMDGOALS))
DAY_DIR := day-$(CMD_ARGS)

# Source files
DIRS := $(patsubst $(DAY_DIR)/src/%, %, $(wildcard $(DAY_DIR)/src/*))
PROG_SOURCES := $(wildcard $(DAY_DIR)/src/*/*.cpp)
OBJECTS := $(patsubst $(DAY_DIR)/src/%.cpp, build/%.o, $(PROG_SOURCES))
DEPENDENCIES := $(patsubst $(DAY_DIR)/src/%.cpp, build/%.d, $(PROG_SOURCES))

-include $(call FixPath,$(DEPENDENCIES))

all: help

help:
	@echo "Usage:"
	@echo "  make <day> - Compiles and runs the program for the specified day"

prepare:
	@echo "Detected OS: $(detected_OS)\n"
	-@$(RM) build/
	@echo "Removed build directory"

dirs: clean
	@$(MD) $(call FixPath,$(patsubst %, build/%, $(DIRS)))
	@echo "Created directories: \n$(DIRS)"

clean: prepare
	-@$(UN) main$(ext)
	@echo "Removed main$(ext)"

build/%.o: $(DAY_DIR)/src/%.cpp
	@echo "\nCompiling: $< : $@..."
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $(call FixPath,$<) -o $(call FixPath,$@)

main: $(OBJECTS)
	@echo "\nLinking $@..."
	$(CXX) $(CXXFLAGS) -o $@ $(call FixPath,$^) $(LDFLAGS)

%: dirs main
	@echo "\nBuilt day $(CMD_ARGS) successfully!"

# Prevents make from interpreting the arguments as targets
.PHONY: all help prepare dirs clean main $(CMD_ARGS)

# No remaking of makefiles
Makefile: ;