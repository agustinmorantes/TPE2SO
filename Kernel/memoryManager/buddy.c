#include <memory_manager.h>

#define MAX_SIZE 0x4000000 // 64Mb
#define MAX_LEVELS 26 // 2^26 = 64Mb
#define BLOCKS_PER_LEVEL(level) (1<<(level))
#define SIZE_OF_BLOCKS_AT_LEVEL(level,total_size) ((total_size) / (1<<(level))
#define INDEX_OF_POINTER_IN_LEVEL(pointer,level,memory_start,total_size) (((pointer)-(memory_start)) / (SIZE_OF_BLOCKS_AT_LEVEL(level,total_size)))

typedef struct _LIST_ENTRY {
   struct LIST_ENTRY* next;
   struct LIST_ENTRY* prev;
}LIST_ENTRY;

void * memory_start = (void *) 0x900000;
void * free_lists[MAX_LEVELS];


void setup() {
   LIST_ENTRY * link;
   size_t i;

   for(i = 0; i < MAX_LEVELS; i++)
      InitializeListHead(&free_lists[i]);

   link = (LIST_ENTRY*)memory_start;
   InitializeListHead(link);
   InsertTailList(&free_lists[0], link);
}

void* alloc(unsigned long size) {
   size_t level = get_level(size);
   return _alloc(level);
}

void * _alloc(size_t level) {
   uint8_t * memory;
   LIST_ENTRY * left;
   LIST_ENTRY * right;
   LIST_ENTRY * link;

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
      InitializeListHead(left);
      InitializeListHead(right);
      /* insert the two new blocks. */
      InsertTailList(&free_lists[level], left);
      InsertTailList(&free_lists[level], right);
      
      }
   link = RemoveHeadList(&free_lists[level]);
   memory = (uint8_t*) link;
   return (void*) memory;
}

void free(void* memory, size_t size) {
   size_t level = get_level(size);
   return _free(memory, level);
}

void _free(void* memory, size_t level) {
   LIST_ENTRY* link;
   LIST_ENTRY* buddy_link;
   size_t index;
   void * buddy;
   size_t size = size_from_level(level);

   index = INDEX_OF_POINTER_IN_LEVEL(memory, level, memory_start, MAX_SIZE);

   if ((index & 1) == 0) 
      buddy = (void *) memory + size;
   else
      buddy = (void *) memory - size;

   buddy_link = NULL;
   if (! ListEmpty(&free_lists[level]))
      buddy_link = free_list_find(buddy);

   link = (LIST_ENTRY*) memory;
   InitializeListHead(link);
   InsertTailList(&free_lists[level], link);

   if ( buddy_link == buddy) {
      RemoveListEntry(link);
      RemoveListEntry(buddy_link);
      if ((index & 1) == 0)
         _free(link, level - 1);
      else
         _free(buddy_link, level - 1);
   }
}