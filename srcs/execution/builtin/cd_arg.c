/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:00:10 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/22 19:17:18 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_spec_arg(const char *arg)
{
	return (arg == NULL || streq(arg, TIELD) || streq(arg, MINUS_SIGN));
}

static char	*get_spec_path(const char *arg, bool *is_print)
{
	char	*var_name;
	char	*spec_path;

	if (arg == NULL || streq(arg, TIELD))
		var_name = HOME_VAR;
	else if (streq(arg, MINUS_SIGN) == true)
	{
		var_name = OLDPWD_VAR;
		*is_print = true;
	}
	spec_path = ft_strdup(ft_getenv(var_name));
	if (spec_path == NULL)
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
		return (get_spec_path(arg, is_print));
	if (can_be_found(arg) == true)
	{
		new_arg = get_path_from_env(arg, CDPATH_VAR, cmd_data->env);
		if (new_arg != NULL)
		{
			*is_print = true;
			return (new_arg);
		}
	}
	return (ft_strdup(arg));
}
