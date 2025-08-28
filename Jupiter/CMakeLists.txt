cmake_minimum_required(VERSION 3.16)
project(jupiter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(VERILOG_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/hardware/top.v
)

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/module/module.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/files/fileInput.cpp
    /usr/share/verilator/include/verilated.cpp
    /usr/share/verilator/include/verilated_vcd_c.cpp
)

set(VERILATOR_OUTPUT_DIR ${CMAKE_BINARY_DIR}/verilated)

# Run Verilator
add_custom_command(
    OUTPUT ${VERILATOR_OUTPUT_DIR}/Vtop.mk ${VERILATOR_OUTPUT_DIR}/Vtop.h
    COMMAND verilator --cc ${VERILOG_SOURCES}
            -Mdir ${VERILATOR_OUTPUT_DIR}
            -trace
    DEPENDS ${VERILOG_SOURCES}
    COMMENT "Running Verilator..."
)

# Build verilated model
add_custom_command(
    OUTPUT ${VERILATOR_OUTPUT_DIR}/Vtop__ALL.a
    COMMAND make -C ${VERILATOR_OUTPUT_DIR} -f Vtop.mk
    DEPENDS ${VERILATOR_OUTPUT_DIR}/Vtop.mk ${VERILATOR_OUTPUT_DIR}/Vtop.h
    COMMENT "Building Verilated model..."
)

add_custom_target(top_generated
    DEPENDS ${VERILATOR_OUTPUT_DIR}/Vtop__ALL.a
)

add_executable(top ${CPP_SOURCES})

target_include_directories(top PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/module
    ${CMAKE_CURRENT_SOURCE_DIR}/include/files
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    ${VERILATOR_OUTPUT_DIR}
    /usr/share/verilator/include
    /usr/share/verilator/include/vltstd
)

add_dependencies(top top_generated)

target_link_libraries(top PRIVATE ${VERILATOR_OUTPUT_DIR}/Vtop__ALL.a)
