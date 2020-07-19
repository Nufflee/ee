set -e

clang++ $(find src/ -type f -name "*.cpp") -Wall -Wextra -lSDL2 -lSDL2_ttf -Isrc/ -std=c++17 -ggdb -o build/editor
echo Compilation finished.
./build/editor