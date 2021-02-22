FROM conanio/gcc7:latest

RUN apt-get update && apt-get install -y \
cppcheck \
clang \
clang-tidy \
clang-format \
&& rm -rf /var/lib/apt/lists/*

RUN mkdir build

CMD ["/bin/bash"]