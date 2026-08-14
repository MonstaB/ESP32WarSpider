#ifndef WARSPIDER_CONFIG_STORAGE_H
#define WARSPIDER_CONFIG_STORAGE_H

#include <Arduino.h>

namespace WarSpider {
namespace ConfigStorage {

bool begin();

bool saveSpiderName(const String& name);
bool saveTeamId(const String& teamId);

bool loadSpiderName(String& name);
bool loadTeamId(String& teamId);


}
}   

#endif
