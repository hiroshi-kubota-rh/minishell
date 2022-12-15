#include "minishell.h"

//mallocの失敗は問答無用で1を返す．
static void memory_out ()
{
	write (2, "virtual memory exhausted\n", 25);
	exit (1);
}

void *xmalloc (size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		memory_out();
	return ptr;
}


