
CC=clang

BIN=main

all: $(BIN)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ -lcurl


clean:
	$(RM) -rf $(BIN) *.dSYM