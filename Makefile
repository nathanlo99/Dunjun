G++ = /usr/local/Cellar/gcc/5.3.0/bin/g++-5
OBJECTS = bin/main.o bin/ShaderProgram.o
FLAGS = -std=c++11 -Ofast \
	-I include \
	-Llibs -lglfw3 -lGLEW \
	-framework OpenGL
WARNINGS = -pedantic -Wall -Wextra -Werror -Wno-unused
EXEC = main

all: $(EXEC)
	./$(EXEC)

$(EXEC): $(OBJECTS)
	$(G++) $(WARNINGS) $(FLAGS) $(OBJECTS) -o $(EXEC)

bin/%.o: src/%.cpp
	$(G++) $(WARNINGS) $(FLAGS) -c $< -o $@

bin/%.o: src/Dunjun/%.cpp
	$(G++) $(WARNINGS) $(FLAGS) -c $< -o $@
