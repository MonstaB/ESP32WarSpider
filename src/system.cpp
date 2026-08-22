#include <M5Cardputer.h>
#include "system.h"
#include "version.h"
#include "identity.h"
#include "config.h"
#include "config_storage.h"
#include "cap_lora.h"

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

    M5Cardputer.Display.setCursor(10, 43);
    M5Cardputer.Display.print("DEVICE ");
    M5Cardputer.Display.println(Identity::instance().getDeviceId());

    M5Cardputer.Display.setCursor(10, 58);
    M5Cardputer.Display.print("NAME ");
    M5Cardputer.Display.println(Config::instance().getSpiderName());

    M5Cardputer.Display.setCursor(10, 73);
    M5Cardputer.Display.print("TEAM ");
    M5Cardputer.Display.println(Config::instance().getTeamId());

    M5Cardputer.Display.setCursor(10, 88);
    M5Cardputer.Display.print("--------------------------------");
    M5Cardputer.Display.setCursor(185, 88);

    bool ready =
        Identity::instance().getStatus() == SubsystemStatus::READY &&
        ConfigStorage::instance().getStatus() == SubsystemStatus::READY &&
        Config::instance().getStatus() == SubsystemStatus::READY &&
        CapLoRa::instance().getStatus() == SubsystemStatus::READY &&
        GPS::instance().getStatus() == SubsystemStatus::READY;

    M5Cardputer.Display.println(ready ? "READY" : "ERROR");

    M5Cardputer.Display.setCursor(10, 101);
    M5Cardputer.Display.print("DISPLAY       ");
    M5Cardputer.Display.println("OK");

    M5Cardputer.Display.setCursor(160, 101);
    M5Cardputer.Display.print("IDENTITY ");
    M5Cardputer.Display.println(
        Identity::instance().getStatus() == SubsystemStatus::READY
        ? "OK"
        : "ERROR"
    );

    M5Cardputer.Display.setCursor(10, 114);
    M5Cardputer.Display.print("STORAGE       ");
    M5Cardputer.Display.println(
        ConfigStorage::instance().getStatus() == SubsystemStatus::READY
        ? "OK"
        : "ERROR"
    );

    M5Cardputer.Display.setCursor(160, 114);
    M5Cardputer.Display.print("CONFIG ");
    M5Cardputer.Display.println(
        Config::instance().getStatus() == SubsystemStatus::READY
        ? "OK"
        : "ERROR"
    );
}

void showReady() {
}

void showStatus() {
    M5Cardputer.Display.fillRect(180, 0, 135, 80, BLACK);

    M5Cardputer.Display.setTextSize(1);

    M5Cardputer.Display.setCursor(180, 5);
    M5Cardputer.Display.println("GPS");

    M5Cardputer.Display.setCursor(180, 18);
    M5Cardputer.Display.println(
        GPS::instance().getStatus() == SubsystemStatus::READY
        ? "UART OK"
        : "UART ERR"
    );

    M5Cardputer.Display.setCursor(180, 31);
    M5Cardputer.Display.print("BYTES ");
    M5Cardputer.Display.println(
        GPS::instance().getBytesReceived()
    );

    M5Cardputer.Display.setCursor(180, 44);
    M5Cardputer.Display.print(
        GPS::instance().getRawData().substring(0, 15)
    );

    M5Cardputer.Display.setCursor(180, 57);
    M5Cardputer.Display.print(
        GPS::instance().getRawData().substring(15, 30)
    );

    M5Cardputer.Display.setCursor(180, 70);
    M5Cardputer.Display.println(
        CapLoRa::instance().getStatus() == SubsystemStatus::READY
        ? "CAP OK"
        : "CAP ERR"
    );
}

}
}

