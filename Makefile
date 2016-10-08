SOURCES=$(shell find src/ -type f -name '*.cpp')
OBJECTS=$(SOURCES:.cpp=.o)

# Paths
SRCPATH=src/
INCPATHS=include/
BINPATH=bin

# Linker flags
LDFLAGS=-Llib -lBox2D -lGLEW -lsfml-system -lsfml-window -lsfml-graphics

# Background colors
BG_WHITE=$$(tput setab 7)

# Foreground colors
FG_RED=$$(tput setaf 1)
FG_GREEN=$$(tput setaf 2)
FG_YELLOW=$$(tput setaf 3)
FG_BLUE=$$(tput setaf 4)
FG_MAGENTA=$$(tput setaf 5)
FG_CYAN=$$(tput setaf 6)

# Other colors
COLOR_RESET=$$(tput sgr 0)
 
# Goal-Based variables
GOAL = $(MAKECMDGOALS)
ifeq ($(GOAL), clean)
	GOAL = 
	SOURCE_FILES =
endif

OBJECTS=$(SOURCES:%.cpp=%.o)
#SOURCE_FILES=$(SOURCES:%=$(SRCPATH)%)
#OBJECT_FILES=$(OBJECTS:%=$(SRCPATH)%)
SOURCE_FILES =$(SOURCES)
OBJECT_FILES=$(OBJECTS)

# Compilers
CC_linux64=g++
CC_win32=i686-w64-mingw32-g++
CC = $(CC_$(GOAL))

# Language-specific flags
CFLAGS_linux64=-Wall -std=c++11 -g
CFLAGS_win32=-Wall -std=c++0x -g
CFLAGS=$(CFLAGS_$(GOAL))

INCFLAGS=$(foreach TMP,$(INCPATHS),-I$(TMP))
EXECUTABLE_linux64=treesimulator
EXECUTABLE_win32=treesimulator.exe
EXECUTABLE=$(EXECUTABLE_$(GOAL))

# Initial Target
$(GOAL): $(SOURCES_FILES) $(EXECUTABLE)

# Link into executable
$(EXECUTABLE): $(OBJECT_FILES)
	@echo ""
	@echo "$(BG_WHITE)$(FG_GREEN) Linking $(COLOR_RESET)"
	$(CC) $(LDFLAGS) $(OBJECT_FILES) -o $(BINPATH)/$(GOAL)/$@
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
