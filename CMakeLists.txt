cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools")
include(toolchain)

project(stm8s_black
    LANGUAGES C
)

set(EXECUTABLE ${PROJECT_NAME}.elf)

file(GLOB SRC_FILES CMAKE_CONFIGURE_DEPENDS *.c)
file(GLOB_RECURSE SRC_FILES_RECURSE CMAKE_CONFIGURE_DEPENDS src/*.c)

add_executable(${EXECUTABLE}
    ${SRC_FILES}
    ${SRC_FILES_RECURSE}
)

target_include_directories(${EXECUTABLE} PRIVATE
    src/inc
    src/hal
)

target_link_options(${EXECUTABLE} PRIVATE
    -lstm8
    -mstm8
    --out-fmt-ihx
    #--out-fmt-elf

    --debug
    --opt-code-size
    --nogcse
    --std-sdcc11
    --verbose
    --fverbose-asm
    --all-callee-saves
    --stack-auto
    --float-reent
    --no-peep
)   
    
target_compile_definitions(${EXECUTABLE} PRIVATE 
    -DSTM8S105
)
target_compile_options(${EXECUTABLE} PRIVATE
    -lstm8
    -mstm8
    --out-fmt-ihx
    #--out-fmt-elf

    --debug
    --opt-code-size
    --nogcse
    --std-sdcc11
    --verbose
    --fverbose-asm
    --all-callee-saves
    --stack-auto
    --float-reent
    --no-peep
)