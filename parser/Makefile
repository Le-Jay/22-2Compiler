CC = gcc

OBJS = main.o util.o lex.yy.o y.tab.o

ID : $(OBJS)
	$(CC) -g -o hw2_binary $(OBJS) -lfl

main.o : main.c util.h globals.h scan.h parse.h y.tab.h
	$(CC) -c main.c

util.o : util.c util.h globals.h y.tab.h
	$(CC) -c util.c

lex.yy.c : lex/tiny.l
	flex lex/tiny.l

lex.yy.o : lex.yy.c globals.h util.h scan.h
	$(CC) -c lex.yy.c

y.tab.c: yacc/tiny.y
	yacc -d -v yacc/tiny.y

y.tab.h: y.tab.c

y.tab.o: y.tab.c y.tab.h globals.h util.h scan.h parse.h
	$(CC) $(CFLAGS) -c y.tab.c

clean :
	rm *.o
	rm lex.yy.c
	rm y.tab.c
	rm y.tab.h
	rm y.output
	rm hw2_binary
	rm hw2_20170624.txt