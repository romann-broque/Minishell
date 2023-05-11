/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode_utils,.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:09:53 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/10 14:13:05 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	are_same_cmds(t_command *cmd1, t_command *cmd2)
{
	size_t	i;

	if (cmd1->command == NULL || cmd2->command == NULL)
		return (cmd1->command == cmd2->command);
	i = 0;
	while (cmd1->command[i] != NULL
		&& cmd2->command[i] != NULL
		&& streq(cmd1->command[i], cmd2->command[i]) == true)
			++i;
	return (cmd1->command[i] == NULL
		&& cmd2->command[i] == NULL);
}

void	clean_commands(t_list **commands)
{
	const t_command	cmd_ref = {.command = NULL};

	ft_list_remove_if(commands,
		(void *)(&cmd_ref),
		(bool (*)(void *, void *))are_same_cmds,
		(void (*)(void *))free_command);
}

void	clear_local_env(t_list **env)
{
	ft_lstclear(env, (void (*)(void *))free_var);
	*env = NULL;
}
