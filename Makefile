G++ = /usr/local/Cellar/gcc/5.3.0/bin/g++-5
OBJECTS = bin/main.o bin/Dunjun/ShaderProgram.o bin/Dunjun/Texture.o bin/Dunjun/Image.o bin/Dunjun/Math/Vector2f.o bin/Dunjun/Math/Vector3f.o bin/Dunjun/Math/Vector4f.o bin/Dunjun/Math/Matrix4f.o bin/Dunjun/Math/Transform.o
FLAGS = -pipe -std=c++14 -Ofast \
	-I include \
	-Llibs -lglfw3 -lGLEW \
	-framework OpenGL
WARNINGS = -Wall -Wextra
EXEC = main

.PHONY: bin/main.o

all: $(EXEC)

debug: $(EXEC)
	gdb -ex "set environment MALLOC_CHECK_ 2" -ex "start" $(EXEC)

run: $(EXEC)
	./$(EXEC)

$(EXEC): $(OBJECTS)
	@echo g++ -g $(WARNINGS) $(FLAGS) $(OBJECTS) -o $(EXEC)
	@$(G++) $(WARNINGS) $(FLAGS) $(OBJECTS) -o $(EXEC)

bin/main.o: src/main.cpp
	@echo g++ $(WARNINGS) $(FLAGS) -c src/main.cpp -o bin/main.o
	@$(G++) $(WARNINGS) $(FLAGS) -c src/main.cpp -o bin/main.o

bin/Dunjun/%.o: src/Dunjun/%.cpp
	@echo g++ $(WARNINGS) $(FLAGS) -c $< -o $@
	@$(G++) $(WARNINGS) $(FLAGS) -c $< -o $@

bin/Dunjun/Math/%.o: src/Dunjun/Math/%.cpp
	@echo g++ $(WARNINGS) $(FLAGS) -c $< -o $@
	@$(G++) $(WARNINGS) $(FLAGS) -c $< -o $@
