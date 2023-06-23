set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR STM8)

set(BINUTILS_PATH ${STM8_TOOLCHAIN_DIR})
set(TOOLCHAIN_PREFIX ${STM8_TOOLCHAIN_DIR}/bin/)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER    "${TOOLCHAIN_PREFIX}sdcc" CACHE FILEPATH "C Compiler Path")
set(CMAKE_ASM_COMPILER  "${TOOLCHAIN_PREFIX}sdcc")
set(CMAKE_CXX_COMPILER  "${TOOLCHAIN_PREFIX}sdcc" CACHE FILEPATH "C++ Compiler Path")
set(CMAKE_OBJCOPY       "${TOOLCHAIN_PREFIX}sdobjcopy" CACHE INTERNAL "Objcopy tool")
set(CMAKE_C_STANDARD    11)
set(CMAKE_CXX_STANDARD  11)

# Disable compiler checks.
set(CMAKE_C_COMPILER_FORCED     TRUE)
set(CMAKE_CXX_COMPILER_FORCED   TRUE)
set(CMAKE_FIND_ROOT_PATH ${BINUTILS_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM   NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY   ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE   ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE   ONLY)