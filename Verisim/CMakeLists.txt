cmake_minimum_required(VERSION 3.16)
project(verisim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(VERILOG_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/verilog/verisim.v
)

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/verisim.cpp
)

set(VERILATOR_OUTPUT_DIR ${CMAKE_BINARY_DIR}/verilated)

# Run Verilator to generate C++ model (creates Vverisim.mk and Vverisim.h)
add_custom_command(
    OUTPUT ${VERILATOR_OUTPUT_DIR}/Vverisim.mk ${VERILATOR_OUTPUT_DIR}/Vverisim.h
    COMMAND verilator --cc ${VERILOG_SOURCES}
            -Mdir ${VERILATOR_OUTPUT_DIR}
            -trace
    DEPENDS ${VERILOG_SOURCES}
    COMMENT "Running Verilator..."
)

# Build Verilator-generated model
add_custom_command(
    OUTPUT ${VERILATOR_OUTPUT_DIR}/Vverisim__ALL.a
    COMMAND make -C ${VERILATOR_OUTPUT_DIR} -f Vverisim.mk
    DEPENDS ${VERILATOR_OUTPUT_DIR}/Vverisim.mk
    COMMENT "Building Verilated model..."
)

# Define a target for generated files
add_custom_target(verisim_generated
    DEPENDS ${VERILATOR_OUTPUT_DIR}/Vverisim__ALL.a
)

# Define a library target from Verilator’s archive
add_library(verisim_model STATIC IMPORTED GLOBAL)
set_target_properties(verisim_model PROPERTIES
    IMPORTED_LOCATION ${VERILATOR_OUTPUT_DIR}/Vverisim__ALL.a
)

# Your own executable
add_executable(verisim ${CPP_SOURCES})

target_include_directories(verisim PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    ${VERILATOR_OUTPUT_DIR}                      # for Vverisim.h
    /usr/share/verilator/include
    /usr/share/verilator/include/vltstd
)

# Make sure sources wait for generated headers
add_dependencies(verisim verisim_generated)
target_link_libraries(verisim PRIVATE verisim_model)

