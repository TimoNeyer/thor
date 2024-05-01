# compiler
CC = g++

# C++ flags
CFLAGS = -std=c++17 -Wall 

# directories
SRCDIR = src
OBJDIR = .obj
DEPDIR = .dep

# source files
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEP = $(OBJS:$(OBJDIR)/%.o=$(DEPDIR)/%.d)

TARGET = thor.out

thor: clean

# clean target
.PHONY: clean
clean:
    rm -f $(wildcard ./$(OBJ)/* ./$(DEP)/*);

# build target
.PHONY: build
build: $(TARGET)

# run target
#.PHONY: run
#run: $(TARGET)
#    ./$(TARGET)

# rule to build object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
    @mkdir -p $(OBJDIR)
    $(CC) $(CFLAGS) -c $< -o $@ -MD -MP -MF $(DEPDIR)/$*.d

# rule to build the target
$(TARGET): $(OBJ)
    @mkdir -p $(dir $@)
    $(CC) $(CFLAGS) $^ -o $@

# Include the dependency files
-include $(DEP)
