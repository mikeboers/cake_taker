
EXE ?= example
SRC ?= cake_taker_template.c

.PHONY: build clean

.DEFAULT: build

build: $(EXE)

$(EXE): $(SRC)
	gcc -o $@ -g -fno-stack-protector -D_FORTIFY_SOURCE=0 $(PACKER_ARGS) $^

clean:
	rm cake_taker