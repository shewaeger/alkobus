cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 11)
set(PROJECT_NAME mega_power_driver)

set(${PROJECT_NAME}_BOARD mega)
set(ARDUINO_CPU atmega2560)
project(${PROJECT_NAME})

# Define additional source and header files or default arduino sketch files
# set(${PROJECT_NAME}_SRCS)
set(${PROJECT_NAME}_HDRS User_Setup.h)

### Additional static libraries to include in the target.
# set(${PROJECT_NAME}_LIBS)

### Main sketch file
set(${PROJECT_NAME}_SKETCH mega_power_driver.ino)

### Add project directories into the build
# add_subdirectory()

### Additional settings to add non-standard or your own Arduino libraries.
# For this example (libs will contain additional arduino libraries)
# An Arduino library my_lib will contain files in libs/my_lib/: my_lib.h, my_lib.cpp + any other cpp files

generate_arduino_library(
        ListUtils
        SRCS modules/list_utils/list_utils.cpp
        HDRS modules/list_utils/list_utils.h
        BOARD ${${PROJECT_NAME}_BOARD}
)

generate_arduino_library(
        EventBus
        SRCS modules/EventBus/EventBus.cpp
        HDRS modules/EventBus/EventBus.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS ListUtils
        )

generate_arduino_library(
        Keyboard
        SRCS modules/Keyboard/Keyboard.cpp
        HDRS modules/Keyboard/Keyboard.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS EventBus
)

generate_arduino_library(
        temperature
        SRCS modules/temperature/temperature.cpp
        HDRS modules/temperature/temperature.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS ListUtils EventBus
)

generate_arduino_library(
        voltage
        SRCS modules/voltage/voltage.cpp
        HDRS modules/voltage/voltage.h
        BOARD ${${PROJECT_NAME}_BOARD}
)

generate_arduino_library(
        TenSwitch
        SRCS modules/TenSwitch/TenSwitch.cpp
        HDRS modules/TenSwitch/TenSwitch.h
        BOARD ${${PROJECT_NAME}_BOARD}
)

generate_arduino_library(
        Speaker
        SRCS modules/Speaker/Speaker.cpp
        HDRS modules/Speaker/Speaker.h
        BOARD ${${PROJECT_NAME}_BOARD}
)

generate_arduino_library(
        Valve
        SRCS modules/Valve/Valve.cpp
        HDRS modules/Valve/Valve.h
        BOARD ${${PROJECT_NAME}_BOARD}
)

generate_arduino_library(
        Settings
        SRCS modules/Settings/Settings.cpp
        HDRS modules/Settings/Settings.h
        BOARD ${${PROJECT_NAME}_BOARD}
)

generate_arduino_library(
        LcdOverflowString
        SRCS modules/LcdOverflowString/LcdOverflowString.cpp
        HDRS modules/LcdOverflowString/LcdOverflowString.h
        BOARD ${${PROJECT_NAME}_BOARD}
)

generate_arduino_library(
        ModManager
        SRCS modules/ModManager/ModManager.cpp
        HDRS modules/ModManager/ModManager.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS voltage temperature Keyboard EventBus Valve Settings TenSwitch Speaker
)

generate_arduino_library(
        Program
        SRCS modules/Program/Program.cpp
        HDRS modules/Program/Program.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS ModManager EventBus
)
generate_arduino_library(
        EmptyProgram
        SRCS modules/EmptyProgram/EmptyProgram.cpp
        HDRS modules/EmptyProgram/EmptyProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program
)
generate_arduino_library(
        AlkobusMenu
        SRCS modules/AlkobusMenu/AlkobusMenu.cpp
        HDRS modules/AlkobusMenu/AlkobusMenu.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program
)

generate_arduino_library(
        VoltageProgram
        SRCS modules/VoltageProgram/VoltageProgram.cpp
        HDRS modules/VoltageProgram/VoltageProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program
)
generate_arduino_library(
        TemperatureProgram
        SRCS modules/TemperatureProgram/TemperatureProgram.cpp
        HDRS modules/TemperatureProgram/TemperatureProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program
)
generate_arduino_library(
        VariableSetProgram
        SRCS modules/VariableSetProgram/VariableSetProgram.cpp
        HDRS modules/VariableSetProgram/VariableSetProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program LcdOverflowString
)

generate_arduino_library(
        TimeSetProgram
        SRCS modules/TimeSetProgram/TimeSetProgram.cpp
        HDRS modules/TimeSetProgram/TimeSetProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program
)

generate_arduino_library(
        PWMScaleSetProgram
        SRCS modules/PWMScaleSetProgram/PWMScaleSetProgram.cpp
        HDRS modules/PWMScaleSetProgram/PWMScaleSetProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program
)

generate_arduino_library(
        ValveSettingsProgram
        SRCS modules/ValveSettingsProgram/ValveSettingsProgram.cpp
        HDRS modules/ValveSettingsProgram/ValveSettingsProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program LcdOverflowString TimeSetProgram PWMScaleSetProgram EmptyProgram
)

generate_arduino_library(
        FindThermometerProgram
        SRCS modules/FindThermometerProgram/FindThermometerProgram.cpp
        HDRS modules/FindThermometerProgram/FindThermometerProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program
)

generate_arduino_library(
        ProcessSettingsProgram
        SRCS modules/ProcessSettingsProgram/ProcessSettingsProgram.cpp
        HDRS modules/ProcessSettingsProgram/ProcessSettingsProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program AlkobusMenu PWMScaleSetProgram EmptyProgram AlkobusMenu
)

generate_arduino_library(
        PrimarySelectionProgram
        SRCS modules/PrimarySelectionProgram/PrimarySelectionProgram.cpp
        HDRS modules/PrimarySelectionProgram/PrimarySelectionProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program
)

generate_arduino_library(
        PrimarySelectionSettingsProgram
        SRCS modules/PrimarySelectionSettingsProgram/PrimarySelectionSettingsProgram.cpp
        HDRS modules/PrimarySelectionSettingsProgram/PrimarySelectionSettingsProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program ValveSettingsProgram EmptyProgram
)

generate_arduino_library(
        WarmingUpProgram
        SRCS modules/WarmingUpProgram/WarmingUpProgram.cpp
        HDRS modules/WarmingUpProgram/WarmingUpProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program PrimarySelectionProgram PrimarySelectionSettingsProgram
)

generate_arduino_library(
        SoundProgram
        SRCS modules/SoundProgram/SoundProgram.cpp
        HDRS modules/SoundProgram/SoundProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program AlkobusMenu EmptyProgram
)

generate_arduino_library(
        DeltaCorrectionProgram
        SRCS modules/DeltaCorrectionProgram/DeltaCorrectionProgram.cpp
        HDRS modules/DeltaCorrectionProgram/DeltaCorrectionProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program AlkobusMenu EmptyProgram
)

generate_arduino_library(
        ExtendedTimeMessageProgram
        SRCS modules/ExtendedTimeMessageProgram/ExtendedTimeMessageProgram.cpp
        HDRS modules/ExtendedTimeMessageProgram/ExtendedTimeMessageProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program AlkobusMenu EmptyProgram
)

generate_arduino_library(
        ProcessProgram
        SRCS modules/ProcessProgram/ProcessProgram.cpp
        HDRS modules/ProcessProgram/ProcessProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program
)

generate_arduino_library(
        MainProcessProgram
        SRCS modules/MainProcessProgram/MainProcessProgram.cpp
        HDRS modules/MainProcessProgram/MainProcessProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program PrimarySelectionProgram PrimarySelectionSettingsProgram WarmingUpProgram SoundProgram DeltaCorrectionProgram ExtendedTimeMessageProgram ProcessProgram
)

generate_arduino_library(
        SettingsProgram
        SRCS modules/SettingsProgram/SettingsProgram.cpp
        HDRS modules/SettingsProgram/SettingsProgram.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program EmptyProgram AlkobusMenu VoltageProgram ValveSettingsProgram VariableSetProgram TimeSetProgram ProcessSettingsProgram FindThermometerProgram
)

generate_arduino_library(
        MainMenu
        SRCS modules/MainMenu/MainMenu.cpp
        HDRS modules/MainMenu/MainMenu.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program VoltageProgram AlkobusMenu SettingsProgram MainProcessProgram
)

generate_arduino_library(
        ProgramManager
        SRCS modules/ProgramManager/ProgramManager.cpp
        HDRS modules/ProgramManager/ProgramManager.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS MainMenu
)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/modules)

# For nested library sources replace ${LIB_NAME} with library name for each library
# set(_RECURSE true)

#### Additional settings for programmer. From programmers.txt
# set(${PROJECT_NAME}_PROGRAMMER avrispmkii)
#set(${PROJECT_NAME}_PORT /dev/ttyUSB0)
set(${PROJECT_NAME}_PORT COM12)

set(mega.upload.speed 9600)

## Verbose build process
set(${PROJECT_NAME}_AFLAGS -v)

generate_arduino_firmware(${PROJECT_NAME} LIBS ModManager ProgramManager)
