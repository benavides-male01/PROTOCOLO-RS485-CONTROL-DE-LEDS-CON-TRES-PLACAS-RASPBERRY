# Set minumum required version of CMake
cmake_minimum_required(VERSION 3.25)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(TP3_MICROS_II_RS485_MAESTRO C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Crear el ejecutable con todos los archivos fuente
add_executable(${PROJECT_NAME}
    main.c
    funciones.c
    systick.c
)
# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Inicializar el SDK de Pico
pico_sdk_init()

# Linkear el ejecutable con las librerías necesarias del SDK
target_link_libraries(${PROJECT_NAME}
    pico_stdlib        # Entradas/salidas estándar
    hardware_uart      # UART para RS485
    hardware_gpio      # Control de pines
    hardware_timer     # Si usás systick u otros
)

# Generar archivos de UF2, BIN, etc.
pico_add_extra_outputs(${PROJECT_NAME})

# Disable usb output, enable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)