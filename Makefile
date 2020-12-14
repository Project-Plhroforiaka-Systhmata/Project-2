OBJS	= main.o vertex.o list.o bucket.o hashTable.o negativeList.o
SOURCE	= main.cpp vertex.cpp list.cpp bucket.cpp hashTable.cpp negativeList.cpp
HEADER	= vertex.h list.h bucket.h hashTable.h negativeList.h
OUT	= project2
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++14

vertex.o: vertex.cpp
	$(CC) $(FLAGS) vertex.cpp -std=c++14

list.o: list.cpp
	$(CC) $(FLAGS) list.cpp -std=c++14

bucket.o: bucket.cpp
	$(CC) $(FLAGS) bucket.cpp -std=c++14

hashTable.o: hashTable.cpp
	$(CC) $(FLAGS) hashTable.cpp -std=c++14

negativeList.o: negativeList.cpp
	$(CC) $(FLAGS) negativeList.cpp -std=c++14


clean:
	rm -f $(OBJS) $(OUT)
