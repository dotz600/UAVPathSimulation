# Use an official Python image as a base
FROM python:3.9

# Set the working directory
WORKDIR /app

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    x11-apps \
    python3-tk \
    nano \
    && rm -rf /var/lib/apt/lists/*


# Copy the entire project into the container
COPY . .

# Install Python dependencies
RUN pip install -r requirements.txt

# Create a build directory and compile the C++ code
RUN mkdir build && cd build && cmake .. && cmake --build .

# Set the command to run your Python script
CMD ["python", "pathPrinter.py"]