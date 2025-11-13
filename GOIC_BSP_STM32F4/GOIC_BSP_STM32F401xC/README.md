# DESCRIPTION

### PROJECT NAME: GOIC_BSP_STM32F401xC

### COMPANY: GOIC

### YEAR: 2025

# GOIC BSP STM32F401xC - Build Instructions

This README explains how to set up, configure, and build the project using **CMake**, **Ninja**, and **ARM GCC**. It also covers VSCode IntelliSense configuration and optional STM32CubeIDE usage.

---

## English Version

### 1. Prerequisites

1. **Install ARM GCC Toolchain**

   - Download from [ARM Developer](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)
   - Example installation path (Windows):

     ```
     C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\<version>\
     ```

2. **Install CMake**

   - Minimum version 3.20
   - [Download CMake](https://cmake.org/download/)

3. **Install Ninja**

   - [Download Ninja](https://ninja-build.org/)
   - Add Ninja to your `PATH`.

4. **Optional: VSCode**

   - Install the **C/C++ Extension** by Microsoft.
   - Configure IntelliSense for ARM GCC (see section below).

---

### 2. Configure Environment Variables

- Add ARM GCC binaries to your PATH (Windows example):

```bat
setx PATH "%PATH%;C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\<version>\bin"
```

- Verify from CMD:

```bat
arm-none-eabi-gcc --version
```

---

### 3. CMake Build Outside CubeIDE

1. Open CMD and navigate to the project root:

```bat
cd C:\path\to\GOIC_BSP_STM32F401xC
```

2. Create a build folder and configure with CMake using **Ninja** and the ARM toolchain:

```bat
cmake -S . -B build -G "Ninja Multi-Config" -DCMAKE_TOOLCHAIN_FILE=toolchain-arm-gcc.cmake
```

or

```bat
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=toolchain-arm-gcc.cmake
```

3. Build the project:

```bat
cmake --build build --config Debug
cmake --build build --config Release
```

or

```bat
cmake --build build
```

4. The output binaries (`.bin` and `.hex`) will be generated in `build/output`.

> **Note:** If you are using STM32CubeIDE, you can just build the project inside the IDE; no need for Ninja or an external toolchain.

---

### 4. VSCode IntelliSense Configuration

1. Create `.vscode/c_cpp_properties.json` in your project folder:

```json
{
  "configurations": [
    {
      "name": "STM32 ARM",
      "includePath": [
        "${workspaceFolder}/**",
        "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/<version>/arm-none-eabi/include",
        "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/<version>/arm-none-eabi/include/sys"
      ],
      "defines": ["STM32F401xC", "USE_CMSIS", "__GNUC__"],
      "compilerPath": "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/<version>/bin/arm-none-eabi-gcc.exe",
      "cStandard": "gnu11",
      "cppStandard": "gnu++17",
      "intelliSenseMode": "gcc-arm"
    }
  ],
  "version": 4
}
```

2. Reload VSCode window (`Ctrl+Shift+P → Reload Window`) to apply configuration.

> This ensures IntelliSense finds headers like `<sys/time.h>` and `<sys/times.h>` without errors.

---

## Versión en Español

### 1. Requisitos Previos

1. **Instalar ARM GCC Toolchain**

   - Descarga desde [ARM Developer](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)
   - Ejemplo de instalación (Windows):

     ```
     C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\<version>\
     ```

2. **Instalar CMake**

   - Versión mínima 3.20
   - [Descargar CMake](https://cmake.org/download/)

3. **Instalar Ninja**

   - [Descargar Ninja](https://ninja-build.org/)
   - Agregar Ninja al `PATH`.

4. **Opcional: VSCode**

   - Instalar la extensión **C/C++ de Microsoft**.
   - Configurar IntelliSense para ARM GCC (ver sección más abajo).

---

### 2. Configurar Variables de Entorno

- Agregar ARM GCC a tu `PATH` (ejemplo Windows):

```bat
setx PATH "%PATH%;C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\<version>\bin"
```

- Verificar desde CMD:

```bat
arm-none-eabi-gcc --version
```

---

### 3. Compilación con CMake fuera de CubeIDE

1. Abrir CMD y navegar a la raíz del proyecto:

```bat
cd C:\ruta\a\GOIC_BSP_STM32F401xC
```

2. Crear carpeta `build` y configurar CMake usando **Ninja** y toolchain ARM:

```bat
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=toolchain-arm-gcc.cmake
```

3. Compilar:

```bat
cmake --build build
```

4. Los binarios (`.bin` y `.hex`) se generarán en `build/output`.

> **Nota:** Si usas STM32CubeIDE, solo hace falta compilar dentro del IDE; no se necesita Ninja ni toolchain externo.

---

### 4. Configuración de IntelliSense en VSCode

1. Crear `.vscode/c_cpp_properties.json` en la carpeta del proyecto:

```json
{
  "configurations": [
    {
      "name": "STM32 ARM",
      "includePath": [
        "${workspaceFolder}/**",
        "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/<version>/arm-none-eabi/include",
        "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/<version>/arm-none-eabi/include/sys"
      ],
      "defines": ["STM32F401xC", "USE_CMSIS", "__GNUC__"],
      "compilerPath": "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/<version>/bin/arm-none-eabi-gcc.exe",
      "cStandard": "gnu11",
      "cppStandard": "gnu++17",
      "intelliSenseMode": "gcc-arm"
    }
  ],
  "version": 4
}
```

2. Recargar VSCode (`Ctrl+Shift+P → Reload Window`) para que los cambios tengan efecto.

> Esto asegura que IntelliSense encuentre headers como `<sys/time.h>` y `<sys/times.h>` sin errores.

---

**End of README / Fin del README**
