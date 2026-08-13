#include <M5Cardputer.h>
#include "system.h"

void setup() {
    M5Cardputer.begin();

    WarSpider::System::begin();
    WarSpider::System::showReady();
}

void loop() {
}