
#ifndef __DATALOG_H__
#define __DATALOG_H__

#include <FS.h>
#include <SPIFFS.h>
#include "config.h"
#include "Peripherals.h"
#include "Status.h"
#include "Utilities.h"

class DataLog
{
private:
    const char *getLogFileName();
    File retrievalfile;

protected:
public:
    void loop();
    void dump();
    bool startRetrieval();
    float getValue(uint32_t minutesBackSinceNow, uint8_t valueIndex);
    void stopRetrieval();
};

#endif