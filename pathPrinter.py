import matplotlib.pyplot as plt
import subprocess
import time
import os
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

import numpy as np

os.chdir(os.path.dirname(os.path.abspath(__file__)))
project_dir = os.path.dirname(os.path.abspath(__file__))


def draw_points_from_file(file_path):
    """
    Reads points from a file and creates an animated plot with improved styling.

    Args:
        file_path (str): Path to the file containing points.
    """
    points = []

    # Read points from the file
    with open(file_path, 'r') as file:
        for line in file:
            try:
                line = line.strip().replace("(", "").replace(")", "")
                x, y = map(float, line.split(','))
                points.append((x, y))
            except ValueError:
                print(f"Skipping invalid line: {line.strip()}")

    if points:
        x_cords, y_cords = zip(*points)

        # Create figure with dark background style
        plt.style.use('dark_background')
        fig, ax = plt.subplots(figsize=(6, 6))
        fig.patch.set_facecolor('#1C1C1C')
        ax.set_facecolor('#1C1C1C')

        # Add a subtle grid
        ax.grid(True, linestyle='--', alpha=0.3, color='gray')

        # Plot the complete path
        ax.plot(x_cords, y_cords,
                linestyle='-',
                color='#4A90E2',  # Blue color
                alpha=0.5,
                linewidth=1.5,
                label='Complete Path')

        # Animation update function
        def update(frame):
            ax.clear()
            ax.grid(True, linestyle='--', alpha=0.3, color='gray')

            # Plot complete path with low opacity
            ax.plot(x_cords, y_cords,
                    linestyle='-',
                    color='#4A90E2',
                    alpha=0.3,
                    linewidth=1.5)

            # Plot the path up to current frame
            if frame > 0:
                ax.plot(x_cords[:frame], y_cords[:frame],
                        color='#00FF00',  # Bright green
                        linewidth=2,
                        label='Current Path')

            # Plot current position
            if frame > 0:
                ax.scatter(x_cords[frame - 1], y_cords[frame - 1],
                           color='#FF4444',  # Red
                           s=100,
                           label='UAV Position')

            # Add start and end markers
            ax.scatter(x_cords[0], y_cords[0],
                       color='#00FF00',
                       s=100,
                       marker='^',
                       label='Start')
            ax.scatter(x_cords[-1], y_cords[-1],
                       color='#FF0000',
                       s=100,
                       marker='*',
                       label='End')

            # Styling
            ax.set_title("UAV Path Visualization",
                         color='white',
                         fontsize=14,
                         pad=20)
            ax.set_xlabel("X Position", color='white')
            ax.set_ylabel("Y Position", color='white')
            ax.tick_params(colors='white')

            # Add legend
            ax.legend(loc='upper right',
                      facecolor='#1C1C1C',
                      edgecolor='gray',
                      labelcolor='white')

            # Maintain equal aspect ratio
            ax.set_aspect('equal')

            # Add margin around the path
            margin = max(max(x_cords) - min(x_cords),
                         max(y_cords) - min(y_cords)) * 0.1
            ax.set_xlim(min(x_cords) - margin, max(x_cords) + margin)
            ax.set_ylim(min(y_cords) - margin, max(y_cords) + margin)

        # Create animation
        anim = FuncAnimation(fig,
                             update,
                             frames=len(points),
                             interval=150,  # 50ms between frames
                             repeat=True)

        plt.tight_layout()
        plt.show()
    else:
        print("No valid points found in the file.")



def draw_points_from_file1(file_path):
    """
    Reads points from a file and plots them on an x, y space.

    Args:
        file_path (str): Path to the file containing points.
    """
    points = []

    # Read points from the file
    with open(file_path, 'r') as file:
        for line in file:
            try:
                # Remove parentheses and split by comma
                line = line.strip().replace("(", "").replace(")", "")
                x, y = map(float, line.split(','))
                points.append((x, y))
            except ValueError:
                print(f"Skipping invalid line: {line.strip()}")

    if points:
        x_cords, y_cords = zip(*points)

        plt.figure(figsize=(6, 6))
        plt.plot(x_cords, y_cords, marker='o', linestyle='-', color='blue', label='Path')
        plt.scatter(x_cords, y_cords, color='red', label='Points')
        plt.title("Path Orbit Visualization")
        plt.xlabel("X-axis")
        plt.ylabel("Y-axis")
        plt.grid(True)
        plt.legend()
        plt.axis('equal')  # Ensure equal scaling on both axes
        plt.show()
    else:
        print("No valid points found in the file.")


# Define the paths
cpp_program = os.path.join(project_dir, "x64", "Debug", "UAVPathSimulation.exe")
output_file = os.path.join(project_dir, "resources", "pathOutput.txt")

# Run the C++ program
try:
    start_time = time.time()
    result = subprocess.run([cpp_program], check=True, cwd=project_dir)
    end_time = time.time()
    elapsed_time = end_time - start_time
    print("C++ program executed successfully. " )
    print(f"Execution Time: {elapsed_time:.4f} seconds")

except subprocess.CalledProcessError as e:
    print(f"Error executing the C++ program: {e}")
    exit(1)

# Draw the points from the output file
draw_points_from_file(output_file)
