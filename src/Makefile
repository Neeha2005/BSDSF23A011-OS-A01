# Makefile inside src/

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -I../include
AR      := ar
ARFLAGS := rcs

OBJDIR  := ../obj
BINDIR  := ../bin
LIBDIR  := ../lib

TARGET  := $(BINDIR)/client
LIBNAME := libmyutils.a
LIB     := $(LIBDIR)/$(LIBNAME)

# only the utility sources go into the library
UTIL_SOURCES := mystrfunctions.c myfilefunctions.c
UTIL_OBJECTS := $(patsubst %.c,$(OBJDIR)/%.o,$(UTIL_SOURCES))

# main stays separate
MAIN_OBJECT  := $(OBJDIR)/main.o

.PHONY: build run clean dirs

build: dirs $(TARGET)

dirs:
	mkdir -p $(OBJDIR) $(BINDIR) $(LIBDIR)

# compile any .c into obj dir
$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# build static library from utility objects
$(LIB): $(UTIL_OBJECTS)
	$(AR) $(ARFLAGS) $(LIB) $(UTIL_OBJECTS)

# link main with the static library
$(TARGET): $(MAIN_OBJECT) $(LIB)
	$(CC) $(CFLAGS) $(MAIN_OBJECT) $(LIB) -o $(TARGET)

run: build
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(BINDIR) $(LIBDIR)

