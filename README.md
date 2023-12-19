# rendoom

weekend raycasting rendering engine made in c++

using an sfml project template from [here](https://github.com/danebulat/cmake-sfml-demo/tree/master/Pong)

sfml is only used for windowing and input. All rendering done by writing a pixel array to a texture

## building

### prerequisites
- cmake
- sfml
- any c++ compiler

### linux
1. `git clone https://github.com/yakkudev/rendoom.git`
2. `cd rendoom`
3. `mkdir build && cd build`
5. `cmake ..`
6. `make`

run the executable `rendoom`

### windows
set wsl up on your machine and follow the linux steps
