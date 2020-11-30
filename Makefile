OBJS	= bucket.o hashTable.o list.o main.o vertex.o
SOURCE	= bucket.cpp hashTable.cpp list.cpp main.cpp vertex.cpp
HEADER	= bucket.h hashTable.h list.h vertex.h
OUT	= project1
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

bucket.o: bucket.cpp
	$(CC) $(FLAGS) bucket.cpp -std=c++14

hashTable.o: hashTable.cpp
	$(CC) $(FLAGS) hashTable.cpp -std=c++14

list.o: list.cpp
	$(CC) $(FLAGS) list.cpp -std=c++14

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++14

vertex.o: vertex.cpp
	$(CC) $(FLAGS) vertex.cpp -std=c++14


clean:
	rm -f $(OBJS) $(OUT)
