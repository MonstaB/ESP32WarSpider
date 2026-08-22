#include <M5Cardputer.h>

#include "version.h"
#include "identity.h"
#include "config_storage.h"
#include "config.h"
#include "cap_lora.h"
#include "gps.h"
#include "system.h"
#include "subsystem.h"

namespace {

void drawPage1()
{
    auto& identity = WarSpider::Identity::instance();
    auto& config = WarSpider::Config::instance();
    auto& cap = WarSpider::CapLoRa::instance();
    auto& gps = WarSpider::GPS::instance();

    M5Cardputer.Display.fillScreen(BLACK);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(4, 4);

    M5Cardputer.Display.println("WAR SPIDER");
    M5Cardputer.Display.print("v");
    M5Cardputer.Display.println(WAR_SPIDER_VERSION_STRING);

    M5Cardputer.Display.println();

    M5Cardputer.Display.print("NAME: ");
    M5Cardputer.Display.println(config.getSpiderName());

    M5Cardputer.Display.print("TEAM: ");
    M5Cardputer.Display.println(config.getTeamId());

    M5Cardputer.Display.print("ID:   ");
    M5Cardputer.Display.println(identity.getDeviceId());

    M5Cardputer.Display.println();

    M5Cardputer.Display.print("CAP: ");
    M5Cardputer.Display.println(
        cap.getStatus() == WarSpider::SubsystemStatus::READY
            ? "OK"
            : "ERR"
    );

    M5Cardputer.Display.print("GPS: ");
    M5Cardputer.Display.println(
        gps.getStatus() == WarSpider::SubsystemStatus::READY
            ? "OK"
            : "ERR"
    );

    M5Cardputer.Display.print("FIX: ");
    M5Cardputer.Display.print(gps.hasFix() ? "YES" : "NO");

    M5Cardputer.Display.print(" SAT: ");
    M5Cardputer.Display.println(gps.getSatellites());

    M5Cardputer.Display.print("RX: ");
    M5Cardputer.Display.println(gps.getBytesReceived());

    M5Cardputer.Display.println();
    M5Cardputer.Display.println("PAGE 1 / 2");
}

void drawPage2()
{
    auto& gps = WarSpider::GPS::instance();

    M5Cardputer.Display.fillScreen(BLACK);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(4, 4);

    M5Cardputer.Display.println("GPS POSITION");

    M5Cardputer.Display.println();

    M5Cardputer.Display.print("FIX: ");
    M5Cardputer.Display.println(gps.hasFix() ? "YES" : "NO");

    M5Cardputer.Display.print("SAT: ");
    M5Cardputer.Display.println(gps.getSatellites());

    M5Cardputer.Display.println();

    M5Cardputer.Display.print("LAT: ");
    M5Cardputer.Display.println(gps.getLatitude(), 6);

    M5Cardputer.Display.print("LON: ");
    M5Cardputer.Display.println(gps.getLongitude(), 6);

    M5Cardputer.Display.print("ALT: ");
    M5Cardputer.Display.print(gps.getAltitude(), 1);
    M5Cardputer.Display.println("m");

    M5Cardputer.Display.println();

    M5Cardputer.Display.print("RX: ");
    M5Cardputer.Display.println(gps.getBytesReceived());

    M5Cardputer.Display.println();
    M5Cardputer.Display.println("PAGE 2 / 2");
}

}

void setup()
{
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);

    WarSpider::Identity::instance().begin();
    WarSpider::ConfigStorage::instance().begin();
    WarSpider::Config::instance().begin();

    const bool capOk =
        WarSpider::CapLoRa::instance().begin();

    bool gpsOk = false;

    if (capOk) {
        gpsOk =
            WarSpider::GPS::instance().begin();
    }

    WarSpider::System::begin();

    (void)gpsOk;

    drawPage1();
}

void loop()
{
    static uint32_t lastUpdate = 0;
    static uint32_t lastPageChange = 0;
    static uint8_t page = 0;

    WarSpider::GPS::instance().update();

    const uint32_t now = millis();

    if (now - lastUpdate >= 500) {
        lastUpdate = now;

        if (page == 0) {
            drawPage1();
        } else {
            drawPage2();
        }
    }

    if (now - lastPageChange >= 5000) {
        lastPageChange = now;
        page = (page == 0) ? 1 : 0;
    }

    delay(5);
}