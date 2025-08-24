cmake_minimum_required(VERSION 3.16)
project(verisim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(VERILOG_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/verilog/verisim.v
)

set(CPP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/verisim.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/verisimFilesIO.cpp
    /usr/share/verilator/include/verilated.cpp
    /usr/share/verilator/include/verilated_vcd_c.cpp # only if trace enabled
)

set(VERILATOR_OUTPUT_DIR ${CMAKE_BINARY_DIR}/verilated)

# Run Verilator
add_custom_command(
    OUTPUT ${VERILATOR_OUTPUT_DIR}/Vverisim.mk ${VERILATOR_OUTPUT_DIR}/Vverisim.h
    COMMAND verilator --cc ${VERILOG_SOURCES}
            -Mdir ${VERILATOR_OUTPUT_DIR}
            -trace
    DEPENDS ${VERILOG_SOURCES}
    COMMENT "Running Verilator..."
)

# Build verilated model
add_custom_command(
    OUTPUT ${VERILATOR_OUTPUT_DIR}/Vverisim__ALL.a
    COMMAND make -C ${VERILATOR_OUTPUT_DIR} -f Vverisim.mk
    DEPENDS ${VERILATOR_OUTPUT_DIR}/Vverisim.mk ${VERILATOR_OUTPUT_DIR}/Vverisim.h
    COMMENT "Building Verilated model..."
)

add_custom_target(verisim_generated
    DEPENDS ${VERILATOR_OUTPUT_DIR}/Vverisim__ALL.a
)

add_executable(verisim ${CPP_SOURCES})

target_include_directories(verisim PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    ${VERILATOR_OUTPUT_DIR}
    /usr/share/verilator/include
    /usr/share/verilator/include/vltstd
)

add_dependencies(verisim verisim_generated)

target_link_libraries(verisim PRIVATE ${VERILATOR_OUTPUT_DIR}/Vverisim__ALL.a)
