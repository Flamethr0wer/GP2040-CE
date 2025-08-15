#ifndef _MYADDON_H
#define _MYADDON_H

#include "gpaddon.h"
#include "GamepadEnums.h"
#include "BoardConfig.h"
#include "enums.pb.h"

#ifndef MY_ADDON_ENABLED
#define MY_ADDON_ENABLED 0
#endif

#ifndef REED_SWITCH_PIN
#define REED_SWITCH_PIN -1
#endif

#ifndef MAX_RPM
#define MAX_RPM 180
#endif

#define AddonName "Bicycle add-on"

class MyAddon : public GPAddon
{
public:
    virtual bool available();
    virtual void setup();
    virtual void preprocess() {}
    virtual void process();
    virtual void postprocess(bool sent) {}
    virtual void reinit() {}
    virtual std::string name() { return AddonName; }

private:
    volatile uint32_t pulseCounter;
    bool lastRead;
    uint32_t lastPulseTime;
};

#endif