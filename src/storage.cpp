#include "storage.h"
#include "version.h"

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
    sessionFilePath = "";

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

bool Storage::createSessionFile(
    const String& sessionId,
    const String& deviceId
) {
    if (!sdAvailable || sessionId.length() == 0) {
        return false;
    }

    if (sessionFile) {
        sessionFile.close();
    }

    sessionFilePath =
        String(SESSIONS_PATH) +
        "/" +
        sessionId +
        ".csv";

    sessionFile = SD.open(
        sessionFilePath,
        FILE_WRITE
    );

    if (!sessionFile) {
        sessionFilePath = "";
        return false;
    }

    sessionFile.println(
        String("WigleWifi-1.6,") +
        "appRelease=" + WAR_SPIDER_VERSION_STRING +
        ",model=M5Cardputer" +
        ",release=ESP32-S3" +
        ",device=WARSPIDER" +
        ",display=240x135" +
        ",board=m5stack" +
        ",brand=M5Stack" +
        ",star=Sol" +
        ",body=3" +
        ",subBody=0"
    );

    sessionFile.println(
        "MAC,SSID,AuthMode,FirstSeen,Channel,Frequency,RSSI,"
        "CurrentLatitude,CurrentLongitude,AltitudeMeters,"
        "AccuracyMeters,RCOIs,MfgrId,Type"
    );

    sessionFile.flush();

    return true;
}

bool Storage::closeSessionFile() {
    if (!sessionFile) {
        return false;
    }

    sessionFile.flush();
    sessionFile.close();

    return true;
}

bool Storage::isSessionFileOpen() const {
    return static_cast<bool>(sessionFile);
}

const char* Storage::getRootPath() const {
    return ROOT_PATH;
}

const char* Storage::getSessionsPath() const {
    return SESSIONS_PATH;
}

const String& Storage::getSessionFilePath() const {
    return sessionFilePath;
}

}