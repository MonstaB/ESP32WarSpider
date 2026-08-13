#include <M5Cardputer.h>
#include "system.h"

namespace WarSpider {
namespace System {

void begin() {
    M5Cardputer.Display.clear();

    M5Cardputer.Display.setTextSize(2);
    M5Cardputer.Display.setCursor(10, 10);
    M5Cardputer.Display.println("WAR SPIDER");

    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(10, 35);
    M5Cardputer.Display.println("v0.0.2");

    M5Cardputer.Display.setCursor(10, 55);
    M5Cardputer.Display.println("SYSTEM START");

    M5Cardputer.Display.setCursor(10, 70);
    M5Cardputer.Display.println("----------------");

    M5Cardputer.Display.setCursor(10, 85);
    M5Cardputer.Display.println("DISPLAY       OK");

    M5Cardputer.Display.setCursor(10, 100);
    M5Cardputer.Display.println("SYSTEM        OK");
}

void showReady() {
    M5Cardputer.Display.setCursor(10, 115);
    M5Cardputer.Display.println("READY");
}

}
}