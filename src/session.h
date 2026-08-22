#ifndef WARSPIDER_SESSION_H
#define WARSPIDER_SESSION_H

#include <Arduino.h>
#include "subsystem.h"

namespace WarSpider {

class Session : public Subsystem {
public:
    static Session& instance();

    bool begin() override;

    bool start();
    bool isActive() const;

    const String& getSessionId() const;
    uint32_t getStartMillis() const;

private:
    Session() = default;

    String sessionId;
    uint32_t startMillis = 0;
    uint16_t sessionNumber = 0;
    bool active = false;
};

}

#endif