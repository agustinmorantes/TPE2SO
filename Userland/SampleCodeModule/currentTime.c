#include <currentTime.h>
#include <syscall.h>
#include <io.h>

Time getCurrentTime() {
    Time t;
    _systime(&t);
    return t;
}

void printCurrentTime() {
    Time t = getCurrentTime();
    printf("%d/%d/%d %d:%d:%d", t.day,t.month,t.year,t.hours,t.minutes,t.seconds); 
}
