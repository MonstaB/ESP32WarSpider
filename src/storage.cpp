#include "storage.h"

namespace WarSpider {

namespace {

constexpr int SD_SCK_PIN = 40;
constexpr int SD_MISO_PIN = 39;
constexpr int SD_MOSI_PIN = 14;
constexpr int SD_CS_PIN = 12;

SPIClass sdSPI(FSPI);

constexpr const char* ROOT_PATH = "/WarSpider";
constexpr const char* SESSIONS_PATH = "/WarSpider/Wardriving";

}

Storage& Storage::instance() {
    static Storage instance;
    return instance;
}

bool Storage::begin() {
    status = SubsystemStatus::NOT_STARTED;
    sdAvailable = false;

    pinMode(SD_CS_PIN, OUTPUT);
    digitalWrite(SD_CS_PIN, HIGH);

    sdSPI.begin(
        SD_SCK_PIN,
        SD_MISO_PIN,
        SD_MOSI_PIN,
        SD_CS_PIN
    );

    delay(20);

    if (!SD.begin(SD_CS_PIN, sdSPI, 25000000)) {
        status = SubsystemStatus::FAILED;
        return false;
    }

    sdAvailable = true;

    if (!ensureDirectories()) {
        status = SubsystemStatus::FAILED;
        return false;
    }

    status = SubsystemStatus::READY;
    return true;
}

bool Storage::isAvailable() const {
    return sdAvailable;
}

bool Storage::ensureDirectories() {
    if (!sdAvailable) {
        return false;
    }

    if (!SD.exists(ROOT_PATH)) {
        if (!SD.mkdir(ROOT_PATH)) {
            return false;
        }
    }

    if (!SD.exists(SESSIONS_PATH)) {
        if (!SD.mkdir(SESSIONS_PATH)) {
            return false;
        }
    }

    return true;
}

const char* Storage::getRootPath() const {
    return ROOT_PATH;
}

const char* Storage::getSessionsPath() const {
    return SESSIONS_PATH;
}

}