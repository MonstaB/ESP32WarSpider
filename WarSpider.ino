#include <M5Cardputer.h>

void setup() {
    M5Cardputer.begin();

    M5Cardputer.Display.setTextSize(2);
    M5Cardputer.Display.setCursor(10, 20);
    M5Cardputer.Display.println("WAR SPIDER");

    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setCursor(10, 50);
    M5Cardputer.Display.println("v0.0.1");

    M5Cardputer.Display.setCursor(10, 80);
    M5Cardputer.Display.println("HELLO WORLD");
}

void loop() {
}