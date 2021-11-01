#ifdef BUDDY

#include <memory_manager.h>
#include <console.h>

#define MAX_LEVELS 26 // 2^16 = 64KB
#define MAX_SIZE (1<<MAX_LEVELS) // 64KB
#define BLOCKS_PER_LEVEL(level) (1<<(level))
#define SIZE_OF_BLOCKS_AT_LEVEL(level,total_size) ((total_size) / (1<<(level)))
#define INDEX_OF_POINTER_IN_LEVEL(pointer,level,memory_start,total_size) (((pointer)-(memory_start)) / (SIZE_OF_BLOCKS_AT_LEVEL(level,total_size)))

typedef struct LIST_ENTRY {
   struct LIST_ENTRY* next;
   struct LIST_ENTRY* prev;
} LIST_ENTRY;

void * memory_start = (void *) 0x900000;
LIST_ENTRY* free_lists[MAX_LEVELS];
static long used_memory = 0;

static void InsertTailList(LIST_ENTRY** list, LIST_ENTRY* entry) {
   LIST_ENTRY* last = *list;
   if (last == NULL) {
      *list = entry;
      entry->next = NULL;
      entry->prev = NULL;
      return;
   }
   
   while(last->next != NULL) {
      last = last->next;
   }

   entry->prev = last;
   entry->next = NULL;
   last->next = entry;
}

static inline int IsListEmpty(LIST_ENTRY** list) {
   return *list == NULL;
}

static LIST_ENTRY* RemoveHeadList(LIST_ENTRY** list) {
   LIST_ENTRY* first = *list;
   if (first == NULL) {
      return NULL;
   }

   LIST_ENTRY* next = first->next;
   if (next != NULL) {
      next->prev = NULL;
   }

   *list = next;
   return first;
}

static void RemoveListEntry(LIST_ENTRY** listStart, LIST_ENTRY* entry) {
   if(entry == NULL) return;

   if(entry->prev != NULL)
      entry->prev->next = entry->next;

   if(entry->next != NULL)
      entry->next->prev = entry->prev;

   if(entry == *listStart)
      *listStart = entry->next;
}

static LIST_ENTRY* FindInList(LIST_ENTRY* list, void* mem) {
   LIST_ENTRY* entry = list;
   while(entry != NULL) {
      if(entry == mem)
         return entry;
      entry = entry->next;
   }
   return NULL;
}

static inline size_t GetLevel(size_t size) {
   size_t level = 0;
   while(SIZE_OF_BLOCKS_AT_LEVEL(level,MAX_SIZE) > size)
      level++;
   return level-1;
}

void setupBuddy() {
   LIST_ENTRY * link;
   size_t i;

   for(i = 0; i < MAX_LEVELS; i++)
      free_lists[i] = NULL;

   link = (LIST_ENTRY*)memory_start;
   link->next = NULL;
   link->prev = NULL;
   InsertTailList(&free_lists[0], link);
}

static void * _alloc(uint8_t level) {
   uint8_t * memory;
   LIST_ENTRY * left;
   LIST_ENTRY * right;
   LIST_ENTRY * link;

   if(level < 0 || level >= MAX_LEVELS)
      return NULL;

   if (IsListEmpty(&free_lists[level])) {
      size_t size;

      memory = _alloc(level-1);
      if (!memory)
         return NULL; /* out of memory. */
      size = SIZE_OF_BLOCKS_AT_LEVEL(level, MAX_SIZE);
      /* now we split this block into two. */
      left = (LIST_ENTRY*) memory;
      right = (LIST_ENTRY*) (memory+size);
      /* initialize them. */
      left->next = NULL;
      left->prev = NULL;
      right->next = NULL;
      right->prev = NULL;
      /* insert the two new blocks. */
      InsertTailList(&free_lists[level], left);
      InsertTailList(&free_lists[level], right);
   }

   link = RemoveHeadList(&free_lists[level]);
   return (void*)link;
}

void* alloc(unsigned long size) {
   size_t blockSize = size+sizeof(uint8_t)+sizeof(LIST_ENTRY);
   uint8_t level = GetLevel(blockSize);
   uint8_t* mem = (uint8_t*)_alloc(level);

   if(mem == NULL)
      return NULL;

   used_memory += blockSize;

   //Guardo el level al principio del bloque.
   *mem = level;

   return (void*)(mem+1);
}

static void _free(void* memory, uint8_t level) {
   LIST_ENTRY* link;
   LIST_ENTRY* buddy_link;
   size_t index;
   void * buddy;
   size_t size = SIZE_OF_BLOCKS_AT_LEVEL(level, MAX_SIZE);

   index = INDEX_OF_POINTER_IN_LEVEL((uint64_t)memory, level, (uint64_t)memory_start, MAX_SIZE);

   if ((index & 1) == 0) 
      buddy = (uint8_t*) memory + size;
   else
      buddy = (uint8_t*) memory - size;

   buddy_link = NULL;
   if (!IsListEmpty(&free_lists[level]))
      buddy_link = FindInList(free_lists[level], buddy);

   link = (LIST_ENTRY*) memory;
   link->next = NULL;
   link->prev = NULL;
   InsertTailList(&free_lists[level], link);

   if ( buddy_link == buddy) {
      RemoveListEntry(&free_lists[level], link);
      RemoveListEntry(&free_lists[level], buddy_link);
      if ((index & 1) == 0)
         _free(link, level - 1);
      else
         _free(buddy_link, level - 1);
   }
}

void free(void* memory) {
   void* block = (uint8_t*)memory - 1;
   uint8_t level = *(uint8_t*)block;
   _free(block, level);
   used_memory -= SIZE_OF_BLOCKS_AT_LEVEL(level, MAX_SIZE);
}

void print_mem_state() {
   print("Total Mem: 0x");
   printhex(MAX_SIZE);
   print(" Bytes\n");

   print("Used Mem: 0x");
   printhex(used_memory);
   print(" Bytes\n");

   print("Free Mem: 0x");
   printhex(MAX_SIZE - used_memory);
   print(" Bytes\n");
}

#endif
