g++ -o bin/main \
src/main.cpp \
src/gui.cpp \
src/image.cpp \
src/map.cpp \
src/tile.cpp \
-lsfml-graphics \
-lsfml-window \
-lsfml-system
cd bin
./main
