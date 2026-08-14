#include "config.h"
#include "config_storage.h"

namespace WarSpider {

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

}