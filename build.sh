g++ -o bin/main \
-I/users/labnet4/st6/djp468/.sfml/include \
src/astar.cpp \
src/bfs.cpp \
src/gui.cpp \
src/image.cpp \
src/main.cpp \
src/map.cpp \
src/pathfinding.cpp \
src/tile.cpp \
-L/users/labnet4/st6/djp468/.sfml/lib \
-lsfml-graphics \
-lsfml-window \
-lsfml-system
cd bin
./main
