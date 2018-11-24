GOAL = $(MAKECMDGOALS)

# Paths
SRCPATH=src
INCPATHS=include
BUILDPATH=build

# Linker flags
LDFLAGS=-Wl,-rpath,lib -Llib -lBox2D -lGLEW -lsfml-system -lsfml-window -lsfml-graphics

# Colors
BG_WHITE=$$(tput setab 7)
FG_RED=$$(tput setaf 1)
FG_GREEN=$$(tput setaf 2)
FG_YELLOW=$$(tput setaf 3)
FG_BLUE=$$(tput setaf 4)
FG_MAGENTA=$$(tput setaf 5)
FG_CYAN=$$(tput setaf 6)
COLOR_RESET=$$(tput sgr 0)

# Source and object filepaths
SOURCES=$(shell find src -type f -name '*.cpp')
OBJECTS=$(SOURCES:%.cpp=%.o)
SOURCE_FILES=$(SOURCES)
OBJECT_FILES=$(OBJECTS)

ifeq ($(GOAL), clean)
	GOAL = 
	SOURCE_FILES =
endif

# Compilers
CC_Darwin_i386=g++
CC = $(CC_$(GOAL))

# Language-specific flags
CFLAGS_Darwin_i386=-Wall -std=c++11 -g
CFLAGS=$(CFLAGS_$(GOAL))

INCFLAGS=$(foreach TMP,$(INCPATHS),-I$(TMP))
EXECUTABLE_Darwin_i386=treesimulator

PATH_EXECUTABLE=$(BUILDPATH)/$(GOAL)/$(EXECUTABLE_$(GOAL))

# Initial Target
$(GOAL): $(SOURCES_FILES) $(PATH_EXECUTABLE)

# Link into executable
$(PATH_EXECUTABLE): $(OBJECT_FILES)
	@echo ""
	@echo "$(BG_WHITE)$(FG_GREEN) Linking $(COLOR_RESET)"
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $(OBJECT_FILES) -o $@
	@echo ""

# Compile source into objects
.cpp.o:
#	@echo "$(BG_WHITE)$(FG_BLUE) Compiling $< $(COLOR_RESET)"
#	@mkdir -p $(dir $@)
	$(CC) $(INCFLAGS) $(CFLAGS) -c $< -o $@
#	@echo ""

# Used to find all source files
# Cleaning Target
.PHONY: clean
clean:
	@find . -type f -name '*.o' -delete
