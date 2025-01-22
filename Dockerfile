# Use Ubuntu as base image
FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    python3 \
    python3-pip \
    git \
    python3-tk \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy the project files
COPY . .

# Install Python dependencies
RUN pip3 install matplotlib numpy

# Add missing includes for math functions
RUN for file in src/*.cpp; do \
    if [ -f "$file" ]; then \
        echo '#include <cmath>' > /tmp/includes && \
        echo '#include <limits>' >> /tmp/includes && \
        cat /tmp/includes "$file" > /tmp/temp && \
        mv /tmp/temp "$file"; \
    fi \
done

# Create build directory and build the C++ project
RUN mkdir -p build && \
    cd build && \
    cmake .. && \
    make && \
    chmod +x uav_simulation

# Set matplotlib to use a non-interactive backend
ENV MPLBACKEND=Agg

# Set the entry point to the Python script
CMD ["python3", "pathPrinter.py"]
