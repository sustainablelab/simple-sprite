EXE = main

$(EXE): $(EXE).c
	$(CC) $(EXE).c -o $(EXE) -Wall -Wextra -pedantic -std=c99
