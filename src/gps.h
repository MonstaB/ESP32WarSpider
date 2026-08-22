#ifndef WARSPIDER_GPS_H
#define WARSPIDER_GPS_H

#include <Arduino.h>
#include <TinyGPSPlus.h>
#include "subsystem.h"

namespace WarSpider {

class GPS : public Subsystem {
public:
    static GPS& instance();

    bool begin() override;
    void update();

    bool hasFix() const;
    bool hasData() const;

    bool hasDateTime() const;
    int getYear();
    int getMonth();
    int getDay();

    int getHour();
    int getMinute();
    int getSecond();


    double getLatitude() const;
    double getLongitude() const;
    double getAltitude() const;

    uint8_t getSatellites() const;
    uint32_t getBytesReceived() const;

    const String& getRawData() const;

private:
    GPS() = default;

    TinyGPSPlus parser;

    double latitude = 0.0;
    double longitude = 0.0;
    double altitude = 0.0;

    uint8_t satellites = 0;
    uint32_t bytesReceived = 0;
    bool fix = false;

    String rawData;
};

}

#endif