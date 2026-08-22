#ifndef WARSPIDER_CONFIG_H
#define WARSPIDER_CONFIG_H

#include <Arduino.h>
#include "subsystem.h"

namespace WarSpider {

class Config : public Subsystem {
public:
    static Config& instance();

    bool begin() override;

    const String& getSpiderName() const;
    const String& getTeamId() const;
    uint32_t getGpsUpdateInterval() const;

    bool setSpiderName(const String& name);
    bool setTeamId(const String& teamId);
    bool setGpsUpdateInterval(uint32_t interval);

private:
    Config() = default;

    String spiderName;
    String teamId;
};

}

#endif