#ifndef WARSPIDER_IDENTITY_H
#define WARSPIDER_IDENTITY_H

#include <Arduino.h>

namespace WarSpider {
namespace Identity {

void begin();

const String& getDeviceId();

}
}

#endif