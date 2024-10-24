#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <version>"
  exit 1
fi

version=$1

check_line_in_file() {
  local line="$1"
  local file="$2"
  grep -Fxq "$line" "$file"
}

remove_line_from_file(){
  sed -i "/$1/d" "$2"
}

# Function to check which shell the user is using and append an alias
export_in_alias() {
  current_shell=$(basename "$SHELL")
  EXPORT_SH="$HOME/esp/esp-idf/export.sh"

  if [[ "$current_shell" == "bash" ]]; then
    BASH_ALIASES="$HOME/.bash_aliases"

    if [ -f "$BASH_ALIASES" ]; then
      if ! check_line_in_file "alias get_idf='source $EXPORT_SH'" "$BASH_ALIASES"; then
        echo "alias get_idf='source $EXPORT_SH'" >> "$BASH_ALIASES"
        echo "$EXPORT_SH sourced in .bash_aliases"
      else
        echo "$EXPORT_SH already exists in .bash_aliases"
      fi      
    else
      touch "$BASH_ALIASES"
      echo "alias get_idf='source $EXPORT_SH'" > "$BASH_ALIASES"
      echo "Created $BASH_ALIASES and appended alias get_idf='source $EXPORT_SH'"
    fi
    source "$BASH_ALIASES"

  elif [[ "$current_shell" == "zsh" ]]; then
    ZSH_ALIASES="$HOME/.zsh_aliases"

    if [ -f "$ZSH_ALIASES" ]; then
      if ! check_line_in_file "alias get_idf='source $EXPORT_SH'" "$ZSH_ALIASES"; then
        echo "alias get_idf='source $EXPORT_SH'" >> "$ZSH_ALIASES"
        echo "$EXPORT_SH sourced in .zsh_aliases"
      else
        echo "$EXPORT_SH already exists in .zsh_aliases"
      fi      
    else
      touch "$ZSH_ALIASES"
      echo "alias get_idf='source $EXPORT_SH'" > "$ZSH_ALIASES"
      echo "Created $ZSH_ALIASES and appended alias get_idf='source $EXPORT_SH'"
    fi
    source "$ZSH_ALIASES"
  else
    echo "Unsupported shell: $current_shell"
  fi
}

# Function to install Homebrew
install_brew() {
  echo "Homebrew is not installed. Installing Homebrew..."

  # Install Homebrew
  /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
  
  echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.zprofile
  eval "$(/opt/homebrew/bin/brew shellenv)"
}

# Function to create directory, clone repository, and install ESP-IDF
install_esp_idf() {
  local ESP_DIR="$HOME/esp"
  local version=$1

  mkdir -p "$ESP_DIR"
  cd "$ESP_DIR" || { echo "Failed to change directory to $ESP_DIR"; exit 1; }
  
  echo "Cloning ESP-IDF repository (version: $version)..."
  git clone -b "$version" --recursive https://github.com/espressif/esp-idf.git esp-idf || { echo "Failed to clone repository"; exit 1; }

  cd ./esp-idf || { echo "Failed to change directory to esp-idf"; exit 1; }

  echo "Running installation script for esp32..."
  ./install.sh esp32 || { echo "Failed to run installation script"; exit 1; }
}

# Function to install packages based on CentOS
install_centos_packages() {
  echo "Updating system..."
  sudo yum -y update
  echo "Installing git wget flex bison gperf python3 cmake ninja-build ccache dfu-util libusb"
  sudo yum install -y git wget flex bison gperf python3 cmake ninja-build ccache dfu-util libusb
}

# Function to install packages based on Arch Linux
install_arch_packages() {
  echo "Updating system..."
  sudo pacman -Syu --noconfirm
  echo "Installing gcc git make flex bison gperf python cmake ninja ccache dfu-util libusb"
  sudo pacman -S --needed --noconfirm gcc git make flex bison gperf python cmake ninja ccache dfu-util libusb

  if ! pacman -Q python-virtualenv &> /dev/null; then
    sudo pacman -S --noconfirm python-virtualenv
  fi
}

# Function to install packages based on Ubuntu/Debian
install_debian_packages() {
  echo "Updating system..."
  sudo apt-get update
  echo "Installing git wget flex bison gperf python3 python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0"
  sudo apt-get install -y git wget flex bison gperf python3 python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
}

# Function to install packages using Homebrew
install_macos_packages() {
  echo "Installing cmake, ninja, and dfu-util using Homebrew..."
  brew install cmake ninja dfu-util
}

# Function to install required packages based on distro
install_packages() {
  if command -v apt-get &> /dev/null; then
    install_debian_packages
  elif command -v pacman &> /dev/null; then
    install_arch_packages
  elif command -v yum &> /dev/null; then
    install_centos_packages
  elif [[ "$(uname -s)" == "Darwin" ]]; then
    if ! command -v brew &> /dev/null; then
      install_brew
    fi
    install_macos_packages
  else
    echo "Unsupported package manager. Install the required packages manually."
    exit 1
  fi
}

install_packages
install_esp_idf "$version"
export_in_alias

# Final message
echo "Run 'get_idf' in every new session to activate the esp-idf"
echo "Then run 'idf.py -help' to use the idf"
