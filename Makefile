CXX = /usr/local/Cellar/gcc/5.3.0/bin/g++-5
OBJECTS = bin/main.o
CXXFLAGS = -std=c++11 -Wall -Ofast -I include -Llibs -lglfw3.3.1 -lglfw3.3 -lglfw3 -framework OpenGL
EXEC = dunjun

all: $(EXEC)
	@rm bin/*.o
	@echo "Executable built!"

run: $(EXEC)
	./$(EXEC)

clean: $(EXEC)
	rm $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

bin/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o bin/main.o
