#ifndef WARSPIDER_CAP_LORA_H
#define WARSPIDER_CAP_LORA_H

#include <Arduino.h>
#include "subsystem.h"

namespace WarSpider {

namespace CapLoraPins {
    static constexpr uint8_t GPS_RX = 13;
    static constexpr uint8_t GPS_TX = 15;
}

class CapLoRa : public Subsystem {
public:
    static CapLoRa& instance();

    bool begin() override;
    bool isPresent() const;

private:
    CapLoRa() = default;

    bool present = false;
};

}

#endif