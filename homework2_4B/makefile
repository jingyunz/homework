all:cup

sourse=main.c cup.c
target=$(sourse:.c=.o)

cup:$(target)
	gcc $^ -o $@

clean:
	rm *.o *.diff cup output.txt

test:
	diff output.txt answer.txt
