#ifndef WARSPIDER_STORAGE_H
#define WARSPIDER_STORAGE_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "subsystem.h"
#include "observation.h"

namespace WarSpider {

class Storage : public Subsystem {
public:
    static Storage& instance();

    bool begin() override;

    bool isAvailable() const;
    bool ensureDirectories();
    bool writeObservation(const Observation& observation);

    uint16_t getNextSessionNumber(
        const String& deviceId,
        int year,
        int month,
        int day
    ) const;

    bool createSessionFile(
        const String& sessionId,
        const String& deviceId
    );
    

    bool closeSessionFile();

    bool isSessionFileOpen() const;

    const char* getRootPath() const;
    const char* getSessionsPath() const;
    const String& getSessionFilePath() const;

private:
    Storage() = default;

    bool sdAvailable = false;
    File sessionFile;
    String sessionFilePath;
};

}

#endif