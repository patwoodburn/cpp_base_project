### Base project

the purpas of this project is to become a simple set of defaults for my future c++ prodjects



docker run -it --rm conanio/gcc7 /bin/bash
docker run -it -v$(pwd):/home/conan/project --rm conanio/gcc7 /bin/bash

conan install .. -s compiler.libcxx=libstdc++11 --build=missing && cmake .. && cmake --build . && make cppcheck