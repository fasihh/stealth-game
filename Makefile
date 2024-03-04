path := "C:\Users\FASIH PC\Desktop\code\practice sfml\stealth\src
files.cpp := main.cpp player.cpp game.cpp entity.cpp enemy.cpp
files.o := main.o player.o game.o entity.o enemy.o

all: compile link

compile:
	g++ -Isfml/include -c ${files.cpp} -DSFML_STATIC

link:
	g++ ${files.o} -o main -Lsfml/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32

clean:
	erase -f main *.o