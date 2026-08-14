#ifndef WARSPIDER_IDENTITY_H
#define WARSPIDER_IDENTITY_H

#include <Arduino.h>
#include "subsystem.h"

namespace WarSpider {

class Identity : public Subsystem {
public:
    static Identity& instance();

    bool begin() override;
    const String& getDeviceId() const;

private:
    Identity() = default;
    String deviceId;
};

}

#endif