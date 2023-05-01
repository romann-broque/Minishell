/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:48:25 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/01 17:23:25 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static bool	is_first_arg_num(char *first_arg)
{
	size_t	i;

	i = 0;
	while (first_arg[i] != '\0')
	{
		if (ft_isdigit(first_arg[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

int	exit_builtin(t_command *cmd_data)
{
	if (cmd_data->command[1] != NULL)
	{
		if (is_first_arg_num(cmd_data->command[1]) == true)
		{
			if (cmd_data->command[2] == NULL)
				exit_shell(ft_atoi(cmd_data->command[1]), true);
			else
			{
				print_error("%s\n%s: %s: too many arguments\n",
					EXIT_MESSAGE, MINISHELL, cmd_data->command[0]);
				return (g_global.last_ret_val);
			}
		}
		else
		{
			print_error("%s\n%s: %s: %s: numeric argument required\n",
				EXIT_MESSAGE, MINISHELL, cmd_data->command[0],
				cmd_data->command[1]);
			exit_shell(INCORRECT_USE, false);
		}
	}
	exit_shell(g_global.last_ret_val, true);
	return (EXIT_SUCCESS);
}
