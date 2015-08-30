#SOURCES=Main.cpp Object/Character/Beaver.cpp Component/Actor.cpp Component/Drawable.cpp Component/Expirable.cpp Component/Intel.cpp Component/Lifeform.cpp Component/Object.cpp Component/Physical.cpp Engine/Constant.cpp Gui/Message.cpp Intel/MaintainDistance.cpp Intel/MoveBlindly.cpp Object/Background/Stars.cpp Object/Internal/Editor.cpp Object/Nugget.cpp Object/Particles.cpp Object/Planet.cpp Object/Player.cpp Layer/Type.cpp Layer/Game.cpp Layer/Menu.cpp Layer/Root.cpp Math/Constant.cpp Math/Geometry.cpp Math/Random.cpp Math/Trigonometry.cpp Math/Vector.cpp Resource/Color.cpp Resource/Font.cpp Resource/Shader.cpp Engine/Error.cpp Object/Branch.cpp Object/Branch/Birch.cpp Physics/Collisions.cpp Physics/Pixels.cpp Physics/World.cpp Utility/Brush.cpp Utility/Float.cpp Utility/Stage.cpp
SOURCES=$(shell find src/ -type f -name '*.cpp')
OBJECTS=$(SOURCES:.cpp=.o)
SRCPATH=src/
INCPATHS=include/
BINPATH=bin
LDFLAGS=-lBox2D -lGLEW -lsfml-system -lsfml-window -lsfml-graphics
CFLAGS=-Wall -std=c++11 -g

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
CC_win32=/opt/mingw32/cross_win32/bin/i686-w64-mingw32-g++
CC = $(CC_$(GOAL))

INCFLAGS=$(foreach TMP,$(INCPATHS),-I$(TMP))
EXECUTABLE=treesimulator

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
