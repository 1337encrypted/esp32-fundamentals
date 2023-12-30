<h1 align="center"><a href="https://www.youtube.com/watch?v=J8zc8mMNKtc&t=410s">Getting Started with espidf</a></h1>

### Contents
- [Script install](#install-through-script)
- [Manual install](#manual-install)

---

## Install through script

### To automate the below steps run the [install_script.sh](install.sh). on Linux system

**Download or copy the script in new file and make the script executable**

```
chmod +x install_script.sh
```

**Run the script passing the latest idf version as the first argument as shown**

```
./install_script.sh v5.1.2
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


  