### There are the following verbosity levels:

- `ESP_LOGV` - Verbose **(highest)**
- `ESP_LOGD` - Debug
- `ESP_LOGI` - Info **(Default)**
- `ESP_LOGW` - Warning
- `ESP_LOGE` - Error **(lowest)**

+ By default the Debug and Verbose are turned off 
+ If we set the verbosity level as **Info** this sets the minimal level to Info
+ All the verbosity levels above Info are enabled and the ones below it are disabled.

- `ESP_LOGV` - Verbose **(highest) (Not included)**
- `ESP_LOGD` - Debug **(Not included)**   
- -> `ESP_LOGI` - Info **(lowest)**
- -> `ESP_LOGW` - Warning **(Included)**
- -> `ESP_LOGE` - Error **(Included)**

### The logging library provides three ways for setting log verbosity:

1. **At compile time** - in menuconfig, set the verbosity level using the option `CONFIG_LOG_DEFAULT_LEVEL`  
- Optionally, also in menuconfig, set the maximum verbosity level using the option `CONFIG_LOG_MAXIMUM_LEVEL`. By default, this is the same as the default level, but it can be set higher in order to compile more optional logs into the firmware.

2. **At runtime** - all logs for verbosity levels lower than `CONFIG_LOG_DEFAULT_LEVEL` are enabled by default.   
- The function `esp_log_level_set()` can be used to set a logging level on a per-module basis.    


3. **At runtime** - if `CONFIG_LOG_MASTER_LEVEL` is enabled then a Master logging level can be set using `esp_log_set_level_master()`. 
- This option adds an additional logging level check for all compiled logs. 
- Note that this will increase application size. 
- This feature is useful if you want to compile a lot of logs that are selectable at runtime, but also want to avoid the performance hit from looking up the tags and their log level when you don't want log output.

### Example

```
static const char* TAG1 = "LOG1";
static const char* TAG2 = "LOG2";

esp_log_level_set(TAG1, ESP_LOG_WARNING);

ESP_LOGE(TAG1, "This is an error");
ESP_LOGW(TAG1, "This is a warning");
ESP_LOGI(TAG1, "This is an info");
ESP_LOGD(TAG1, "This is a Debug");
ESP_LOGV(TAG1, "This is Verbose");

// The LOG1 will print only upto warning.

esp_log_level_set(TAG2, ESP_LOG_);

ESP_LOGE(TAG2, "This is an error %d", number++);
ESP_LOGW(TAG2, "This is a warning %d", number++);
ESP_LOGI(TAG2, "This is an info %d", number++);
ESP_LOGD(TAG2, "This is a Debug %d", number++);
ESP_LOGV(TAG2, "This is Verbose %d", number++);

// Whereas LOG2 will print upto info
```