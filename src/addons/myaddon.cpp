#include "addons/myaddon.h"
#include "storagemanager.h"
#include "config.pb.h"
#include "helper.h"
#include <iostream>

bool MyAddon::available(){
    stdio_init_all();
    return MY_ADDON_ENABLED && isValidPin(REED_SWITCH_PIN);
    printf("available\n");
}

void MyAddon::setup(){
    pulseCounter = 0;
    gpio_init(REED_SWITCH_PIN);
    gpio_set_dir(REED_SWITCH_PIN, GPIO_IN);
    lastRead = gpio_get(REED_SWITCH_PIN);
    lastPulseTime = 0;
    Gamepad * gamepad = Storage::getInstance().GetGamepad();
    gamepad->hasAnalogTriggers = true;
    printf("setup\n");
}

void MyAddon::process(){
    Gamepad * gamepad = Storage::getInstance().GetGamepad();

    bool read = gpio_get(REED_SWITCH_PIN);
    uint32_t now = getMillis();

    if(read == 1 && read != lastRead){
        float rpm = 60000 / ((now - lastPulseTime) * 4);
        gamepad->state.rt = int(rpm * 255 / MAX_RPM);
        lastPulseTime = now;
    }
    lastRead = read;

    if(now - lastPulseTime >= 2000){
        gamepad->state.rt = 0;
    }

    printf("process\n");
}
