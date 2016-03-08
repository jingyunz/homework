all:selectball

sourse=main.c cmp.c
obj=$(sourse:.c=.o)
selectball:$(obj)
	gcc $^ -o $@

clean:
	rm selectball

test:
	diff output.txt answer.txt
