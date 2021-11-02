#include <io.h>
#include <str.h>
#include <syscall.h>

#define N 1000000

static uint32_t my_create_process(void* func, int argc, char** argv){
  return _syscreateprocess(func, argc, argv);
}

static uint64_t my_sem_open(int sem_id, uint64_t initialValue){
  return _semopen(sem_id, initialValue);
}

static uint64_t my_sem_wait(int sem_id){
  return _semwait(sem_id);
}

static uint64_t my_sem_post(int sem_id){
  return _sempost(sem_id);
}

static uint64_t my_sem_close(int sem_id){
  return my_sem_close(sem_id);
}

#define TOTAL_PAIR_PROCESSES 2
#define SEM_ID 30

static int64_t global;  //shared memory

static void slowInc(int64_t *p, int64_t inc){
  int64_t aux = *p;
  aux += inc;
  _sysyield();
  *p = aux;
}

static void inc(int argc, char** argv){
  uint64_t sem; int64_t value;
  strToIntBase(argv[1], strlen(argv[1]), 10, (int*)&sem, 1);
  strToIntBase(argv[2], strlen(argv[2]), 10, (int*)&value, 0);

  printf("[inc] sem:%d, val:%d", sem, value);

  uint64_t i;

  if (sem && !my_sem_open(SEM_ID, 1)){
    printf("ERROR OPENING SEM\n");
    return;
  }
  
  for (i = 0; i < N; i++){
    if (sem) my_sem_wait(SEM_ID);
    slowInc(&global, value);
    if (sem) my_sem_post(SEM_ID);
  }

  if (sem) my_sem_close(SEM_ID);
  
  printf("Final value: %d\n", global);
}

void test_sync(){
  uint64_t i;

  global = 0;

  printf("CREATING PROCESSES...(WITH SEM)\n");

  for(i = 0; i < TOTAL_PAIR_PROCESSES; i++){
    char* argv1[] = {"inc", "1", "1"};
    char* argv2[] = {"inc", "1", "-1"};

    my_create_process(&inc, 3, argv1);
    my_create_process(&inc, 3, argv2);
  }
}

void test_no_sync(){
  uint64_t i;

  global = 0;

  printf("CREATING PROCESSES...(WITHOUT SEM)\n");

  for(i = 0; i < TOTAL_PAIR_PROCESSES; i++){
    char* argv1[] = {"inc", "0", "1"};
    char* argv2[] = {"inc", "0", "-1"};

    my_create_process(&inc, 3, argv1);
    my_create_process(&inc, 3, argv2);
  }
}
