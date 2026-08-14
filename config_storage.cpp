#include "config_storage.h"
#include <Preferences.h>

namespace WarSpider {
namespace ConfigStorage {

static Preferences preferences;
    
bool begin() {
    // Implementation for initializing config storage
    return preferences.begin("war-spider", false);
    
}
    
bool saveSpiderName(const String& name) {
    return preferences.putString("spider_name", name) > 0;
}

bool saveTeamId(const String& teamId) {
    return preferences.putString("team_id", teamId) > 0;   
} 

bool loadSpiderName(String& name) {
    if (!preferences.isKey("spider_name")) {
        return false;
    }
    name = preferences.getString("spider_name", "");
    return true;
}

bool loadTeamId(String& teamId) {
    if (!preferences.isKey("team_id")) {
        return false;
    }
    teamId = preferences.getString("team_id", "");
    return true;
}
}   

}
