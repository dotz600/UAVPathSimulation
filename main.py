# main.py - Main execution script
import os
import time
import subprocess
from utils import find_executable, configure_matplotlib
from visualizer import draw_points_from_file

# Configure matplotlib at the beginning
configure_matplotlib()

def run_cpp_program(project_dir):
    """Run the C++ UAV simulation program and visualize results."""
    try:
        start_time = time.time()
        
        exe_path = find_executable(project_dir)
        result = subprocess.run([exe_path], check=True, cwd=project_dir)
        
        end_time = time.time()
        elapsed_time = end_time - start_time
        print("C++ program executed successfully.")
        print(f"Execution Time: {elapsed_time:.4f} seconds")
        
        # Draw the points from the output file
        cpp_path_output = os.path.join(project_dir, "resources", "pathOutput.txt")
        draw_points_from_file(cpp_path_output)
        
        return True
    except subprocess.CalledProcessError as e:
        print(f"Error executing the C++ program: {e}")
        return False
    except FileNotFoundError as e:
        print(f"Error: {e}")
        return False

def main():
    """Main entry point of the program."""
    project_dir = os.path.dirname(os.path.abspath(__file__))
    success = run_cpp_program(project_dir)
    if not success:
        exit(1)

if __name__ == "__main__":
    main()
