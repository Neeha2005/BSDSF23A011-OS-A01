# Top-level Makefile
.PHONY: all build run clean

all: build

build:
	$(MAKE) -C src build

run:
	$(MAKE) -C src run

clean:
	$(MAKE) -C src clean

