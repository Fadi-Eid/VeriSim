#include "verisimModuleOutputs.hpp"
#include "verisimHelper.hpp"

namespace verisim_ns {

    VeriSimModuleOutputs::VeriSimModuleOutputs(Vverisim& mod) : module(&mod) {

    }

    VeriSimModuleOutputs::~VeriSimModuleOutputs() = default;


    /* Getter for Module Outputs */
    CData VeriSimModuleOutputs::getOutput_leds() {
        return module->leds;
    }
    CData VeriSimModuleOutputs::getOutput_sevenSegment0() {
        return module->sevenseg0;
    }
    CData VeriSimModuleOutputs::getOutput_sevenSegment1() {
        return module->sevenseg1;
    }
    CData VeriSimModuleOutputs::getOutput_pwmBlue() {
        return module->pwm_b;
    }
    CData VeriSimModuleOutputs::getOutput_pwmGreen() {
        return module->pwm_g;
    }
    CData VeriSimModuleOutputs::getOutput_pwmRed() {
        return module->pwm_r;
    }
    CData VeriSimModuleOutputs::getOutput_pwmGeneral() {
        return module->pwm_gen;
    }
    CData VeriSimModuleOutputs::getOutput_tx0() {
        return module->TX0;
    }
    CData VeriSimModuleOutputs::getOutput_tx1() {
        return module->TX1;
    }
    IData VeriSimModuleOutputs::getOutput_bus0() {
        return module->out_bus0;
    }
    IData VeriSimModuleOutputs::getOutput_bus1() {
        return module->out_bus1;
    }

    /* Special getters for the outputs */
    CData VeriSimModuleOutputs::getOutput_led_x(CData idx) {
        return verisim_ns::getBit(module->leds, idx);
    }
    CData VeriSimModuleOutputs::getOutput_bus0_x(CData idx) {
        return verisim_ns::getBit(module->out_bus0, idx);
    }
    CData VeriSimModuleOutputs::getOutput_bus1_x(CData idx) {
        return verisim_ns::getBit(module->out_bus1, idx);
    }
    CData VeriSimModuleOutputs::getOutput_sevenSegment0_x(CData idx) {
        return verisim_ns::getBit(module->sevenseg0, idx);
    }
    CData VeriSimModuleOutputs::getOutput_sevenSegment1_x(CData idx) {
        return verisim_ns::getBit(module->sevenseg1, idx);
    }


    //////////////////////////////
    int VeriSimModuleOutputs::getOutput_bus0_int() {
        return static_cast<int>(module->in_bus0);
    }
    char VeriSimModuleOutputs::getOutput_bus0_char() {
        return static_cast<char>(module->in_bus0 & 0xFF);
    }
    float VeriSimModuleOutputs::getOutput_bus0_float() {
        float f;
        std::memcpy(&f, &module->in_bus0, sizeof(f));
        return f;
    }
    int VeriSimModuleOutputs::getOutput_bus1_int() {
        return static_cast<int>(module->in_bus1);
    }
    char VeriSimModuleOutputs::getOutput_bus1_char() {
        return static_cast<char>(module->in_bus1 & 0xFF);
    }
    float VeriSimModuleOutputs::getOutput_bus1_float() {
        float f;
        std::memcpy(&f, &module->in_bus1, sizeof(f));
        return f;
    }

}