#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <version>"
  exit 1
fi

version=$1

# Install required packages
sudo apt-get install git wget flex bison gperf python3 python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0

# Create directory and clone the repository
mkdir -p ~/esp
cd ~/esp
git clone -b "$version" --recursive https://github.com/espressif/esp-idf.git

# Navigate to the esp-idf directory and run installation script
cd ./esp-idf
./install.sh esp32

# Source the export script
source ./export.sh

# Run idf.py with the help option
echo "Successfull installed idf, you can not run idf.py -help" 

