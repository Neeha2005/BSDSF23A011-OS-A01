# Makefile inside src/
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -I../include
OBJDIR  := ../obj
BINDIR  := ../bin
TARGET  := $(BINDIR)/client

SOURCES := mystrfunctions.c myfilefunctions.c main.c
OBJECTS := $(patsubst %.c,$(OBJDIR)/%.o,$(SOURCES))

.PHONY: build run clean dirs

build: dirs $(TARGET)

dirs:
	mkdir -p $(OBJDIR) $(BINDIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

run: build
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(BINDIR)
