FROM nvidia/cuda:10.0-devel-ubuntu18.04 AS devel
MAINTAINER Carlos Osuna <Carlos.Osuna@meteoswiss.ch>
LABEL description="This is a gtclang container" 
RUN apt-get update                                                                                                              && \
    apt-get install -y clang-6.0 libclang-6.0-dev git cmake openssh-client python3.7                                            && \
    mkdir /usr/local/gtclang                                                                                                    && \
    chown -R 1001:1001 /usr/local/gtclang
ENV PYTHON_DIR $(which python3.7)
USER 1001
RUN cd /usr/local/gtclang                                                                                                       && \
    git clone https://github.com/MeteoSwiss-APN/gtclang.git                                                                     && \
    cd gtclang                                                                                                                  && \
    sed -i 's/git@github.com:MeteoSwiss-APN\/dawn.git/https:\/\/github.com\/MeteoSwiss-APN\/dawn.git/g' bundle/CMakeLists.txt   && \
    cd bundle/ && mkdir build && cd build && cmake -DPYTHON_EXECUTABLE="${PYTHON_DIR}" .. && make -j2 
CMD ["/usr/local/gtclang/bundle/install/bin/gtclang"]
