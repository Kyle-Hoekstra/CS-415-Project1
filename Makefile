all : pseudo-shell
	
	
pseudo-shell: main.o lab1_skeleton.o string_parser.o command.o
	gcc -o pseudo-shell main.o lab1_skeleton.o string_parser.o command.o
	
main.o: main.c
	gcc -c -g main.c

lab1_skeleton.o: lab1_skeleton.c lab1_skeleton.h
	gcc -c -g lab1_skeleton.c
	
string_parser.o: string_parser.c string_parser.h
	gcc -c -g string_parser.c

command.o: command.c command.h
	gcc -c -g command.c

clean:
	rm -f core *.o project1.exe
