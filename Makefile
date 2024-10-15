SRCS = src/particle.c
main:
	gcc main.c src/particle.c src/physics.c -o main -Iinclude -lraylib -lm
