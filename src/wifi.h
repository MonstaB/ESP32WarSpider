#ifndef WARSPIDER_WIFI_H
#define WARSPIDER_WIFI_H

#include <Arduino.h>
#include "subsystem.h"

namespace WarSpider {

class WiFi : public Subsystem {
public:
    static WiFi& instance();

    bool begin() override;
    void update();

private:
    WiFi() = default;
};

}

#endif