# Tested on Ubuntu-20.04
cmake -S . -B build
cmake --build build
cd ./build/
mv t_rex_runner ../t_rex_runner.out
