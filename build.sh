g++ -o bin/main \
-I/users/labnet4/st6/djp468/.sfml/include \
src/main.cpp \
src/gui.cpp \
src/image.cpp \
src/map.cpp \
src/tile.cpp \
-L/users/labnet4/st6/djp468/.sfml/lib \
-lsfml-graphics \
-lsfml-window \
-lsfml-system
cd bin
./main
