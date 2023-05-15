/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:28:37 by mdorr             #+#    #+#             */
/*   Updated: 2023/05/15 10:29:19 by rbroque          ###   ########.fr       */
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
		ft_printf("%s", str_ptr[i]);
		if (str_ptr[i + 1] != NULL)
			ft_printf(SPACE_STR);
		i++;
	}
	if (n_option == false)
		ft_printf(NEWLINE_STR);
	return (EXIT_SUCCESS);
}
