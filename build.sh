g++ -o bin/main \
src/main.cpp \
src/gui.cpp \
-lsfml-graphics \
-lsfml-window \
-lsfml-system
cd bin
./main
