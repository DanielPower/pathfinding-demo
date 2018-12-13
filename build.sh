rm bin/main
clang++ -O3 -o bin/main \
-Wall \
-I./include \
src/astar.cpp \
src/bfs.cpp \
src/gui.cpp \
src/mapLoader.cpp \
src/main.cpp \
src/map.cpp \
src/pathfinding.cpp \
src/tile.cpp \
include/imgui.cpp \
include/imgui_draw.cpp \
include/imgui-SFML.cpp \
include/imgui_demo.cpp \
-L./lib \
-lsfml-graphics \
-lsfml-window \
-lsfml-system \
-lGL
cd bin
export LD_LIBRARY_PATH=../lib
./main
