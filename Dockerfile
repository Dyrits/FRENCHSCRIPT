# Use an official Ubuntu as a parent image
FROM --platform=linux/amd64 ubuntu:latest

# Set the environment variable
ARG FILE=main.frs

# Set the working directory
WORKDIR /usr/src/app

# Install necessary packages
RUN apt-get update && \
    apt-get install -y build-essential nasm cmake

# Copy the current directory contents into the container at /usr/src/app
COPY ./ ./

# Create build directory and run cmake and make
RUN mkdir -p build && cd build && cmake .. && make

# Run the frs executable with the specified file
RUN ./build/frs ${FILE}

# Start an interactive shell to keep the container running
CMD ["sh", "-c", "exec /bin/bash"]