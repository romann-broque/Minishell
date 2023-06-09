/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:00:10 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/29 19:12:06 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_spec_arg(const char *arg)
{
	return (arg == NULL
		|| streq(arg, TIELD)
		|| streq(arg, MINUS_SIGN));
}

static char	*get_var_value(const char *var_name, char **env)
{
	t_var	*var;
	char	*var_value;

	var_value = ft_getenv_local(var_name, env);
	if (var_value == NULL)
	{
		var = get_var(var_name);
		if (var != NULL)
		{
			if (var->flags == SLEEP_MASK)
				return (NULL);
			var_value = var->value;
		}
	}
	return (var_value);
}

static char	*get_spec_path(const char *arg, char **env, bool *is_print)
{
	char	*var_name;
	char	*var_value;
	char	*spec_path;

	if (arg == NULL || streq(arg, TIELD))
		var_name = HOME_VAR;
	else if (streq(arg, MINUS_SIGN) == true)
	{
		var_name = OLDPWD_VAR;
		*is_print = true;
	}
	var_value = get_var_value(var_name, env);
	spec_path = NULL;
	if (var_value != NULL)
		spec_path = ft_strdup(var_value);
	else
		print_error("%s: %s: %s not set\n", MINISHELL,
			CD_BUILTIN, var_name);
	return (spec_path);
}

static bool	can_be_found(const char *arg)
{
	return (arg != NULL && arg[0] != FWD_SLASH && arg[0] != DOT);
}

char	*get_cd_arg(t_command *cmd_data, const char *arg, bool *is_print)
{
	char	*new_arg;

	if (is_spec_arg(arg) == true)
		return (get_spec_path(arg, cmd_data->env, is_print));
	if (can_be_found(arg) == true)
	{
		if (arg[0] == '\0')
			arg = DOT_STR;
		new_arg = get_path_from_env(arg, CDPATH_VAR, cmd_data->env);
		if (new_arg != NULL)
		{
			*is_print = true;
			return (new_arg);
		}
	}
	return (ft_strdup(arg));
}
