#include <M5Cardputer.h>
#include "session.h"
#include "version.h"
#include "identity.h"
#include "config_storage.h"
#include "config.h"
#include "cap_lora.h"
#include "gps.h"
#include "system.h"
#include "subsystem.h"
#include "observation.h"
#include "storage.h"
#include "wifi.h"

namespace {

bool sessionStarted = false;

String getGpsTimestamp()
{
    auto& gps = WarSpider::GPS::instance();

    char timestamp[32];

    snprintf(
        timestamp,
        sizeof(timestamp),
        "%04d-%02d-%02d %02d:%02d:%02d",
        gps.getYear(),
        gps.getMonth(),
        gps.getDay(),
        gps.getHour(),
        gps.getMinute(),
        gps.getSecond()
    );

    return String(timestamp);
}

void drawPage1()
{
    auto& identity = WarSpider::Identity::instance();
    auto& config = WarSpider::Config::instance();
    auto& cap = WarSpider::CapLoRa::instance();
    auto& gps = WarSpider::GPS::instance();
    auto& session = WarSpider::Session::instance();
    auto& storage = WarSpider::Storage::instance();

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

    M5Cardputer.Display.print("SD:  ");
    M5Cardputer.Display.println(
        storage.getStatus() == WarSpider::SubsystemStatus::READY
            ? "OK"
            : "ERR"
    );

    M5Cardputer.Display.print("FIX: ");
    M5Cardputer.Display.print(gps.hasFix() ? "YES" : "NO");

    M5Cardputer.Display.print(" SAT: ");
    M5Cardputer.Display.println(gps.getSatellites());

    M5Cardputer.Display.print("RX: ");
    M5Cardputer.Display.println(gps.getBytesReceived());

    M5Cardputer.Display.print("SES: ");

    if (sessionStarted) {
        M5Cardputer.Display.println(session.getSessionId());
    } else {
        M5Cardputer.Display.println("WAITING");
    }

    if (sessionStarted) {
        M5Cardputer.Display.println("S=STOP");
    } else {
        M5Cardputer.Display.println("S=START");
    }

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
    M5Cardputer.Display.println("SD: /WarSpider/Wardriving");

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

    if (capOk) {
        WarSpider::GPS::instance().begin();
    }

    WarSpider::System::begin();
    WarSpider::Storage::instance().begin();
    WarSpider::Storage::instance().begin();
    WarSpider::WiFi::instance().begin();

    drawPage1();
}

void loop()
{
    static uint32_t lastUpdate = 0;
    static uint32_t lastPageChange = 0;
    static uint8_t page = 0;

    auto& gps = WarSpider::GPS::instance();

    gps.update();
    WarSpider::WiFi::instance().update();

    M5Cardputer.update();

    if (M5Cardputer.Keyboard.isChange() &&
        M5Cardputer.Keyboard.isPressed()) {

        Keyboard_Class::KeysState keys =
            M5Cardputer.Keyboard.keysState();

        for (auto key : keys.word) {

            if (key == 's' || key == 'S') {

                if (!sessionStarted) {

                    if (!gps.hasDateTime()) {
                        Serial.println(
                            "Cannot start session: GPS time unavailable"
                        );
                        continue;
                    }

                    if (!WarSpider::Session::instance().start()) {
                        Serial.println(
                            "Session start failed"
                        );
                        continue;
                    }

                    if (!WarSpider::Storage::instance().createSessionFile(
                            WarSpider::Session::instance().getSessionId(),
                            WarSpider::Identity::instance().getDeviceId()
                        )) {

                        WarSpider::Session::instance().close();

                        Serial.println(
                            "Session CSV creation failed"
                        );
                        continue;
                    }

                    sessionStarted = true;

                    Serial.println(
                        "SESSION STARTED"
                    );
                }
            }
            
            if (key == 'o' || key == 'O') {

                if (!sessionStarted) {
                    Serial.println(
                        "Cannot write observation: no active session"
                    );
                    continue;
                }

                auto& gps = WarSpider::GPS::instance();

                WarSpider::Observation observation;

                observation.mac =
                    "AA:BB:CC:DD:EE:FF";

                observation.ssid =
                    "WARSPIDER-TEST";

                observation.authMode =
                    "[WPA2-PSK-CCMP][ESS]";

                observation.firstSeen =
                    getGpsTimestamp();

                observation.channel = 6;
                observation.frequency = 2437;
                observation.rssi = -54;

                observation.currentLatitude =
                    gps.getLatitude();

                observation.currentLongitude =
                    gps.getLongitude();

                observation.altitudeMeters =
                    gps.getAltitude();

                observation.accuracyMeters = 0.0;

                observation.rcois = "";
                observation.mfgrId = "";
                observation.type = "WIFI";

                if (WarSpider::Storage::instance().writeObservation(
                        observation
                    )) {

                    Serial.println(
                        "OBSERVATION WRITTEN"
                    );
                } else {

                    Serial.println(
                        "OBSERVATION WRITE FAILED"
                    );
                }
            }

            if (key == 'x' || key == 'X') {

                if (sessionStarted) {

                    bool fileClosed =
                        WarSpider::Storage::instance().closeSessionFile();

                    bool fileRead = false;

                    if (fileClosed) {
                        fileRead =
                            WarSpider::Storage::instance().readSessionFile();
                    }

                    bool sessionClosed =
                        WarSpider::Session::instance().close();

                    if (fileClosed && fileRead && sessionClosed) {
                        sessionStarted = false;
                        Serial.println("SESSION CLOSED");
                    } else {
                        Serial.println("SESSION CLOSE ERROR");
                    }
                }
            }
        }
    }

    



    const uint32_t now = millis();

    if (now - lastUpdate >= 500) {
        lastUpdate = now;

        if (page == 0) {
            drawPage1();
        } else {
            drawPage2();
        }
    }

    if (now - lastPageChange >= 15000) {
        lastPageChange = now;
        page = (page == 0) ? 1 : 0;
    }

    delay(5);
}