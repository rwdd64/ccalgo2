TARGET=a.exe
OBJS=main.o

all: $(OBJS)
	gcc obj/main.o -o bin/$(TARGET)

main.o: src/main.c
	gcc -c src/main.c -o obj/main.o

run: all
	./bin/$(TARGET)
