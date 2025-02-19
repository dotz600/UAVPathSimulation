# utils.py - Utility functions
import os
import platform
import subprocess
import time
import matplotlib

def in_docker():
    """Check if the script is running inside a Docker container."""
    if platform.system() == 'Linux':
        return os.path.exists('/.dockerenv') or \
               any('docker' in line for line in open('/proc/1/cgroup', 'rt').readlines())
    return False  # Not running in Docker if not on Linux

def configure_matplotlib():
    """Configure the appropriate matplotlib backend based on environment."""
    if in_docker():
        matplotlib.use('Agg')  # Use a non-interactive backend in Docker
    else:
        matplotlib.use('TkAgg')

def find_executable(project_dir, exe_name="UAVPathSimulation"):
    """Find the executable in the project directory."""
    # Handle both .exe and no extension for different platforms
    exe_patterns = [f"{exe_name}.exe", exe_name]
    
    for root, dirs, files in os.walk(project_dir):
        for pattern in exe_patterns:
            if pattern in files:
                exe_path = os.path.join(root, pattern)
                print(f"Found executable at: {exe_path}")
                return exe_path
                
    raise FileNotFoundError(f"No {exe_name} executable found in {project_dir}")
