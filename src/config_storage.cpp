#include "config_storage.h"
#include <Preferences.h>

namespace WarSpider {

ConfigStorage& ConfigStorage::instance() {
    static ConfigStorage storage;
    return storage;
}

bool ConfigStorage::begin() {
    bool success = preferences.begin("war-spider", false);

    status = success
        ? SubsystemStatus::READY
        : SubsystemStatus::FAILED;

    return success;
}

bool ConfigStorage::saveSpiderName(const String& name) {
    return preferences.putString("spider_name", name) > 0;
}

bool ConfigStorage::saveTeamId(const String& teamId) {
    return preferences.putString("team_id", teamId) > 0;
}

bool ConfigStorage::loadSpiderName(String& name) {
    if (!preferences.isKey("spider_name")) {
        return false;
    }

    name = preferences.getString("spider_name", "");
    return true;
}

bool ConfigStorage::loadTeamId(String& teamId) {
    if (!preferences.isKey("team_id")) {
        return false;
    }

    teamId = preferences.getString("team_id", "");
    return true;
}

bool ConfigStorage::saveGpsUpdateInterval(uint32_t interval) {
    return preferences.putUInt("gps_interval", interval) > 0;
}

bool ConfigStorage::loadGpsUpdateInterval(uint32_t& interval) {
    if (!preferences.isKey("gps_interval")) {
        return false;
    }

    interval = preferences.getUInt("gps_interval", 5);
    return true;
}

}
