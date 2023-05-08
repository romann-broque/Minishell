/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:55:33 by mat               #+#    #+#             */
/*   Updated: 2023/05/07 15:41:53 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	export_to_env(char *arg)
{
	t_var *const	var = export_var_from_str(arg, is_assign_tok_state(arg));
	t_var			*old_var;

	if (var != NULL)
	{
		old_var = get_var(var->key);
		if (old_var != NULL && var->value == NULL)
			update_var(old_var->key, NULL, EXPORT_MASK);
		else
			update_var(var->key, var->value, EXPORT_MASK);
	}
	free_var(var);
}

static bool	is_valid_identifier(char *arg)
{
	size_t	index;

	if (is_in_var_start_charset(arg[0]) == false)
		return (false);
	index = 1;
	while (arg[index] != '\0' && arg[index] != EQUAL_SIGN)
	{
		if (is_in_var_charset(arg[index]) == false)
			return (false);
		index++;
	}
	return (true);
}

static int	print_export(void)
{
	char	**export_array;
	size_t	index;

	export_array = dup_export_lst_to_array(g_global.env);
	sort_strings(export_array);
	index = 0;
	while (export_array[index] != NULL)
	{
		printf("%s %s\n", EXPORT_BUILTIN, export_array[index]);
		index++;
	}
	free_strs(export_array);
	return (EXIT_SUCCESS);
}

static int	handle_export_arg(char *arg)
{
	if (is_valid_identifier(arg))
		export_to_env(arg);
	else
	{
		print_error("%s: %s: `%s': %s\n",
			MINISHELL, EXPORT_BUILTIN, arg,
			INVALID_ID);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	export_builtin(t_command *cmd_data)
{
	int	index;
	int	exit_status;

	exit_status = EXIT_FAILURE;
	if (cmd_data->command[1] == NULL)
		exit_status = print_export();
	else
	{
		index = 1;
		while (cmd_data->command[index] != NULL)
		{
			exit_status = handle_export_arg(cmd_data->command[index]);
			index++;
		}
	}
	return (exit_status);
}
