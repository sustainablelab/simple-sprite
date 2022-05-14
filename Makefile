EXE = main
CFLAGS = `pkg-config --cflags sdl2`
CFLAGS += -Wall -Wextra -pedantic -std=c99
LIBS = `pkg-config --libs sdl2`


$(EXE): $(EXE).c
	$(CC) $(EXE).c -o $(EXE) $(CFLAGS) $(LIBS)

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
