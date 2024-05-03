# Compiler and compiler flags
CC = C:/msys64/mingw64/bin/g++
CFLAGS = -Wall -g -std=c++17

# Linker flags for static linking
LDFLAGS = -static-libgcc

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin
LIBDIR = lib
INCDIR := include src src/graphics src/util src/vendor src/vendor/stb_image src/vendor/glm src/io src/entity src/graphics/geometry src/component

# Libraries for GLFW
LIB = -lglfw3 -lgdi32 -lopengl32 -lglew32 -lglu32
GLFW_LDFLAGS = -L$(LIBDIR)

# Main target
TARGET = Robin.exe

# Source and object files
SRCS := $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/*/*.cpp $(SRCDIR)/*/*/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Include directories, each prefixed with -I
INCDIRS := $(foreach d, $(INCDIR), -I$(d))

# Resource Compiler
WINDRES = C:\msys64\mingw64\bin\windres

# Resource Files and Object
RES = gfx/icon.rc
RESOBJ = obj/icon.res

# Add RESOBJ to object files list
OBJS += $(RESOBJ)

# Compile and link
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIB) $(GLFW_LDFLAGS) $(LDFLAGS) -o $@

# Compile resource file
$(RESOBJ): $(RES)
	$(WINDRES) -I$(SRCDIR) -O coff -o $(RESOBJ) $(RES)

# Compile each source file into an object file
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCDIRS) -c $< -o $@

# Create the object directory if it doesn't exist
$(OBJS): | $(OBJDIR)

# Create the binary directory if it doesn't exist
$(TARGET): | $(BINDIR)

# Clean up
clean:
	rm -f $(OBJDIR)/*.o $(OBJDIR)/*/*.o $(TARGET)

# Create the object directory
$(OBJDIR):
	@mkdir -p $@

# Create the binary directory
$(BINDIR):
	@mkdir -p $@