#include "identity.h"
#include <esp_system.h>

namespace WarSpider {

Identity& Identity::instance() {
    static Identity instance;
    return instance;
}

bool Identity::begin() {
    uint64_t mac = ESP.getEfuseMac();

    uint32_t shortId = (uint32_t)(mac & 0xFFFFFFFF);

    char buffer[16];

    snprintf(
        buffer,
        sizeof(buffer),
        "WS-%08lX",
        (unsigned long)shortId
    );

    deviceId = String(buffer);
    status = deviceId.length() > 0 
        ? SubsystemStatus::READY
        : SubsystemStatus::FAILED;

return status == SubsystemStatus::READY;
}

const String& Identity::getDeviceId() const {
    return deviceId;
}

}
