ifndef VERBOSE
.SILENT:
endif

flags = -std=c23 -g -fsanitize=address
build/shell: make_build src/shell.c build/lib.o
	gcc -o build/shell $(flags) -I lib/include src/shell.c build/lib.o

build/lib.o: lib/src/String.c lib/include/String.h
	gcc -o build/lib.o $(flags) -c -I lib/include lib/src/String.c

.PHONY: make_build
make_build:
	mkdir -p build

.PHONY: clean
clean:
	rm -r build

