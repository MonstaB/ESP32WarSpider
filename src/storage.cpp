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

uint16_t Storage::getNextSessionNumber(
    const String& deviceId,
    int year,
    int month,
    int day
) const {
    if (!sdAvailable) {
        return 1;
    }

    char prefix[64];

    snprintf(
        prefix,
        sizeof(prefix),
        "%s_%04d%02d%02d_",
        deviceId.c_str(),
        year,
        month,
        day
    );

    uint16_t highest = 0;

    File directory = SD.open(SESSIONS_PATH);

    if (!directory || !directory.isDirectory()) {
        return 1;
    }

    File file = directory.openNextFile();

    while (file) {
        if (!file.isDirectory()) {
            String name = file.name();

            if (name.startsWith(prefix) &&
                name.endsWith(".csv")) {

                int start =
                    String(prefix).length();

                int end =
                    name.length() - 4;

                String numberText =
                    name.substring(start, end);

                int number =
                    numberText.toInt();

                if (number > highest &&
                    number <= 65535) {
                    highest =
                        static_cast<uint16_t>(number);
                }
            }
        }

        file.close();
        file = directory.openNextFile();
    }

    directory.close();

    if (highest >= 65535) {
        return 65535;
    }

    return highest + 1;
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

bool Storage::writeObservation(
    const Observation& observation
) {
    if (!sessionFile) {
        return false;
    }

    if (!observation.isValid()) {
        return false;
    }

    sessionFile.print(observation.mac);
    sessionFile.print(",");
    sessionFile.print(observation.ssid);
    sessionFile.print(",");
    sessionFile.print(observation.authMode);
    sessionFile.print(",");
    sessionFile.print(observation.firstSeen);
    sessionFile.print(",");
    sessionFile.print(observation.channel);
    sessionFile.print(",");
    sessionFile.print(observation.frequency);
    sessionFile.print(",");
    sessionFile.print(observation.rssi);
    sessionFile.print(",");
    sessionFile.print(observation.currentLatitude, 6);
    sessionFile.print(",");
    sessionFile.print(observation.currentLongitude, 6);
    sessionFile.print(",");
    sessionFile.print(observation.altitudeMeters, 1);
    sessionFile.print(",");
    sessionFile.print(observation.accuracyMeters, 1);
    sessionFile.print(",");
    sessionFile.print(observation.rcois);
    sessionFile.print(",");
    sessionFile.print(observation.mfgrId);
    sessionFile.print(",");
    sessionFile.println(observation.type);

    sessionFile.flush();

    return true;
}

bool Storage::readSessionFile() {
    if (!sdAvailable || sessionFilePath.length() == 0) {
        return false;
    }

    if (sessionFile) {
        return false;
    }

    File file = SD.open(sessionFilePath, FILE_READ);

    if (!file) {
        return false;
    }

    Serial.println();
    Serial.println("----- SESSION CSV -----");

    while (file.available()) {
        Serial.write(file.read());
    }

    Serial.println();
    Serial.println("----- END CSV -----");

    file.close();

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