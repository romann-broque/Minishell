/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:28:37 by mdorr             #+#    #+#             */
/*   Updated: 2023/04/28 11:03:57 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static bool	is_n_option(char *first_argument)
{
	return (first_argument != NULL && streq(ECHO_OPT, first_argument) == true);
}

int	echo_builtin(t_command *cmd_data)
{
	bool	n_option;
	char	**str_ptr;
	size_t	i;

	str_ptr = cmd_data->command + 1;
	n_option = is_n_option(str_ptr[0]);
	if (n_option == true)
		str_ptr++;
	i = 0;
	while (str_ptr[i] != NULL)
	{
		printf("%s", str_ptr[i]);
		if (str_ptr[i + 1] != NULL)
			printf(SPACE_STR);
		i++;
	}
	if (n_option == false)
		printf(NEWLINE_STR);
	return (0);
}
