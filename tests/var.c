#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	int		i;
	char	*var_value;

	if (ac > 1)
	{
		i = 0;
		while (av[i + 1] != NULL)
		{
			var_value = getenv(av[i + 1]);
			printf("var is [%s]\n", var_value);
			++i;
		}
	}
}
