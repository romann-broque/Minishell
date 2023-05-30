/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:36:04 by mat               #+#    #+#             */
/*   Updated: 2023/05/29 17:04:10 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_command *cmd_data)
{
	int		ret_val;
	size_t	index;

	ret_val = EXIT_SUCCESS;
	index = 0;
	while (cmd_data->env[index] != NULL)
	{
		if (ft_printf("%s\n", cmd_data->env[index]) == -1)
		{
			print_error("%s: %s: %s: %s\n",
				MINISHELL, ENV_BUILTIN, WRITE_ERROR, strerror(errno));
			ret_val = EXIT_FAILURE;
			break ;
		}
		++index;
	}
	return (ret_val);
}
