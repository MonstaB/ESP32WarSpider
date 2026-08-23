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
    status = SubsystemStatus::NOT_STARTED;

    return true;
}

bool Session::start() {
    if (active) {
        return true;
    }

    GPS& gps = GPS::instance();

    // Do not create a session until GPS has supplied a valid date/time.
    if (!gps.hasDateTime()) {
        return false;
    }

    const String& deviceId =
        Identity::instance().getDeviceId();

    sessionNumber++;

    char id[64];

    snprintf(
        id,
        sizeof(id),
        "%s_%04d%02d%02d_%03u",
        deviceId.c_str(),
        gps.getYear(),
        gps.getMonth(),
        gps.getDay(),
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