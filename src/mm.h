#include <stdio.h>

extern int mm_init (void);
extern void *mm_malloc (size_t size);
extern void mm_free (void *ptr);
extern void *mm_realloc(void *ptr, size_t size);


/* 
 * Students work in teams of one or two.  Teams enter their team name, 
 * personal names and login IDs in a struct of this
 * type in their bits.c file.
 */
typedef struct {
    char *teamname; /* ID1+ID2 or ID1 */
    char *name1;    /* full name of first member */
    char *id1;      /* login ID of first member */
    char *name2;    /* full name of second member (if any) */
    char *id2;      /* login ID of second member */
} team_t;

extern team_t team;


/* 基本常数大小 */
#define WSIZE   4   /* 字大小 */
#define DSIZE   8   /* 双字大小 */
#define CHUNKSIZE   (1<<12) /* 初始块大小和扩展堆时的默认大小 */

#define MAX(x,y)    ((x) > (y)? (x) : (y))

#define PACK(size,alloc) ((size)|(alloc))   /* 将大小和已分配位结合并返回一个值，可把它存放在头部或者脚部中 */

#define GET(p)      (*(unsigned int *)(p))          /* 读取和返回参数p引用的字 */
#define PUT(p,val)  (*(unsigned int *)(p) = (val))  /* 将val存放在参数p指向的字中*/

#define GET_SIZE(p)     (GET(p) & -0x7) /* 从p处的头部或者脚部分别返回大小 */
#define GET_ALLOC(p)    (GET(p) & 0x1)  /* 从p处的头部或者脚部分别返回已分配位 */

#define HDRP(bp)    ((char *)(bp) - WSIZE)  /* 返回指向块的头部 */
#define FTRP(bp)    ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE) /* 返回指向块的脚部 */

#define NEXT_BLKP(bp)   ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))   /* 返回指向后面的块的块指针 */
#define PREV_BLKP(bp)   ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))   /* 返回指向前面的块的块指针 */
