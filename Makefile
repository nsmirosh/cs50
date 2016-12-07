resize: clean resize.c
	cc -std=c99 resize.c -o resize
	./resize 2 small.bmp large.bmp

clean:
	rm -f large.bmp
