G++ = /usr/local/Cellar/gcc/5.3.0/bin/g++-5
OBJECTS = bin/main.o
FLAGS = -std=c++11 -Wall -Ofast \
	-I include \
	-Llibs -lglfw3 -lGLEW \
	-framework OpenGL
EXEC = dunjun

all: $(EXEC)
	./$(EXEC)

$(EXEC): $(OBJECTS)
	$(G++) $(FLAGS) $(OBJECTS) -o $(EXEC)

bin/main.o: src/main.cpp
	$(G++) $(FLAGS) -c src/main.cpp -o bin/main.o
