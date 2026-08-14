#include "identity.h"
#include <esp_system.h>

namespace WarSpider {
namespace Identity {

static String deviceId;

void begin() {
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
}

const String& getDeviceId() {
    return deviceId;
}

}
}