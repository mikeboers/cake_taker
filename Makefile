
EXE ?= example
SRC ?= cake_taker_template.c

.PHONY: build clean example

.DEFAULT: build

$(EXE): $(SRC)
	gcc -o $@ -g -std=c99 -fno-stack-protector -D_FORTIFY_SOURCE=0 $^

clean:
	rm $(EXE)
