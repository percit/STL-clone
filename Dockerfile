FROM carlonluca/qt-dev:5.15.8-lts-lgpl

RUN mkdir /app
COPY . /app
WORKDIR /app

RUN mkdir build && cd build && \
    cmake .. && \
    make -j16
