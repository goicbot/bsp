#######################################################################################################
# Project:   GOIC Firmware Framework (portable CMake template)
# Author:    Felipe Gómez
# Compatible with: STM32 / ARM Cortex / Native (Linux, macOS, Windows)
#######################################################################################################
cmake_minimum_required(VERSION 3.20)

# ------------------------- PROJECT CONFIG -------------------------
set(PROJECT_NAME "GOIC_BSP_STM32F401xC")
set(PROJECT_TYPE "exe")                      # exe | static-lib
project(${PROJECT_NAME} C ASM)

# Detect host platform
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Building on Linux host")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Building on Windows host")
endif()

# ------------------------- CHECK REQUIRED FILES -------------------------
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/Core/Source/system_stm32f4xx.c")
    message(FATAL_ERROR "Missing system_stm32f4xx.c in Core/Source/")
endif()

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/App/main.c")
    message(FATAL_ERROR "Missing main.c in App/")
endif()

# ------------------------- TOOLCHAIN INFO -------------------------
if(CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
endif()

# ------------------------- TARGET ARCHITECTURE -------------------------
if(CMAKE_C_COMPILER_ID MATCHES "GNU" AND CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    set(IS_ARM TRUE)
    set(MCPU "-mcpu=cortex-m4")
    set(MFPU "-mfpu=fpv4-sp-d16")
    set(MFLOAT_ABI "-mfloat-abi=softfp")
    set(MTHUMB "-mthumb")
    set(SYSCALLS "--specs=nosys.specs")
    set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/linker/STM32F401RCTX_FLASH.ld")
else()
    set(IS_ARM FALSE)
    set(MCPU "")
    set(MFPU "")
    set(MFLOAT_ABI "")
    set(MTHUMB "")
    set(SYSCALLS "")
    set(LINKER_SCRIPT "")
endif()

# ------------------------- SOURCE COLLECTION -------------------------
file(GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_SOURCE_DIR}/Core/Source/*.c"
    "${CMAKE_SOURCE_DIR}/Startup/*.s"
    "${CMAKE_SOURCE_DIR}/Bsp/Source/*.c"
    "${CMAKE_SOURCE_DIR}/App/*.c"
)

file(GLOB_RECURSE PROJECT_HEADERS
    "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include/*.h"
    "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include/*.h"
    "${CMAKE_SOURCE_DIR}/Core/Include/*.h"
    "${CMAKE_SOURCE_DIR}/Drivers/Include/*.h"
    "${CMAKE_SOURCE_DIR}/Bsp/Include/*.h"
    "${CMAKE_SOURCE_DIR}/App/*.h"
)

# ------------------------- INCLUDE DIRECTORIES -------------------------
set(PROJECT_INCLUDES
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include
    ${CMAKE_SOURCE_DIR}/Core/Include
    ${CMAKE_SOURCE_DIR}/Bsp/Include
    ${CMAKE_SOURCE_DIR}/App
)

# Add Newlib includes if ARM GCC
if(IS_ARM)
    set(ARM_NEWLIB_INCLUDE "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/14.3 rel1/arm-none-eabi/include")
    include_directories(${ARM_NEWLIB_INCLUDE})
    add_definitions(-DUSE_SYS_TIME)
endif()

# ------------------------- BUILD TYPE -------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# ------------------------- TARGET SETUP -------------------------
enable_language(ASM)

if(PROJECT_TYPE STREQUAL "exe")
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
elseif(PROJECT_TYPE STREQUAL "static-lib")
    add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDES})

# ------------------------- COMPILER OPTIONS -------------------------
target_compile_options(${PROJECT_NAME} PRIVATE
    ${MCPU} ${MTHUMB} ${MFPU} ${MFLOAT_ABI}
    -std=gnu11 -Wall -Wextra -Werror
)

# ------------------------- DEFINES -------------------------
target_compile_definitions(${PROJECT_NAME} PRIVATE
    STM32F401xC
    USE_CMSIS
)

# ------------------------- LINKER FLAGS -------------------------
if(IS_ARM AND LINKER_SCRIPT)
    if(NOT EXISTS ${LINKER_SCRIPT})
        message(FATAL_ERROR "Linker script not found: ${LINKER_SCRIPT}")
    endif()

    target_link_options(${PROJECT_NAME} PRIVATE
        -T${LINKER_SCRIPT}
        ${SYSCALLS}
        -Wl,-Map=${PROJECT_NAME}.map
        -Wl,--gc-sections
        -static
        -Wl,--start-group -lc -lm -Wl,--end-group
    )
endif()

# ------------------------- POST BUILD -------------------------
# Ensure tools are defined
if(IS_ARM)
    if(NOT CMAKE_OBJCOPY)
        set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
    endif()
    if(NOT CMAKE_SIZE)
        set(CMAKE_SIZE arm-none-eabi-size)
    endif()

    set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/output)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMENT "Generating binary and hex files in ${OUTPUT_DIR}..."
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}> ${OUTPUT_DIR}/${PROJECT_NAME}.bin
        COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${PROJECT_NAME}> ${OUTPUT_DIR}/${PROJECT_NAME}.hex
        COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}>
    )
endif()

# ------------------------- MESSAGES -------------------------
message(STATUS "CMake configuration loaded successfully!")
message(STATUS "Project: ${PROJECT_NAME}")
if(IS_ARM)
    message(STATUS "Target: ARM Cortex-M4")
else()
    message(STATUS "Target: Native / Host compilation")
endif()
