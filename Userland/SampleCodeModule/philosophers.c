#include <syscall.h>
#include <stdint.h>
#include <str.h>
#include <currentTime.h>

#define THINKING 0
#define HUNGRY 1
#define EATING 2

#define DEAULT_PHILO_COUNT 5
#define MAX_PHILO_COUNT 32
#define MUTEX_ID 128
#define SEMAPHORE_MIN_ID 129

#define LEFT(x) (((x)==philoCount)? 0 : (x)+1)
#define RIGHT(x) (((x)+1)%philoCount)

static uint8_t philoVector[MAX_PHILO_COUNT];
static int philoPID[MAX_PHILO_COUNT];
static int philoCount;

void philosophers(unsigned int argc, const char** argv) {
    int idx;
    if (argc > 1) {
        if (strToIntBase(argv[1], strlen(argv[1]), 10, &idx, 1) <= 0)
            return;
    }

    while (1) {
        //Thinking
        for (int i = 0; i < 10000; i++);
        tryToEat(idx);
        //Eating
        for (int i = 0; i < 10000; i++); 
        stopEating(idx);
    }
}

void tryToEat(int idx) {
    philoVector[idx] = HUNGRY;
    while (philoVector[idx] == HUNGRY) {
        _semwait(MUTEX_ID);
        if (philoVector[idx] == HUNGRY && philoVector[LEFT(idx)] != EATING && philoVector[RIGHT(idx)] != EATING) {
            philoVector[idx] == EATING;
            _sempost(SEMAPHORE_MIN_ID + idx);
        }
        _sempost(MUTEX_ID);
        _semwait(SEMAPHORE_MIN_ID + idx);
    }
}

void stopEating(int idx) {
    _semwait(MUTEX_ID);
    philoVector[SEMAPHORE_MIN_ID + idx] = THINKING;
    if (philoVector[SEMAPHORE_MIN_ID + LEFT(idx)] == HUNGRY)
        _sempost(LEFT(idx));
    if (philoVector[SEMAPHORE_MIN_ID + RIGHT(idx)] == HUNGRY)
        _sempost(RIGHT(idx));
    _sempost(MUTEX_ID);
}

void philosopherPrinter() {
    Time t = getCurrentTime();
    while(1) {
        if(t.seconds != (t = getCurrentTime()).seconds && t.seconds % 1 == 0) {
            for (int i = 0; i < philoCount; i++) {
                char * printState;
                switch (philoVector[i]) {
                    case EATING:
                        printState = "E";
                        break;
                    default:
                        printState = ".";
                        break;
                }

                printf("%s ", printState);
            }
            putchar('\n');
        }
    }
}

void philosopherManager() {
    _systerminalraw(1);

    philoCount = DEAULT_PHILO_COUNT;
    
    while (1) {

        int printerpid;
        int modified = 0;
        int end = 0;

        _semopen(MUTEX_ID, 1);

        char idstr[10];
        char * argv[] = {"philosopher", idstr, 0};

        for (int i = 0; i < philoCount; i++) {
            uintToBase(i, idstr, 10);
            _semopen(SEMAPHORE_MIN_ID + i, 0);
            philoPID[i] = _syscreateprocess(&philosophers, 2, argv);
        }
        char * printerArgs[] = {"phprinter",0};
        printerpid = _syscreateprocess(&philosopherPrinter, 1, printerArgs);

        char buf[1];
        while (_sysread(0,buf,1)) {
            switch (buf[0]) {
            case 'a':
                modified = 1;
                break;
            case 'r':
                modified = -1;
                break;
            case 't':
                end = 1;
                break;
            default:
                continue;
            }
            break;
        }
        
        for (int i = 0; i < philoCount; i++) {
            _semclose(SEMAPHORE_MIN_ID + i);
            _syskill(philoPID[i]);
        }
        _syskill(printerpid);
        _semclose(MUTEX_ID);

        if (end) break;

        philoCount += modified;
    }

    

    _systerminalraw(0);
}