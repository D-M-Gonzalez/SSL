all: hello-world

hello-world: hello.o
	gcc hello.o -o hello_create_with_make

hello-world.o: hello.c
	gcc -c hello.c -std=c18

clean:
	del *.o, del hello_created_with_make.exe