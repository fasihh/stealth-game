files.cpp := main.cpp src/player.cpp src/game.cpp src/entity.cpp src/enemy.cpp src/detection.cpp src/object.cpp
files.o := main.o player.o game.o entity.o enemy.o detection.o object.o

all: compile link

compile:
	g++ -Isfml/include -c ${files.cpp} -DSFML_STATIC

link:
	g++ ${files.o} -o main -Lsfml/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32

clean:
	erase -f main *.o