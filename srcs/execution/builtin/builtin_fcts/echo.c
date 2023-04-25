/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:28:37 by mdorr             #+#    #+#             */
/*   Updated: 2023/04/25 12:19:30 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_arg_nbr(t_command *cmd_data, int arg_start_pos)
{
	int	arg_nbr;

	arg_nbr = 0;
	while (cmd_data->command[arg_nbr + arg_start_pos] != NULL)
		arg_nbr++;
	return (arg_nbr);
}

static bool	is_n_option(char *first_argument)
{
	return (ft_strncmp("-n", first_argument, 3) == 0);
}

void	echo_builtin(t_command *cmd_data)
{
	bool	n_option;
	size_t	arg_start_pos;
	size_t	arg_nbr;
	size_t	i;

	arg_start_pos = 1;
	n_option = is_n_option(cmd_data->command[arg_start_pos]);
	if (n_option == true)
		arg_start_pos++;
	arg_nbr = get_arg_nbr(cmd_data, arg_start_pos);
	i = 0;
	while (i < arg_nbr)
	{
		printf("%s", cmd_data->command[i + arg_start_pos]);
		if (i < arg_nbr - 1)
			printf(" ");
		i++;
	}
	if (n_option == false)
		printf("\n");
}
