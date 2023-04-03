FROM ubuntu:20.04

# Install dependencies
# Clone the "Hello World" application from the Qt GitHub repository
RUN git clone https://github.com/qt/qtbase.git && \
    cd qtbase/examples/widgets/widgets/hello

# Build the application using CMake
RUN mkdir build && \
    cd build && \
    cmake .. && \
    make -j16

# Run the application
CMD ["./hello"]
