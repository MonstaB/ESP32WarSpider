#include "config.h"
#include "config_storage.h"

namespace WarSpider {
namespace Config {

static String spiderName;
static String teamId;

void begin() {
    if (!ConfigStorage::loadSpiderName(spiderName)) {
        spiderName = "SPIDER";
        ConfigStorage::saveSpiderName(spiderName);
    }

    if (!ConfigStorage::loadTeamId(teamId)) {
        teamId = "UNASSIGNED";
        ConfigStorage::saveTeamId(teamId);
    } 
}

const String& getSpiderName() {
    return spiderName;
}

const String& getTeamId() {
    return teamId;
}

bool setSpiderName(const String& newName) {
    if (newName.length() == 0) {
        return false; // Invalid name
    }

    if (!ConfigStorage::saveSpiderName(newName)) {
        return false; // Failed to save
    }
    spiderName = newName;
    return true;
}

bool setTeamId(const String& newTeamId) {
    if (newTeamId.length() == 0) {
        return false; // Invalid team ID
    }

    if (!ConfigStorage::saveTeamId(newTeamId)) {
        return false; // Failed to save
    }
    teamId = newTeamId;
    return true;
}

}
}