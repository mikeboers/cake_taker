
cake_taker: cake_taker.c
	gcc -o $@ -g -fno-stack-protector -D_FORTIFY_SOURCE=0 $^

clean:
	rm cake_taker