/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:44:29 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/14 13:45:26 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

extern char	**g_env;

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

static t_list	*get_list_from_array_cmd(t_command *array, const size_t size)
{
	size_t	i;
	t_list	*cmd_list;

	cmd_list = NULL;
	i = 0;
	while (i < size)
	{
		ft_lstadd_back(&cmd_list, ft_lstnew(array + i));
		i++;
	}
	return (cmd_list);
}

static bool	strs_eq(char **strs1, char **strs2)
{
	while (*strs1 != NULL && *strs2 != NULL
		&& streq(*strs1, *strs2) == true)
	{
		++strs1;
		++strs2;
	}
	return (*strs1 == NULL && *strs2 == NULL);
}

static bool	is_same_cmd(t_command *cmd1, t_command *cmd2)
{
	return ((cmd1 == NULL && cmd2 == NULL)
		|| (cmd1 != NULL && cmd2 != NULL
		&& strs_eq(cmd1->command, cmd2->command) == true
		&& strs_eq(cmd1->env, cmd2->env) == true
		&& cmd1->fdin == cmd2->fdin
		&& cmd1->fdout == cmd2->fdout)
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

static bool	is_cmd_valid(t_token *tok_array, t_command *cmd_array, const size_t size_cmd_array)
{
	t_list	*tok_list = get_list_from_array(tok_array);
	t_list	*cmd_exp = get_list_from_array_cmd(cmd_array, size_cmd_array);
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
			"commo",
			"esta",
			NULL
			},
		.env = g_env,
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
		},
	};
	
	t_token	toks2[] = {
		{.type = T_START, .value = NULL},
		{.type = T_END, .value = NULL}
	};
	t_command	*cmds2 = NULL;
	t_token	toks3[] = {
		{.type = T_START, .value = NULL},
		{.type = T_GENERIC, .value = "ls"},
		{.type = T_GENERIC, .value = "srcs/"},
		{.type = T_PIPE, .value = PIPE},
		{.type = T_GENERIC, .value = "cat"},
		{.type = T_GENERIC, .value = "lol"},
		{.type = T_END, .value = NULL}
	};
	t_command	cmds3[] = {
		{.command = (char *[]){
			"ls",
			"srcs/",
			NULL
			},
		.env = g_env,
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
		},
		{.command = (char *[]){
			"cat",
			"lol",
			NULL
			},
		.env = g_env,
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
		},
	};
	t_token	toks4[] = {
		{.type = T_START, .value = NULL},
		{.type = T_GENERIC, .value = "ls"},
		{.type = T_GENERIC, .value = "srcs/"},
		{.type = T_GENERIC, .value = "|"},
		{.type = T_GENERIC, .value = "cat"},
		{.type = T_GENERIC, .value = "lol"},
		{.type = T_END, .value = NULL}
	};
	t_command	cmds4[] = {
		{.command = (char *[]){
			"ls",
			"srcs/",
			"|",
			"cat",
			"lol",
			NULL
			},
		.env = g_env,
		.fdin = STDIN_FILENO,
		.fdout = STDOUT_FILENO,
		},
	};

	CU_ASSERT_TRUE(is_cmd_valid(toks1, cmds1, 1));
	CU_ASSERT_TRUE(is_cmd_valid(toks2, cmds2, 0));
	CU_ASSERT_TRUE(is_cmd_valid(toks3, cmds3, 2));
	CU_ASSERT_TRUE(is_cmd_valid(toks4, cmds4, 1));
}
