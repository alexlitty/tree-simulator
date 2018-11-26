GOAL = $(MAKECMDGOALS)

# Directories and files
DIR_TARGET=$(PATH_BUILD)/$(GOAL)
DIR_RELEASE=$(DIR_TARGET)/release

DIR_INCLUDES=$(PATH_INCLUDE)
DIR_SOURCES=$(PATH_SOURCE)
FILES_SOURCES=$(shell find $(DIR_SOURCES) -type f -name '*.cpp')

DIR_OBJECTS=$(DIR_TARGET)/obj
FILES_OBJECTS=$(subst $(DIR_SOURCES),$(DIR_OBJECTS),$(FILES_SOURCES:%.cpp=%.o))

FILE_EXECUTABLE_Darwin_i386=tree-simulator
FILE_EXECUTABLE=$(DIR_RELEASE)/$(FILE_EXECUTABLE_$(GOAL))

# Compilers
CC_Darwin_i386=g++
CC = $(CC_$(GOAL))

# Flags
FLAGS_C_Darwin_i386=-Wall -std=c++11 -g -I$(DIR_INCLUDES)
FLAGS_C=$(FLAGS_C_$(GOAL))

FLAGS_LINKER=-Wl,-rpath,lib -Llib -lBox2D -lGLEW -lsfml-system -lsfml-window -lsfml-graphics

# Targets
$(GOAL): $(FILE_EXECUTABLE)
	@: # Suppress the "nothing to be done" message.

$(FILE_EXECUTABLE): $(FILES_OBJECTS)
	@echo "Link :: $@"
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS_LINKER) $(FILES_OBJECTS) -o $@

$(DIR_OBJECTS)/%.o: $(DIR_SOURCES)/%.cpp
	@echo "Comp :: $<"
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS_INCLUDES) $(FLAGS_C) -c $< -o $@
