#include "gps.h"
#include "cap_lora.h"
#include <driver/gpio.h>

namespace WarSpider {

GPS& GPS::instance() {
    static GPS instance;
    return instance;
}

bool GPS::begin() {
    if (!CapLoRa::instance().isPresent()) {
        status = SubsystemStatus::FAILED;
        return false;
    }

    latitude = 0.0;
    longitude = 0.0;
    altitude = 0.0;
    satellites = 0;
    bytesReceived = 0;
    fix = false;
    rawData = "";

    // GPIO13 is the ESP32-S3 FSPIQ/IOMUX pin.
    // Porkchop clears the IOMUX before using it as UART TX.
    gpio_reset_pin(GPIO_NUM_13);

    // Proven Cap LoRa-1262 configuration.
    // GPS TX -> Cardputer GPIO15 (ESP32 RX)
    // GPS RX <- Cardputer GPIO13 (ESP32 TX)
    Serial2.end();
    delay(10);

    Serial2.begin(
        115200,
        SERIAL_8N1,
        15,
        13
    );

    status = SubsystemStatus::READY;

    return true;
}

void GPS::update() {
    while (Serial2.available()) {
        char c = Serial2.read();

        bytesReceived++;

        if (rawData.length() < 80) {
            rawData += c;
        }

        parser.encode(c);
    }

    if (parser.location.isValid()) {
        latitude = parser.location.lat();
        longitude = parser.location.lng();
        fix = parser.location.isValid();
    }

    if (parser.altitude.isValid()) {
        altitude = parser.altitude.meters();
    }

    if (parser.satellites.isValid()) {
        satellites =
            static_cast<uint8_t>(parser.satellites.value());
    }
}

bool GPS::hasFix() const {
    return fix;
}

bool GPS::hasData() const {
    return bytesReceived > 0;
}

double GPS::getLatitude() const {
    return latitude;
}

double GPS::getLongitude() const {
    return longitude;
}

double GPS::getAltitude() const {
    return altitude;
}

uint8_t GPS::getSatellites() const {
    return satellites;
}

uint32_t GPS::getBytesReceived() const {
    return bytesReceived;
}

const String& GPS::getRawData() const {
    return rawData;
}

}