main: ./src/main.c
	cc -o ./build/main ./src/main.c -Wall -std=c99 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -latomic 
