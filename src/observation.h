#ifndef WARSPIDER_OBSERVATION_H
#define WARSPIDER_OBSERVATION_H

#include <Arduino.h>

namespace WarSpider {

class Observation {
public:
    String mac;
    String ssid;
    String authMode;
    String firstSeen;

    int channel = 0;
    int frequency = 0;
    int rssi = 0;

    double currentLatitude = 0.0;
    double currentLongitude = 0.0;
    double altitudeMeters = 0.0;
    double accuracyMeters = 0.0;

    String rcois;
    String mfgrId;
    String type;

    bool isValid() const;
};

}

#endif