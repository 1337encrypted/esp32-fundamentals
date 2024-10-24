### Contents
- [Create project](#create-project)
- [File structure](#file-structure)
- [Project workflow](#project-workflow-configuration)

## Create project

- Before you do anything its important to activate the esp-idf virtual environment `get-idf`

- To create your project cd into desired folder and create the directory.

```
idf.py create-project -p <name>
```
NOTE: -p creates the file structure for the project.

## File structure

```
- my_project
  - main/
    - my_project.c
    - CMakeLists.txt
  - CMakeLists.txt
```

- The **`CMakeLists.txt`** at the project level declares the entire project.
- **`main folder`** contains the **`project`** and another **`CMakeLists.txt`** file.
- The source file **`my_project.c`** contain the code with **`app_main()`** which is the enty point to the code  written by the user
- The **`CMakeLists.txt`** inside the main components is to register the main component

### C++ compatibility 

- In order to convert the project to support C++ do the following changes in the main 

```
#include <stdio.h>

extern "C" {
    void app_main(void)
    {
      // Your code goes here
    }
}
```

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
