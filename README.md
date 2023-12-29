<h1 align="center"><a href="https://www.youtube.com/watch?v=J8zc8mMNKtc&t=410s">Getting Started with espidf</a></h1>

### Contents
- [Script install](#install-through-script)
- [Manual install](#manual-install)
- [Create project](#create-project)
- [File structure](#file-structure)
- [Project workflow](#project-workflow-configuration)

---

## Install through script

### To automate the below steps run the [install_script.sh](install.sh). on Linux system

**Download or copy the script in new file and make the script executable**

```
chmod +x install_script.sh
```

**Run the script passing the latest idf version**

```
./install_script.sh
```

## Manual install

**First Install dependencies**
```
sudo apt-get install git wget flex bison gperf python3 python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
```

**Make a new directory and navigate inisde to clone the espidf repository from github**   
**Note: the latest relaease is 5.1.2 as of now, it might change in the future, make sure you put in the right version**

```
mkdir -p ~/esp
```
```
cd ~/esp
```

```
git clone -b v5.1.2 -recursive https://github.com/espressif/esp-idf.git
```
```
cd ./esp-idf
```


**Install and export**

```
./install.sh esp32
```
```
. ./export.sh 
```

**Run the idf**

```
idf.py -help
```

## Create project

```
idf.py create-project my_project
```

## File structure

```
- my_project
  - main/
    - my_project.c
    - CMakeLists.txt
  - CMakeLists.txt
```

- The **`CMakeLists.txt`** at the project level declares the entire project.
- **`main`** folder contains the **`project`** and another **`CMakeLists.txt`** file.
- The source file **`my_project.c`** contain the code with **`app_main()`** which is the enty point to the code  written by the user
- The **`CMakeLists.txt`** inside the main components is to register the main component

## Project Workflow (Configuration)

The workflow is divided into 4 steps   

### 1. Configure 

  - **Set configuration** options from each component

  ```
  idf.py set-target esp32
  ```

  - After configuring the project there are 2 new components added to the file structure
  1. The **build** directory
  2. The **sdkconfig** file which stores all the configuration values
  ```
  - my_project
    - main/
      - my_project.c
      - CMakeLists.txt
  - CMakeLists.txt
  - build
  - sdkconfig

  ```
   - Generate **sdkconfig** file

  ```
  idf.py menuconfig
  ```

### 2. Build

  - **Compile** source files from **all** components
  - **link** and generate the **project binary**

  ```
  idf.py all
  ```

  Note: To clean the build folder user. This is optional

  ```
  idf.py fullclean
  ```
  
  - The build system compiles all source files of all components 
  - But on repeated build it will compile on the source files which have been changed, so build speed increases
  - The build generates **3 binary files** i.e
  1. **Partition table**
  2. **Bootloader**
  3. **Application Binary**

### 3. Flash 

  - First find the serial port for ESP32 device in the `/dev` folder, most of the times it /`dev/ttyUSB0`

  ```
  ls /dev/ttyUSB*       
  ```

  - Reset the ESP-32 into **Firmware download mode**. 
  - Write the binary into **Flash memory**

  ```
  idf.py -p /dev/ttyUSB0 flash
  ```

### 4. Monitor

  - Reset the ESP-32 into execution mode.
  - Monitor the log output using **idf.py monitor**

  ```
  idf.py -p /dev/ttyUSB0 monitor
  ```

  
