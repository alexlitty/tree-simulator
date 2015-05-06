SOURCES=main.cpp layer.cpp layer/game.cpp layer/menu.cpp layer/root.cpp resource/font.cpp error.cpp
OBJECTS=$(SOURCES:.cpp=.o)
SRCPATH=src/
INCPATHS=include/
BINPATH=bin
LDFLAGS=-lGLEW -lsfml-system -lsfml-window -lsfml-graphics
CFLAGS=-Wall -std=c++11

# Compilers
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
OBJECTS=$(SOURCES:%.cpp=%.o)
SOURCE_FILES=$(SOURCES:%=$(SRCPATH)%)
OBJECT_FILES=$(OBJECTS:%=$(SRCPATH)%)

# Compilers
CC_linux64=g++
CC_win32=/opt/mingw32/cross_win32/bin/i686-w64-mingw32-g++
CC = $(CC_$(GOAL))

INCFLAGS=$(foreach TMP,$(INCPATHS),-I$(TMP))
EXECUTABLE=treesimulator

# Initial Target
$(GOAL): $(SOURCES_FILES) $(EXECUTABLE)

# Link into executable
$(EXECUTABLE): $(OBJECT_FILES)
	@echo "$(BG_WHITE)$(FG_GREEN) Creating $@ $(COLOR_RESET)"
	$(CC) $(LDFLAGS) $(OBJECT_FILES) -o $(BINPATH)/$(GOAL)/$@
	@echo ""

# Compile source into objects
.cpp.o:
	@echo "$(BG_WHITE)$(FG_BLUE) Compiling $< $(COLOR_RESET)"
	@mkdir -p $(dir $@)
	$(CC) $(INCFLAGS) $(CFLAGS) -c $< -o $@
	@echo ""
