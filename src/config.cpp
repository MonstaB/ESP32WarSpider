#include "config.h"
#include "config_storage.h"

namespace WarSpider {

static uint32_t gpsUpdateInterval = 5;

Config& Config::instance() {
    static Config config;
    return config;
}

bool Config::begin() {
    bool success = true;

    if (!ConfigStorage::instance().loadSpiderName(spiderName)) {
        spiderName = "SPIDER";

        if (!ConfigStorage::instance().saveSpiderName(spiderName)) {
            success = false;
        }
    }

    if (!ConfigStorage::instance().loadTeamId(teamId)) {
        teamId = "UNASSIGNED";

        if (!ConfigStorage::instance().saveTeamId(teamId)) {
            success = false;
        }
    }

    if (!ConfigStorage::instance().loadGpsUpdateInterval(gpsUpdateInterval)) {
        gpsUpdateInterval = 5;

        if (!ConfigStorage::instance().saveGpsUpdateInterval(gpsUpdateInterval)) {
            success = false;
        }
    }

    status = success
        ? SubsystemStatus::READY
        : SubsystemStatus::FAILED;

    return success;
}

const String& Config::getSpiderName() const {
    return spiderName;
}

const String& Config::getTeamId() const {
    return teamId;
}

uint32_t Config::getGpsUpdateInterval() const {
    return gpsUpdateInterval;
}

bool Config::setSpiderName(const String& newName) {
    if (newName.length() == 0) {
        return false;
    }

    if (!ConfigStorage::instance().saveSpiderName(newName)) {
        return false;
    }

    spiderName = newName;
    return true;
}

bool Config::setTeamId(const String& newTeamId) {
    if (newTeamId.length() == 0) {
        return false;
    }

    if (!ConfigStorage::instance().saveTeamId(newTeamId)) {
        return false;
    }

    teamId = newTeamId;
    return true;
}

bool Config::setGpsUpdateInterval(uint32_t interval) {
    if (interval == 0) {
        return false;
    }

    if (!ConfigStorage::instance().saveGpsUpdateInterval(interval)) {
        return false;
    }

    gpsUpdateInterval = interval;
    return true;
}

}