G++ = /usr/local/Cellar/gcc/5.3.0/bin/g++-5
OBJECTS = bin/main.o bin/ShaderProgram.o
FLAGS = -std=c++11 \
	-I include \
	-Llibs -lglfw3 -lGLEW \
	-framework OpenGL
WARNINGS = -Wall
EXEC = main

all: $(EXEC)

run: $(EXEC)
	./$(EXEC)

$(EXEC): $(OBJECTS)
	@echo g++ $(WARNINGS) $(FLAGS) $(OBJECTS) -o $(EXEC)
	@$(G++) $(WARNINGS) $(FLAGS) $(OBJECTS) -o $(EXEC)

bin/%.o: src/%.cpp
	@echo g++ $(WARNINGS) $(FLAGS) -c $< -o $@
	@$(G++) $(WARNINGS) $(FLAGS) -c $< -o $@

bin/%.o: src/Dunjun/%.cpp
	@echo g++ $(WARNINGS) $(FLAGS) -c $< -o $@
	@$(G++) $(WARNINGS) $(FLAGS) -c $< -o $@
