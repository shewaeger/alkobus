cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 98)
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
        HDRS modules/voltage/voltage.cpp
        BOARD ${${PROJECT_NAME}_BOARD}
)

generate_arduino_library(
        ModManager
        SRCS modules/ModManager/ModManager.cpp
        HDRS modules/ModManager/ModManager.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS voltage temperature Keyboard EventBus
)

generate_arduino_library(
        Program
        SRCS modules/Program/Program.cpp
        HDRS modules/Program/Program.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS ModManager EventBus
)

generate_arduino_library(
        TemperatureProgram
        SRCS modules/TemperatureProgram/TemperatureProgram.cpp
        HDRS modules/TemperatureProgram/TemperatureProgram.h
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
        MainMenu
        SRCS modules/MainMenu/MainMenu.cpp
        HDRS modules/MainMenu/MainMenu.h
        BOARD ${${PROJECT_NAME}_BOARD}
        LIBS Program TemperatureProgram VoltageProgram
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
set(${PROJECT_NAME}_PORT /dev/ttyUSB0)
set(mega.upload.speed 9600)

## Verbose build process
set(${PROJECT_NAME}_AFLAGS -v)

generate_arduino_firmware(${PROJECT_NAME} LIBS ModManager ProgramManager)
