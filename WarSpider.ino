#include <M5Cardputer.h>
#include "system.h"
#include "identity.h"
#include "config.h"

void setup() {
    M5Cardputer.begin();
    
    WarSpider::Identity::begin();
    WarSpider::Config::begin();
    WarSpider::System::begin();
    WarSpider::System::showReady();
}

void loop() {
}