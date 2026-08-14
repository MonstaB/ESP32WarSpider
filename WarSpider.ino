#include <M5Cardputer.h>
#include "system.h"
#include "identity.h"
#include "config.h"
#include "config_storage.h"


void setup() {
    M5Cardputer.begin();
    
    WarSpider::Identity::instance().begin();
    WarSpider::ConfigStorage::instance().begin();
    WarSpider::Config::instance().begin();
    WarSpider::System::begin();
    WarSpider::System::showReady();

}

void loop() {
}