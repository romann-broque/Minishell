/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:36:04 by mat               #+#    #+#             */
/*   Updated: 2023/05/08 10:03:58 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_command *cmd_data)
{
	size_t	index;

	index = 0;
	while (cmd_data->env[index] != NULL)
		printf("%s\n", cmd_data->env[index++]);
	return (0);
}
