CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -Wshadow -Werror -Warray-bounds=2 -Wwrite-strings -Wcast-qual -ggdb
#CFLAGS += -fsanitize-address-use-after-scope -fsanitize=undefined -fsanitize=leak -fsanitize-address-use-after-scope -fsanitize=bounds-strict -fsanitize=address -fsanitize=null -fsanitize-recover=all
CXXFLAGS := -O0 -g -std=c++11 -Wall -Wextra -Wshadow -pedantic -Weffc++ -Werror  
LDFLAGS := -lm 

decode: decode.c
	$(CC) $(CFLAGS) decode.c -o decode

.PHONY: clean

clean:
	rm -f decode
