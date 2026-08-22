#ifndef WARSPIDER_CONFIG_STORAGE_H
#define WARSPIDER_CONFIG_STORAGE_H

#include <Arduino.h>
#include "subsystem.h"
#include <Preferences.h>

namespace WarSpider {

class ConfigStorage : public Subsystem {
public:
    static ConfigStorage& instance();

    bool begin() override;

    bool saveSpiderName(const String& name);
    bool saveTeamId(const String& teamId);
    bool saveGpsUpdateInterval(uint32_t interval);
    
    bool loadSpiderName(String& name);
    bool loadTeamId(String& teamId);
    bool loadGpsUpdateInterval(uint32_t& interval);

private:
    ConfigStorage() = default;

    Preferences preferences;;
};

}

#endif