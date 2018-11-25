GOAL = $(MAKECMDGOALS)

# Directories and files
DIRS_INCLUDES=$(PATH_INCLUDE)
FILES_SOURCES=$(shell find $(PATH_SOURCE) -type f -name '*.cpp')
FILES_OBJECTS=$(FILES_SOURCES:%.cpp=%.o)

FILES_EXECUTABLE_Darwin_i386=tree-simulator
FILES_EXECUTABLE=$(PATH_BUILD)/$(GOAL)/$(FILES_EXECUTABLE_$(GOAL))

# Compilers
CC_Darwin_i386=g++
CC = $(CC_$(GOAL))

# Flags
FLAGS_INCLUDES=$(foreach TMP,$(DIRS_INCLUDES),-I$(TMP))
FLAGS_LINKER=-Wl,-rpath,lib -Llib -lBox2D -lGLEW -lsfml-system -lsfml-window -lsfml-graphics

FLAGS_C_Darwin_i386=-Wall -std=c++11 -g
FLAGS_C=$(FLAGS_C_$(GOAL))

# Targets
$(GOAL): $(FILES_EXECUTABLE)
	@: # Suppress the "nothing to be done" message.

$(FILES_EXECUTABLE): $(FILES_OBJECTS)
	@echo "Linking: $@"
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS_LINKER) $(FILES_OBJECTS) -o $@

$(PATH_ROOT)/src/%.o: $(PATH_ROOT)/src/%.cpp
	@echo "Compiling: $<"
	@$(CC) $(FLAGS_INCLUDES) $(FLAGS_C) -c $< -o $@
