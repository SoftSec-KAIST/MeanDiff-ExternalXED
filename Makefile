all: xed

xed: xed.c
	$(CC) -Wall -I./include -L./lib -o $@ $< -lxed

clean:
	rm -f xed

.PHONY: all clean
