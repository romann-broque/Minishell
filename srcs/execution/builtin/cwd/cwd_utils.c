/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:15:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/29 19:01:41 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cwd_var(const char *pwd)
{
	const char	*curr_path = ft_getenv(PWD_VAR);
	char *const	new = clean_pwd(pwd, curr_path);

	if (ft_getenv(OLDPWD_VAR) == NULL)
		update_var(OLDPWD_VAR, curr_path, EXPORT_MASK);
	update_var(PWD_VAR, new, ENV_MASK);
	free(new);
}

void	update_cwd_var(const char *pwd)
{
	const char	*curr_path = ft_getenv(PWD_VAR);
	char *const	new = clean_pwd(pwd, curr_path);

	update_var(OLDPWD_VAR, curr_path, SET_MASK);
	update_var(PWD_VAR, new, SET_MASK);
	free(new);
}

void	check_pos(const char *caller)
{
	char *const	curr_pwd = getcwd(NULL, 0);

	if (curr_pwd == NULL)
	{
		print_error("%s: %s: %s: %s: %s\n",
			caller, ERROR_ACCESS_DIR, GETCWD,
			ERROR_ACCESS_PAR_DIR, strerror(errno));
	}
	free(curr_pwd);
}

static int	print_pos_exec(const char *caller, char *cwd, char *pos)
{
	char	*printed_pos;
	int		ret_val;

	ret_val = EXIT_SUCCESS;
	if (cwd != NULL && is_cmd_accessible(cwd) == true)
		printed_pos = cwd;
	else
		printed_pos = pos;
	if (ft_printf("%s\n", printed_pos) == -1)
	{
		print_error("%s: %s: %s: %s\n",
			MINISHELL, caller, WRITE_ERROR, strerror(errno));
		ret_val = EXIT_FAILURE;
	}
	return (ret_val);
}

int	print_pos(const char *caller)
{
	char *const	cwd = ft_getenv(PWD_VAR);
	char		*pos;
	int			ret_val;

	pos = getcwd(NULL, 0);
	if (pos != NULL)
		ret_val = print_pos_exec(caller, cwd, pos);
	else
	{
		print_error("%s: %s: %s: %s: %s\n",
			PWD_BUILTIN, ERROR_ACCESS_DIR, GETCWD,
			ERROR_ACCESS_PAR_DIR, strerror(errno));
		free(pos);
		ret_val = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	free(pos);
	return (ret_val);
}
