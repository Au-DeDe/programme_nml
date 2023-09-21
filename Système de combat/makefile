CC = g++ 
CPPFLAGS = -Wall -g -Iinclude/ 
OPT = -O3
SRC = main.cpp $(wildcard src/*.cpp)
OBJ = $(patsubst main.o, obj/main.o, $(patsubst src/%, obj/%, $(patsubst %.cpp, %.o, $(SRC))))

main : $(OBJ)
	$(CC) $(OPT) $^ -o $@

obj/main.o : main.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

obj/%.o : src/%.cpp include/%.hpp
	$(CC) -c $(CPPFLAGS) $< -o $@

.PHONY : clean 

clean : 
	rm -f obj/*.o main