#include "cap_lora.h"
#include <M5Unified.h>
#include "utility/PI4IOE5V6408_Class.hpp"

namespace WarSpider {

static m5::PI4IOE5V6408_Class ioe(
    0x43,
    400000,
    &m5::In_I2C
);

CapLoRa& CapLoRa::instance() {
    static CapLoRa instance;
    return instance;
}

bool CapLoRa::begin() {
    present = false;

    if (!m5::In_I2C.begin()) {
        status = SubsystemStatus::FAILED;
        return false;
    }

    if (!ioe.begin()) {
        status = SubsystemStatus::FAILED;
        return false;
    }

    present = true;
    status = SubsystemStatus::READY;

    return true;
}

bool CapLoRa::isPresent() const {
    return present;
}

}