#include "verisimModuleInputs.hpp"
#include "verisimHelper.hpp"

namespace verisim_ns {

    VeriSimModuleInputs::VeriSimModuleInputs(Vverisim& mod) : module(&mod) {

    }

    VeriSimModuleInputs::~VeriSimModuleInputs() = default;

    /* Getters for Module Inputs */
    CData VeriSimModuleInputs::getInput_clk() {
        return module->clk;
    }
    CData VeriSimModuleInputs::getInput_rst() {
        return module->rst_n;
    }
    CData VeriSimModuleInputs::getInput_toggleButton() {
        return module->toggle_btn;
    }
    CData VeriSimModuleInputs::getInput_buttons() {
        return module->buttons;
    }
    CData VeriSimModuleInputs::getInput_dips() {
        return module->dips;
    }
    CData VeriSimModuleInputs::getInput_rx0() {
        return module->RX0;
    }
    CData VeriSimModuleInputs::getInput_rx1() {
        return module->RX1;
    }
    IData VeriSimModuleInputs::getInput_bus0() {
        return module->in_bus0;
    }
    IData VeriSimModuleInputs::getInput_bus1() {
        return module->in_bus1;
    }

    /* Special getters for the inputs */
    CData VeriSimModuleInputs::getInput_button_x(CData idx) {
        return verisim_ns::getBit(module->buttons, idx);
    }
    CData VeriSimModuleInputs::getInput_bus0_x(CData idx) {
        return verisim_ns::getBit(module->in_bus0, idx);
    }
    CData VeriSimModuleInputs::getInput_bus1_x(CData idx) {
        return verisim_ns::getBit(module->in_bus1, idx);
    }
    CData VeriSimModuleInputs::getInput_dip_x(CData idx) {
        return verisim_ns::getBit(module->dips, idx);
    }

    /* Modifier for Module Inputs */
    void VeriSimModuleInputs::setInput_clk() {
        module->clk = 1;
    }
    void VeriSimModuleInputs::setInput_rst() {
        module->rst_n = 1;
    }
    void VeriSimModuleInputs::setInput_toggleButton() {
        module->toggle_btn = 1;
    }
    void VeriSimModuleInputs::setInput_rx0() {
        module->RX0 = 1;
    }
    void VeriSimModuleInputs::setInput_rx1() {
        module->RX1 = 1;
    }
    void VeriSimModuleInputs::setInput_buttons() {
        verisim_ns::setData(module->buttons);
    }
    void VeriSimModuleInputs::setInput_dips() {
        verisim_ns::setData(module->dips);
    }
    void VeriSimModuleInputs::setInput_bus0() {
        verisim_ns::setData(module->in_bus0);
    }
    void VeriSimModuleInputs::setInput_bus1() {
        verisim_ns::setData(module->in_bus1);
    }
    void VeriSimModuleInputs::setInput_button_x(CData idx) {
        verisim_ns::setBit(module->buttons, idx);
    }
    void VeriSimModuleInputs::setInput_dip_x(CData idx) {
        verisim_ns::setBit(module->dips, idx);
    }
    void VeriSimModuleInputs::setInput_bus0_x(CData idx) {
        verisim_ns::setBit(module->in_bus0, idx);
    }
    void VeriSimModuleInputs::setInput_bus1_x(CData idx) {
        verisim_ns::setBit(module->in_bus1, idx);
    }
    ////////////////////////
    void VeriSimModuleInputs::resetInput_clk() {
        module->clk = 0;
    }
    void VeriSimModuleInputs::resetInput_rst() {
        module->rst_n = 0;
    }
    void VeriSimModuleInputs::resetInput_toggleButton() {
        module->toggle_btn = 0;
    }
    void VeriSimModuleInputs::resetInput_rx0() {
        module->RX0 = 0;
    }
    void VeriSimModuleInputs::resetInput_rx1() {
        module->RX1 = 0;
    }
    void VeriSimModuleInputs::resetInput_buttons() {
        verisim_ns::resetData(module->buttons);
    }
    void VeriSimModuleInputs::resetInput_dips() {
        verisim_ns::resetData(module->dips);
    }
    void VeriSimModuleInputs::resetInput_bus0() {
        verisim_ns::resetData(module->in_bus0);
    }
    void VeriSimModuleInputs::resetInput_bus1() {
        verisim_ns::resetData(module->in_bus1);
    }
    void VeriSimModuleInputs::resetInput_button_x(CData idx) {
        verisim_ns::resetBit(module->buttons, idx);
    }
    void VeriSimModuleInputs::resetInput_dip_x(CData idx) {
        verisim_ns::resetBit(module->dips, idx);
    }
    void VeriSimModuleInputs::resetInput_bus0_x(CData idx) {
        verisim_ns::resetBit(module->in_bus0, idx);
    }
    void VeriSimModuleInputs::resetInput_bus1_x(CData idx) {
        verisim_ns::resetBit(module->in_bus1, idx);
    }
    ////////////////////////
    void VeriSimModuleInputs::flipInput_clk() {
        module->clk = !module->clk;
    }
    void VeriSimModuleInputs::flipInput_rst() {
        module->rst_n = module->rst_n;
    }
    void VeriSimModuleInputs::flipInput_toggleButton() {
        module->toggle_btn = !module->toggle_btn;
    }
    void VeriSimModuleInputs::flipInput_rx0() {
        module->RX0 = !module->RX0;
    }
    void VeriSimModuleInputs::flipInput_rx1() {
        module->RX1 = !module->RX1;
    }
    void VeriSimModuleInputs::flipInput_buttons() {
        verisim_ns::flipData(module->buttons);
    }
    void VeriSimModuleInputs::flipInput_dips() {
        verisim_ns::flipData(module->dips);
    }
    void VeriSimModuleInputs::flipInput_bus0() {
        verisim_ns::flipData(module->in_bus0);
    }
    void VeriSimModuleInputs::flipInput_bus1() {
        verisim_ns::flipData(module->in_bus1);
    }
    void VeriSimModuleInputs::flipInput_button_x(CData idx) {
        verisim_ns::flipBit(module->buttons, idx);
    }
    void VeriSimModuleInputs::flipInput_dip_x(CData idx) {
        verisim_ns::flipBit(module->dips, idx);
    }
    void VeriSimModuleInputs::flipInput_bus0_x(CData idx) {
        verisim_ns::flipBit(module->in_bus0, idx);
    }
    void VeriSimModuleInputs::flipInput_bus1_x(CData idx) {
        verisim_ns::flipBit(module->in_bus1, idx);
    }
}