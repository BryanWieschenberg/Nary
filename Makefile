.PHONY: all build compile run echo clean

all: build compile run

build:
	cmake -B build -S .
	cmake --build build

compile: build
	./build/nary examples/main.na main

run:
	./build/main

echo:
	@echo $$?

clean:
	rm -rf build main
