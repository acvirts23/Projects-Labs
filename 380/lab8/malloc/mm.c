/*
*Andrew Virts
*Malloc
*Due Date: 4/22/20
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memlib.h"
#include "mm.h"

/****************************************************************/
// Useful type aliases

typedef uint64_t word;
typedef uint32_t tag;
typedef uint8_t  byte;
typedef byte*    address; 

/****************************************************************/
// Useful constants

const uint8_t WORD_SIZE = sizeof (word);
static address g_hp;

/****************************************************************/
// function prototypes

// returns header address given base pointer
static inline tag* header (address);

// return true if block is allocated
static inline bool 
isAllocated (address);

// returns size of block
static inline uint32_t 
sizeOf (address);

// return true if tag is allocated
static inline bool
isTagAllocated (tag*);

// returns size of tag
static inline uint32_t
sizeOfTag (tag*);

// returns footer address given base pointer
static inline tag* 
footer (address);

// returns the base pointer of the next block
static inline address 
nextBlock (address);

// returns a pointer to the prev block’s footer
static inline tag* 
prevFooter (address);

// returns a pointer to the next block’s header.
static inline tag* 
nextHeader (address);

//Gives us the base pointer of the previous block
static inline address 
prevBlock (address);

// base pointer, size, allocated
static inline void
makeBlock (address, uint32_t, bool);

// base pointer, toggles alloced/free
static inline void toggleBlock (address);

int
mm_init (void);

void*
mm_malloc (uint32_t size);

void
mm_free (void* ptr);

void*
mm_realloc (void* ptr, uint32_t size);

address
extend_heap (uint32_t bytes);

uint32_t
blockSizeFor (uint32_t bytes);

address
coalesce (address basePtr);

void
printHeap ();

/****************************************************************/
// inline functions

// returns header address
static inline tag*
header (address addr)
{
  return ((tag*)(addr)-1);
}

// return true if block is allocated
static inline bool
isAllocated (address addr)
{
  return *header (addr) & 0x1;
}

// returns size of block
static inline uint32_t
sizeOf (address addr)
{
  return (*header (addr)) & (uint32_t)-2;
}

// returns true if tag is allocated
static inline bool
isTagAllocated (tag* t)
{
  return *t & 1;
}

// returns size of tag
static inline uint32_t
sizeOfTag (tag* t)
{
  return *t & (uint32_t)-2;
}

// returns footer address given base pointer
static inline tag*
footer (address addr)
{
  return (tag*)(addr + (sizeOf (addr) - 1) * sizeof (word));
}

// returns the base pointer of the next block
static inline address
nextBlock (address addr)
{
  return addr + sizeOf (addr) * sizeof (word);
}

// returns a pointer to the prev block’s footer
static inline tag*
prevFooter (address addr)
{
  return header (addr) - 1;
}

// returns a pointer to the next block’s header.
static inline tag*
nextHeader (address addr)
{
  return header (nextBlock (addr));
}

//Gives us the base pointer of the previous block
static inline address
prevBlock (address addr)
{
  return addr - (*prevFooter (addr) & (uint32_t)-2) * sizeof (word);
}

static inline void
makeBlock (address addr, uint32_t size, bool allocated)
{
  if (allocated && sizeOf (addr) - size >= 2)
  {
    uint32_t freeBlockSize = sizeOf (addr);
    uint32_t newFreeBlockSize = freeBlockSize - size;
    *header (addr) = size | allocated;
    *footer (addr) = size | allocated;
    addr = nextBlock (addr);
    *header (addr) = newFreeBlockSize;
    *footer (addr) = newFreeBlockSize;
  }
  else
  {
    *header (addr) = size | allocated;
    *footer (addr) = size | allocated;
  }
}

//basePtr
//toggles alloced/free
static inline void
toggleBlock (address addr)
{
  *header (addr) ^= 0x1;
  *footer (addr) ^= 0x1;
  return;
}

/****************************************************************/
// Non-inline functions

//init is the first thing ran by the calling program, before anything else is run
//Init will perform any initial initializations so our program can run properly
//Returns 0 if success, or -1 if there was a problem
int
mm_init (void)
{
  //create initial empty heap
  if ((g_hp = mem_sbrk (2 * sizeof (word))) == (void*)-1)
  {
    return -1;
  }
  g_hp = extend_heap (1 << 8);
  *prevFooter (g_hp) = 0 | true;
  return 0;
}

/****************************************************************/

//Returns a pointer to an allocated block
//The entire allocated block must lie within the heap region
void*
mm_malloc (uint32_t size)
{
  if (size == 0)
  {
    return NULL;
  }
  const uint32_t blocks = blockSizeFor (size);
  address scan = g_hp;
  while (sizeOf (scan) != 0)
  {
    if (!isAllocated (scan) && sizeOf (scan) >= blocks)
    {
      break;
    }
    scan = nextBlock (scan);
  }
  if (isAllocated (scan))
  {
    scan = extend_heap (blocks);
  }
  makeBlock (scan, blocks, true);
  return scan;
}

/****************************************************************/
/*
The mm_free routine frees the block pointed to by ptr
It will not return anything, however, this routine is only guaranteed to work when the passed pointer was returned
by a prior call to mm_malloc or mm_realloc 
*/
void
mm_free (void *ptr)
{
  address base = (address)ptr;
  toggleBlock (base);
  coalesce (base);
}

/****************************************************************/
//If the pointer is NULL, the call is basically mm_malloc(size)
//If the size is 0, the function basically just calls free()
//If the pointer is not NULL, it must have been returned by an earlier call to malloc or realloc
//The contents of the new block are the same as those of the old, in addition to any new information
void*
mm_realloc (void *ptr, uint32_t size)
{
  if (ptr == NULL)
  {
    ptr = mm_malloc (size);
    return ptr;
  }
  if (size == 0)
  {
    mm_free (ptr);
    return NULL;
  }
  void* newPtr = mm_malloc (size);
  if (newPtr == NULL)
  {
    return newPtr;
  }
  uint32_t currentSize =
    (uint32_t) (sizeOf (ptr) * sizeof (word) - 2 * sizeof (tag));
  uint32_t copySize = (currentSize > size) ? size : currentSize;
  memcpy (newPtr, ptr, copySize);
  mm_free (ptr);
  return newPtr;
}

//extends heap
address
extend_heap (uint32_t blocks)
{
  address base = (address)mem_sbrk ((int)(sizeof (word) * blocks));
  if (base == (void*)-1)
  {
    fprintf (stderr, "ERROR: mem_sbrk failed. Ran out of memory...\n");
    return NULL;
  }
  makeBlock (base, blocks, false);
  *nextHeader (base) = 0 | true;
  return coalesce (base);
}

//returns block size
uint32_t
blockSizeFor (uint32_t bytes)
{
  uint32_t const OVERHEAD = 2 * sizeof (tag);
  uint32_t const DWORD = 2 * sizeof (word);
  uint32_t const SIZE = bytes + OVERHEAD;
  uint32_t const DWORD_SIZE = (SIZE + (DWORD - 1)) / DWORD;
  return DWORD_SIZE * 2;
}

//coalesces free blocks of memory
address
coalesce (address basePtr)
{
  tag* prev = prevFooter (basePtr);
  tag* next = nextHeader (basePtr);
  uint32_t newSize = sizeOf (basePtr);
  if (!isTagAllocated (prev))
  {
    newSize += sizeOfTag (prev);
    basePtr = prevBlock (basePtr);
  }
  if (!isTagAllocated (next))
  {
    newSize += sizeOfTag (next);
  }
  makeBlock (basePtr, newSize, false);
  return basePtr;
}


//prints out the structure of heap
void
printHeap ()
{
  return;
  int blockCount = 1;
  for (address scan = g_hp; sizeOf (scan) != 0; scan = nextBlock (scan))
  {
    fprintf (stderr, "Block ID: %d\n", blockCount);
    fprintf (stderr, "Block size: %u\n", sizeOf (scan));
    fprintf (stderr, "Address: %p\n", scan);
    fprintf (stderr, "Allocated: %d\n", isAllocated (scan));
    ++blockCount;
  }
  return;
}
