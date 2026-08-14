#include <M5Cardputer.h>
#include "system.h"
#include "version.h"
#include "identity.h"
#include "config.h"

namespace WarSpider {
namespace System {

void begin() {
    M5Cardputer.Display.clear();

    M5Cardputer.Display.setTextSize(2);
    M5Cardputer.Display.setCursor(10, 5);
    M5Cardputer.Display.println("WAR SPIDER");

    M5Cardputer.Display.setTextSize(1);

    M5Cardputer.Display.setCursor(10, 28);
    M5Cardputer.Display.print("v");
    M5Cardputer.Display.println(WAR_SPIDER_VERSION_STRING);

    M5Cardputer.Display.setCursor(10,43);
    M5Cardputer.Display.print("DEVICE ");
    M5Cardputer.Display.println(Identity::getDeviceId());

    M5Cardputer.Display.setCursor(10, 58);
    M5Cardputer.Display.print("NAME ");
    M5Cardputer.Display.println(Config::getSpiderName());

    M5Cardputer.Display.setCursor(10, 73);
    M5Cardputer.Display.print("TEAM ");
    M5Cardputer.Display.println(Config::getTeamId());

    M5Cardputer.Display.setCursor(10, 88);
    M5Cardputer.Display.println("----------------");

    M5Cardputer.Display.setCursor(10, 101);
    M5Cardputer.Display.println("DISPLAY       OK");

    M5Cardputer.Display.setCursor(10, 114);
    M5Cardputer.Display.println("SYSTEM        OK");
}

void showReady() {
    M5Cardputer.Display.setCursor(185, 114);
    M5Cardputer.Display.println("READY");
}

}
}