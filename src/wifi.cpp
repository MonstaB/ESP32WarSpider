#include "wifi.h"

namespace WarSpider {

WiFi& WiFi::instance() {
    static WiFi instance;
    return instance;
}

bool WiFi::begin() {
    status = SubsystemStatus::NOT_STARTED;

    status = SubsystemStatus::READY;
    return true;
}

void WiFi::update() {
}

}