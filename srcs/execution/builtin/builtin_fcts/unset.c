/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:57:44 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/08 11:06:31 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static bool	is_same_varkey(t_var *var1, t_var *var2)
{
	return (streq(var1->key, var2->key));
}

static void	unset_arg(char *arg)
{
	const t_var	var_ref = {.key = arg};

	ft_list_remove_if(&(g_global.env),
		(void *)&var_ref,
		(bool (*)(void *, void *))is_same_varkey,
		(void (*)(void *))free_var);
}

int	unset_builtin(t_command *cmd)
{
	char	**command;

	command = cmd->command + 1;
	while (*command != NULL)
	{
		unset_arg(*command);
		++command;
	}
	return (EXIT_SUCCESS);
}
