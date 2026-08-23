#ifndef WARSPIDER_STORAGE_H
#define WARSPIDER_STORAGE_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "subsystem.h"

namespace WarSpider {

class Storage : public Subsystem {
public:
    static Storage& instance();

    bool begin() override;

    bool isAvailable() const;
    bool ensureDirectories();

    const char* getRootPath() const;
    const char* getSessionsPath() const;

private:
    Storage() = default;

    bool sdAvailable = false;
};

}

#endif