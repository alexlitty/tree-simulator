GOAL = $(MAKECMDGOALS)

# Dependencies
LIBS=Box2D GLEW sfml-system sfml-window sfml-graphics

# Directories and files
DIR_LIBS=$(PATH_LIB)
DIR_TARGET=$(PATH_BUILD)/$(GOAL)
DIR_RELEASE=$(DIR_TARGET)/release

DIR_INCLUDES=$(PATH_INCLUDE)
DIR_SOURCES=$(PATH_SOURCE)
FILES_SOURCES=$(shell find $(DIR_SOURCES) -type f -name '*.cpp')

DIR_OBJECTS=$(DIR_TARGET)/obj
FILES_OBJECTS=$(subst $(DIR_SOURCES),$(DIR_OBJECTS),$(FILES_SOURCES:%.cpp=%.o))

FILE_EXECUTABLE_darwin-i386=tree-simulator
FILE_EXECUTABLE=$(DIR_RELEASE)/$(FILE_EXECUTABLE_$(GOAL))

# Compilers
CC_darwin-i386=g++
CC=$(CC_$(GOAL))

CC_FLAGS_darwin-i386=-Wall -std=c++11 -g -I$(DIR_INCLUDES)
CC_FLAGS=$(CC_FLAGS_$(GOAL))

# Linkers
CL_darwin-i386=g++
CL=$(CL_$(GOAL))

CL_FLAGS_darwin-i386=-Wl,-rpath,$(subst $(PATH_ROOT)/,,$(DIR_LIBS)) \
                     $(addprefix -L,$(DIR_LIBS)) \
                     $(addprefix -l,$(LIBS))

CL_FLAGS=$(CL_FLAGS_$(GOAL))

# Targets
$(GOAL): $(FILE_EXECUTABLE)
	@: # Suppress the "nothing to be done" message.

$(FILE_EXECUTABLE): $(FILES_OBJECTS)
	@echo "Link :: $@"
	@mkdir -p $(dir $@)
	@$(CL) $(CL_FLAGS) $(FILES_OBJECTS) -o $@

$(DIR_OBJECTS)/%.o: $(DIR_SOURCES)/%.cpp
	@echo "Comp :: $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) -c $< -o $@
