/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:48:25 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/02 12:16:39 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static bool	is_inbounds(long nb, long added_nb, bool is_neg)
{
	const long	bound = (LONG_MAX - is_neg - added_nb) / 10;

	return (nb <= bound);
}

static bool	check_and_updates_retval(long *ret_value, char *str)
{
	long	nb;
	bool	is_neg;

	nb = 0;
	is_neg = (*str == '-');
	str += (*str == '-' || *str == '+');
	while (ft_isdigit(*str) != 0)
	{
		if (is_inbounds(nb, *str - '0', is_neg) == false)
			break ;
		nb = nb * 10 + (*str - '0');
		str++;
	}
	if (*str == '\0')
	{
		if (is_neg == true)
			nb = -nb;
		*ret_value = nb;
		return (true);
	}
	return (false);
}

static int	exit_num_arg(const char *second_arg, const long nb)
{
	if (second_arg == NULL)
		exit_shell(nb, true);
	else
	{
		print_error("%s\n%s: %s: %s\n",
			EXIT_MESSAGE, MINISHELL, EXIT_BUILTIN, TOO_MANY_ARGS);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	exit_invalid_arg(const char *invalid_arg)
{
	print_error("%s\n%s: %s: %s: %s\n",
		EXIT_MESSAGE, MINISHELL, EXIT_BUILTIN, invalid_arg, NUM_ARG_REQ);
	exit_shell(INCORRECT_USE, false);
}

int	exit_builtin(t_command *cmd_data)
{
	long	nb;

	if (cmd_data->command[1] != NULL)
	{
		if (check_and_updates_retval(&nb, cmd_data->command[1]) == true)
			return (exit_num_arg(cmd_data->command[2], nb));
		else
			exit_invalid_arg(cmd_data->command[1]);
	}
	exit_shell(g_global.last_ret_val, true);
	return (EXIT_SUCCESS);
}
