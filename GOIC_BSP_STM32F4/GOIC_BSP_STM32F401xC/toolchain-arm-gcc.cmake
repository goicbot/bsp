cmake_minimum_required(VERSION 3.16)

# ---------------------------------------------------------------------------
# SYSTEM
# ---------------------------------------------------------------------------
set(CMAKE_SYSTEM_NAME Generic CACHE INTERNAL "")
set(CMAKE_SYSTEM_PROCESSOR arm CACHE INTERNAL "")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# ---------------------------------------------------------------------------
# TOOLCHAIN DETECTION
# ---------------------------------------------------------------------------
find_program(ARM_GCC arm-none-eabi-gcc)
if (NOT ARM_GCC)
    message(STATUS "ARM GCC not found in PATH — configuring CubeIDE toolchain path")

    if (WIN32)
        set(CUBEIDE_TOOLCHAIN_PATH
            "C:/ST/STM32CubeIDE_1.19.0/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.13.3.rel1.win32_1.0.0.202411081344/tools/bin")

        set(ENV{PATH} "$ENV{PATH};${CUBEIDE_TOOLCHAIN_PATH}")
    endif()
endif()

set(TOOLCHAIN_PREFIX arm-none-eabi-)

# ---------------------------------------------------------------------------
# COMPILER BINARIES
# ---------------------------------------------------------------------------
set(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)

set(CMAKE_AR      ${TOOLCHAIN_PREFIX}ar)
set(CMAKE_RANLIB  ${TOOLCHAIN_PREFIX}ranlib)
set(CMAKE_LINKER  ${TOOLCHAIN_PREFIX}ld)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}objdump)
set(CMAKE_SIZE    ${TOOLCHAIN_PREFIX}size)

# ---------------------------------------------------------------------------
# SEARCH PATH RULES
# ---------------------------------------------------------------------------
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# ---------------------------------------------------------------------------
# DEFAULT FLAGS
# ---------------------------------------------------------------------------
set(CMAKE_C_FLAGS_INIT
    "-mcpu=cortex-m4 -mthumb -ffunction-sections -fdata-sections")

set(CMAKE_CXX_FLAGS_INIT
    "-mcpu=cortex-m4 -mthumb -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections")

set(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,--gc-sections")
