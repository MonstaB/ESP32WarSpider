#include "config.h"

namespace WarSpider {
namespace Config {

static String spiderName;
static String teamId;

void begin() {
    spiderName = "SPIDER";
    teamId = "UNASSIGNED";
}

const String& getSpiderName() {
    return spiderName;
}

const String& getTeamId() {
    return teamId;
}

}
}