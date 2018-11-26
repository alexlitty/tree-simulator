GOAL = $(MAKECMDGOALS)

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

# Dependencies
LIBS=Box2D GLEW sfml-system sfml-window sfml-graphics

ASSET_SOURCES=$(shell find $(PATH_ASSETS) -type f)
ASSET_TARGETS=$(subst $(PATH_ROOT),$(DIR_RELEASE),$(ASSET_SOURCES))

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

# Define the goal: An executable with its assets.
$(GOAL): $(FILE_EXECUTABLE) $(ASSET_TARGETS)
	@: # Suppress the "nothing to be done" message.

# Link the final executable together.
$(FILE_EXECUTABLE): $(FILES_OBJECTS)
	@echo "Link :: $@"
	@mkdir -p $(dir $@)
	@$(CL) $(CL_FLAGS) $(FILES_OBJECTS) -o $@

# Compile .o from .cpp.
$(DIR_OBJECTS)/%.o: $(DIR_SOURCES)/%.cpp
	@echo "Comp :: $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) -c $< -o $@

# Copy assets to the release directory.
$(DIR_RELEASE)/%: $(PATH_ROOT)/%
	@echo "File :: $<"
	@mkdir -p $(dir $@)
	@cp $< $@
