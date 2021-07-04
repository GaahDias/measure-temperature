CC=gcc
all:
	$(CC) *.c -o measure-temperature `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0`
