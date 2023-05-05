/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:55:33 by mat               #+#    #+#             */
/*   Updated: 2023/05/05 10:00:53 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	export_to_env(char	*arg)
{
	if (is_assign_tok_state(arg) == true)
		add_assignation_to_env(arg);
	else
		add_key_to_env(arg);
}

static bool	is_valid_identifier(char *arg)
{
	size_t	index;

	if (is_in_var_start_charset(arg[0]) == false)
		return (false);
	index = 1;
	while (arg[index] != '\0' && arg[index] != '=')
	{
		if (is_in_var_charset(arg[index]) == false)
			return (false);
		index++;
	}
	return (true);
}

static void	print_export(void)
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
}

static void	handle_export_arg(char *arg, bool *error)
{
	if (is_valid_identifier(arg))
		export_to_env(arg);
	else
	{
		print_error("%s: %s: `%s': %s\n",
			MINISHELL, EXPORT_BUILTIN, arg,
			INVALID_ID);
		*error = true;
	}
}

int	export_builtin(t_command *cmd_data)
{
	int		index;
	bool	error;

	error = false;
	if (cmd_data->command[1] == NULL)
		print_export();
	else
	{
		index = 1;
		while (cmd_data->command[index] != NULL)
		{
			handle_export_arg(cmd_data->command[index], &error);
			index++;
		}
	}
	if (error == true)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
