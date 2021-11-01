#include <syscall.h>
#include <stdint.h>

#define THINKING 0
#define HUNGRY 1
#define EATING 2

#define DEAULT_PHILO_COUNT 5
#define MAX_PHILO_COUNT 32
#define MUTEX_ID 128

#define LEFT(x) (((x)==philoCount)? 0 : (x)+1)
#define RIGHT(x) (((x)+1)%philoCount)

#define SEMAPHORE_MIN_ID 129

static uint8_t philoVector[MAX_PHILO_COUNT];

static int philoCount = DEAULT_PHILO_COUNT;

void philosophers(int idx, semID left, semID right, semID global) {
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