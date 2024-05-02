

#include "cub.h"

#define UP 119
#define DOWN 115
#define RIGHT 100
#define LEFT 97

int	ft_strlen_sl(const char *s)
{
	int	x;

	x = 0;
	while (s[x] != '\0' && s[x] != '\n')
		x++;
	return (x);
}


int	read_esc(int keycode, t_main *main)
{
	if (keycode == 65307)
		end(main);
	return (0);
}
