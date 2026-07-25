all:
	gcc -o main main.c encoder.c decoder.c formatter.c -lm -fsanitize=address -g
	./main

clean:
	rm main
	rm output/*