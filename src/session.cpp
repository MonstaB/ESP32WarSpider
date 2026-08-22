#include "session.h"
#include "identity.h"
#include "gps.h"

namespace WarSpider {

Session& Session::instance() {
    static Session instance;
    return instance;
}

bool Session::begin() {
    sessionId = "";
    startMillis = 0;
    sessionNumber = 0;
    active = false;
    status = SubsystemStatus::READY;

    return start();
}

bool Session::start() {
    if (active) {
        return true;
    }

    const String& deviceId =
        Identity::instance().getDeviceId();

    sessionNumber++;

    int year = 0;
    int month = 0;
    int day = 0;

    GPS& gps = GPS::instance();

    if (gps.hasDateTime()) {
        year = gps.getYear();
        month = gps.getMonth();
        day = gps.getDay();
    }

    if (year < 2000 || month < 1 || month > 12 || day < 1 || day > 31) {
        // GPS time is not available yet.
        // Keep session creation working; the final persistent
        // session/CSV timestamp will be finalized by storage later.
        year = 2000;
        month = 1;
        day = 1;
    }

    char id[64];

    snprintf(
        id,
        sizeof(id),
        "%s_%04d%02d%02d_%03u",
        deviceId.c_str(),
        year,
        month,
        day,
        static_cast<unsigned>(sessionNumber)
    );

    sessionId = id;
    startMillis = millis();
    active = true;
    status = SubsystemStatus::READY;

    return true;
}

bool Session::isActive() const {
    return active;
}

const String& Session::getSessionId() const {
    return sessionId;
}

uint32_t Session::getStartMillis() const {
    return startMillis;
}

}