/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:44:29 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/11 19:31:05 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

#define MAX_LEN_CMD 100

extern const char	**g_env;

// static void	free_command_arg(t_command *cmd)
// {
// 	if (cmd != NULL)
// 		free_strs(cmd->command);
// }

static t_list	*get_list_from_array(t_token *array)
{
	size_t	i;
	t_list	*tokens_list;

	tokens_list = NULL;
	i = 0;
	while (array[i].type != T_END)
	{
		ft_lstadd_back(&tokens_list, ft_lstnew(array + i));
		i++;
	}
	ft_lstadd_back(&tokens_list, ft_lstnew(array + i));
	return (tokens_list);
}

static t_list	*get_list_from_array_cmd(t_command *array)
{
	size_t	i;
	t_list	*cmd_list;

	cmd_list = NULL;
	i = 0;
	while (array[i].command[0] != NULL)
	{
		ft_lstadd_back(&cmd_list, ft_lstnew(array + i));
		i++;
	}
	ft_lstadd_back(&cmd_list, ft_lstnew(array + i));
	return (cmd_list);
}

static bool	strs_eq(const char **strs1, const char **strs2)
{
	while (strs1 != NULL && strs2 != NULL
		&& streq(*strs1, *strs2) == true)
	{
		++strs1;
		++strs2;
	}
	return (strs1 == NULL && strs2 == NULL);
}

static bool	is_same_cmd(t_command *cmd1, t_command *cmd2)
{
	return (cmd1 != NULL && cmd2 != NULL
		&& strs_eq((const char **)cmd1->command, (const char **)cmd2->command) == true
		&& strs_eq(cmd1->env, cmd2->env) == true
		&& cmd1->fdin == cmd2->fdin
		&& cmd1->fdout == cmd2->fdout
	);
}

static bool	comp_commands(t_list *cmd_out, t_list *cmd_exp)
{
	while (cmd_out != NULL && cmd_exp != NULL
		&& is_same_cmd(cmd_out->content, cmd_exp->content) == true)
	{
		cmd_out = cmd_out->next;
		cmd_exp = cmd_exp->next;
	}
	return (cmd_out == NULL && cmd_exp == NULL);
}

static bool	is_cmd_valid(t_token *tok_array, t_command *cmd_array)
{
	t_list	*tok_list = get_list_from_array(tok_array);
	t_list	*cmd_exp = get_list_from_array_cmd(cmd_array);
	t_list	*cmd_out = interpreter(tok_list, g_env);
	bool	ret_val = comp_commands(cmd_out, cmd_exp);

	ft_lstclear(&tok_list, NULL);
	ft_lstclear(&cmd_exp, NULL);
	ft_lstclear(&cmd_out, (void (*)(void *))free_command);
	return (ret_val);
}

void	interpreter__test(void)
{
	t_token	toks1[] = {
		{.type = T_START, .value = NULL},
		{.type = T_GENERIC, .value = "hola"},
		{.type = T_GENERIC, .value = "commo"},
		{.type = T_GENERIC, .value = "esta"},
		{.type = T_END, .value = NULL}
	};
	t_command	cmds1[] = {
		{.command = (char *[]){
			"hola",
			"como",
			"esta"
			},
		.env = g_env,
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
		},
		{.command = (char *[]){NULL}}
	};

	CU_ASSERT_TRUE(is_cmd_valid(toks1, cmds1));
}
