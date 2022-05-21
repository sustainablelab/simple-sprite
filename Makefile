EXE = main
CFLAGS = -Wall -Wextra -pedantic -std=c99
CFLAGS_SDL = `pkg-config --cflags sdl2`
LIBS_SDL = `pkg-config --libs sdl2`


$(EXE): $(EXE).c
	$(CC) $(EXE).c -o $(EXE) $(CFLAGS) $(CFLAGS_SDL) $(LIBS_SDL)

parse: parse.c
	$(CC) $< -o $@ $(CFLAGS)

read-file: read-file.c
	$(CC) $< -o $@ $(CLFAGS)

.PHONY: tags
tags:
	ctags --c-kinds=+l --exclude=Makefile -R .

.PHONY: lib-tags
lib-tags: $(EXE).c
	$(CC) $(CFLAGS) $^ -M > headers-windows.txt
	python.exe parse-lib-tags.py
	rm -f headers-windows.txt
	ctags -f lib-tags --c-kinds=+p -L headers-posix.txt
	rm -f headers-posix.txt
