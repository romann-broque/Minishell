/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:08:04 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/10 10:41:10 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_strs(char **strs)
{
	while (*strs != NULL)
	{
		printf("-[%s]", *strs);
		++strs;
	}
	printf("-\n\n\n");
}

static void	print_env(char **env)
{
	while (*env != NULL)
	{
		printf("---\n");
		printf("[%s]\n", *env);
		printf("---\n");
		++env;
	}
	printf("-\n\n\n");
}

void	print_cmd(t_list *cmds)
{
	t_command	*cmd_data;

	printf("COMMAND:\n");
	while (cmds != NULL)
	{
		cmd_data = cmds->content;
		printf("ARG :\n");
		print_strs(cmd_data->command);
		printf("\nENV :\n");
		print_env(cmd_data->env);
		cmds = cmds->next;
	}
}

void	print_command(t_list *token_lst)
{
	char	*str_tmp;
	size_t	i;
	size_t	index;

	i = 0;
	index = 0;
	while (token_lst != NULL)
	{
		str_tmp = get_str_from_tok(token_lst->content);
		if (token_lst->content != NULL
			&& ft_strlen_safe(str_tmp) > 0)
		{
			printf("Element %zu : [%s]\n", i + 1, str_tmp);
			++i;
		}
		token_lst = token_lst->next;
		++index;
	}
}
