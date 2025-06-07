#include "../include/libft.h"

static int	count = 0;

void	*malloc_B(size_t size)
{
	if (--count == 0)
		return (NULL);
	return ((malloc)(size));
}