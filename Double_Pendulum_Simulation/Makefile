all: compile

test : compile run

compile:
	g++ double.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include/ -o prog -L/usr/local/Cellar/sfml/2.5.1_1/lib -lsfml-graphics -lsfml-window -lsfml-system
clean:
	del double.o
run:
	./prog