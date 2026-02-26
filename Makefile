CC = g++
LIBS = 
FLAGS = -Wall -g -Wextra

demo : src/main.cpp
	$(CC) src/main.cpp -o build/demo $(FLAGS) $(LIBS)
