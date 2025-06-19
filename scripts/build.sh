#!/bin/bash
# build.sh - Build script for Transportation Route Recommendation System
# ET234203 Final Project

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
PROJECT_NAME="TransportationRouteSystem"
BUILD_DIR="build"
BIN_DIR="bin"
LIB_DIR="lib"
OBJ_DIR="obj"

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to check dependencies
check_dependencies() {
    print_status "Checking dependencies..."
    
    # Check for required tools
    REQUIRED_TOOLS=("g++" "make" "cmake")
    MISSING_TOOLS=()
    
    for tool in "${REQUIRED_TOOLS[@]}"; do
        if ! command -v "$tool" &> /dev/null; then
            MISSING_TOOLS+=("$tool")
        fi
    done
    
    if [ ${#MISSING_TOOLS[@]} -ne 0 ]; then
        print_error "Missing required tools: ${MISSING_TOOLS[*]}"
        print_status "Please install missing tools:"
        print_status "  Ubuntu/Debian: sudo apt install build-essential cmake"
        print_status "  CentOS/RHEL: sudo yum groupinstall 'Development Tools' && sudo yum install cmake"
        exit 1
    fi
    
    print_success "All dependencies found"
}

# Function to create directories
create_directories() {
    print_status "Creating build directories..."
    
    DIRECTORIES=("$BUILD_DIR" "$BIN_DIR" "$LIB_DIR" "$OBJ_DIR")
    for dir in "${DIRECTORIES[@]}"; do
        if [ ! -d "$dir" ]; then
            mkdir -p "$dir"
            print_status "Created directory: $dir"
        fi
    done
    
    # Create subdirectories for object files
    OBJ_SUBDIRS=("core" "algorithms" "preferences" "io" "ui" "utils")
    for subdir in "${OBJ_SUBDIRS[@]}"; do
        mkdir -p "$OBJ_DIR/$subdir"
    done
    
    print_success "Build directories created"
}