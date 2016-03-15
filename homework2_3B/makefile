all:fraction

sourse=main.c fraction.c
target=$(sourse:.c=.o)

fraction:$(target)
	gcc $^ -o $@

clean:
	rm *.o *.diff output.txt fraction

test:
	diff output.txt answer.txt
