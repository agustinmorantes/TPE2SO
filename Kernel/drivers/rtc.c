#include <stdint.h>
#include <rtc.h>
#include <console.h>
#include <numtostr.h>

typedef enum RtcRegister {
    Seconds = 0,
    Minutes = 0x02,
    Hours = 0x04,
    Weekday = 0x06,
    DayOfMonth = 0x07,
    Month = 0x08,
    Year = 0x09,
    RegA = 0x0a,
    RegB = 0x0b
} RtcRegister;

uint8_t readRtcRaw(uint8_t reg);

//Devuelve 1 si el rtc está en modo binario
static uint8_t getBinaryMode() {
    uint8_t regB = readRtcRaw(RegB);
    return 1 & (regB>>2);
}

//Devuelve 1 si está en modo 24hs
static uint8_t getHourMode() {
    uint8_t regB = readRtcRaw(RegB);
    return 1 & (regB>>1);
}

static uint8_t bcdToBinary(uint8_t bcd) {
    return ((bcd / 16) * 10) + (bcd & 0xf);
}

//Tomo el registro reg y lo convierto a binario
static uint8_t getConvertedRegister(RtcRegister reg) {
    uint8_t binaryMode = getBinaryMode();
    uint8_t regRaw = readRtcRaw(reg);

    if(binaryMode) return regRaw;
    
    return bcdToBinary(regRaw);
}

static uint8_t getCurrentSeconds() {
    return getConvertedRegister(Seconds);
}

static uint8_t getCurrentMinutes() {
    return getConvertedRegister(Minutes);
}

static uint8_t getCurrentDay() {
    return getConvertedRegister(DayOfMonth);
}

static uint8_t getCurrentMonth() {
    return getConvertedRegister(Month);
}

static uint8_t getCurrentYear() {
    return getConvertedRegister(Year);
}

static uint8_t getCurrentHours() {
    uint8_t hourMode = getHourMode();
    uint8_t binaryMode = getBinaryMode();

    uint8_t hours = readRtcRaw(Hours);
    
    if(!binaryMode)
        hours = bcdToBinary(hours);

    if(!hourMode && (hours & 0x80))
        hours = ((hours & 0x7F) + 12) % 24;

    if(hours < 3) {
        return hours + 21;
    }
    return hours - 3; //Convert from UTC to UTC-3 local time
}

Time getCurrentTime() {
    Time time = {getCurrentDay(), getCurrentMonth(), getCurrentYear(), getCurrentHours(), getCurrentMinutes(), getCurrentSeconds()};
    return time;
}

void printCurrentTime() {
    Time time = getCurrentTime();

    printnum(time.day);
    print("/");
    printnum(time.month);
    print("/");
    printnum(time.year);
    print(" ");
    printnum(time.hours);
    print(":");
    printnum(time.minutes);
    print(":");
    printnum(time.seconds);
}
