.PHONY: all build compile run echo clean

all: build compile run

build:
	@cmake -B build -S . > /dev/null
	@cmake --build build > /dev/null

compile: build
	@./build/nary examples/main.na main

run:
	@./main

echo:
	@echo $$?

clean:
	@rm -rf build main
