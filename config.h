#ifndef WARSPIDER_CONFIG_H
#define WARSPIDER_CONFIG_H

#include <Arduino.h>

namespace WarSpider {
namespace Config {

void begin();

const String& getSpiderName();
const String& getTeamId();

}
}

#endif