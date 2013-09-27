
all: turtle eins.ps

eins.ps: eins.tlt turtle
	./turtle < eins.tlt > eins.ps

lex.yy.o:  lex.yy.c turtle_fsv5d.tab.h symtab.h
	gcc -c lex.yy.c

lex.yy.c: turtle_fsv5d.l
	flex turtle_fsv5d.l
	
turtle_fsv5d.tab.h: turtle_fsv5d.y
	bison -d turtle_fsv5d.y
	
turtle_fsv5d.tab.c: turtle_fsv5d.y
	bison -d turtle_fsv5d.y
	
turtle_fsv5d.tab.o: turtle_fsv5d.tab.c symtab.h
	gcc -c turtle_fsv5d.tab.c

turtle: turtle_fsv5d.tab.o lex.yy.o symtab.c
	gcc lex.yy.o turtle_fsv5d.tab.o symtab.c -lfl -o turtle

clean:
	rm -f turtle lex.* turtle_fsv5d.tab.* *.o eins.ps

