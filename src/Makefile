CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -I../include -fPIC

OBJDIR  := ../obj
BINDIR  := ../bin
LIBDIR  := ../lib

TARGET  := $(BINDIR)/client_dynamic
LIBNAME := libmyutils.so
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

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# build dynamic library from utility objects
$(LIB): $(UTIL_OBJECTS)
	$(CC) -shared -o $(LIB) $(UTIL_OBJECTS)

# link main with the dynamic library
$(TARGET): $(MAIN_OBJECT) $(LIB)
	$(CC) $(CFLAGS) $(MAIN_OBJECT) -L$(LIBDIR) -lmyutils -o $(TARGET)

run: build
	LD_LIBRARY_PATH=$(LIBDIR) ./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(BINDIR) $(LIBDIR)

PREFIX ?= /usr/local

install: build
	# install the binary
	install -d $(PREFIX)/bin
	install -m 755 ../bin/client_dynamic $(PREFIX)/bin/client

	# install man pages
	install -d $(PREFIX)/share/man/man1
	install -m 644 ../man/man3/*.1 $(PREFIX)/share/man/man1
