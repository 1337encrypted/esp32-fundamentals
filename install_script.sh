#!/bin/bash

BASH_ALIASES="$HOME/.bash_aliases"
EXPORT_SH="$HOME/esp/esp-idf/export.sh"
ESP_DIR="$HOME/esp"

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <version>"
  exit 1
fi

version=$1

check_line_in_file(){
  grep -q "$1" "$2"
}

remove_line_from_file(){
  sed -i "/$1/d" "$2"
}

# Install required packages
sudo apt-get install git wget flex bison gperf python3 python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0

# Create directory and clone the repository
mkdir -p "$ESP_DIR"
cd "$ESP_DIR"
git clone -b "$version" --recursive https://github.com/espressif/esp-idf.git

# Navigate to the esp-idf directory and run installation script
cd ./esp-idf
./install.sh esp32

# Check if .bash_aliases exists
if [ -f "$BASH_ALIASES" ]; then
  # Check if the export line is already present
  if ! check_line_in_file "alias get_idf='source $EXPORT_SH'" "$BASH_ALIASES"; then
    echo "alias get_idf='source $EXPORT_SH'" >> "$BASH_ALIASES"
    echo "$EXPORT_SH sourced in .bash_aliases"
  else
    echo "$EXPORT_SH already exists in .bash_aliases"
  fi
else
  # If .bash_aliases doesn't exist, append the export line
  touch "$BASH_ALIASES"
  echo "alias get_idf='source $EXPORT_SH'" > "$BASH_ALIASES"
  echo "Created $BASH_ALIASES and appended alias get_idf='source $EXPORT_SH'"
fi

source "$BASH_ALIASES"

# Run idf.py with the help option
echo "run get_idf for in every new session to activate the esp-idf"
echo "Then run idf.py -help to use the idf" 