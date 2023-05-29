/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:28:37 by mdorr             #+#    #+#             */
/*   Updated: 2023/05/29 16:05:07 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static bool	is_n_option(char *str)
{
	bool	is_option;

	is_option = false;
	if (*str == '-')
	{
		++str;
		while (*str != '\0' && *str == 'n')
		{
			is_option = true;
			++str;
		}
		if (*str != '\0')
			is_option = false;
	}
	return (is_option);
}

static bool	get_n_option(char ***strs)
{
	bool	is_option;

	is_option = false;
	while (**strs != NULL && is_n_option(**strs) == true)
	{
		is_option = true;
		++(*strs);
	}
	return (is_option);
}

int	echo_builtin(t_command *cmd_data)
{
	bool	n_option;
	char	**str_ptr;
	char	*output;

	str_ptr = cmd_data->command + 1;
	n_option = get_n_option(&str_ptr);
	output = get_echo_output(str_ptr, n_option);
	ft_printf(output);
	free(output);
	return (EXIT_SUCCESS);
}
