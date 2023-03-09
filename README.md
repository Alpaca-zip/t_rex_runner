# t_rex_runner v0.2.2

Stay tuned for the development of the ROS-compatible dinosaur game! :ghost:  

<img src="https://user-images.githubusercontent.com/84959376/222948883-bc049a28-dd4c-4685-b61b-c1c6f5b9c1af.gif" width="500px">

- ROS noetic -> https://github.com/Alpaca-zip/t_rex_runner/tree/devel/ros-noetic

[![](https://img.shields.io/badge/Ubuntu20.04%20build-passing-green?style=flat-square&logo=Ubuntu)](https://github.com/Alpaca-zip/t_rex_runner) [![](https://img.shields.io/badge/Windows11%20build-passing-green?style=flat-square&logo=Windows)](https://github.com/Alpaca-zip/t_rex_runner) [![](https://img.shields.io/badge/ROS%20noetic%20build-passing-green?style=flat-square&logo=ros)](https://github.com/Alpaca-zip/t_rex_runner/tree/devel/ros-noetic)
___
## For Ubuntu
### Install SDL2
```
$ sudo apt-get install libsdl2-dev
$ sudo apt-get install libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev
```

### Build & Run
```
$ sudo bash build.sh
$ ./t_rex_runner.out
```
## For Windows
### Setup SDL2 (MinGW)
Please refer to the following article.  
- https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/mingw/index.php

### Build & Run
```
$ g++ game_node.cpp -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o t_rex_runner
$ t_rex_runner.exe
```
