/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:15:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/24 18:02:37 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_cwd_var(const char *new_pwd)
{
	const char	*curr_path = ft_getenv(PWD_VAR);
	char *const	clean_pwd = ft_remove_neighboor(new_pwd, FWD_SLASH_STR);
	char		*new;

	if (curr_path != NULL && clean_pwd[0] != FWD_SLASH)
	{
		new = get_clean_pwd_value(clean_pwd, curr_path);
		change_var(OLDPWD_VAR, ft_getenv(PWD_VAR));
		change_var(PWD_VAR, new);
		free(new);
	}
	else
	{
		change_var(OLDPWD_VAR, ft_getenv(PWD_VAR));
		change_var(PWD_VAR, clean_pwd);
	}
	free(clean_pwd);
}

void	check_pos(const char *caller)
{
	char *const	curr_pwd = getcwd(NULL, 0);

	if (curr_pwd == NULL)
	{
		print_error("%s: %s: %s: %s: ",
			caller, ERROR_ACCESS_DIR, GETCWD, ERROR_ACCESS_PAR_DIR);
		perror(EMPTY_STR);
	}
	free(curr_pwd);
}

void	print_pos(void)
{
	const char	*cwd = ft_getenv(PWD_VAR);
	char		*pos;

	pos = getcwd(NULL, 0);
	if (pos != NULL && cwd == NULL)
	{
		update_cwd_var(pos);
		cwd = ft_getenv(PWD_VAR);
	}
	if (pos != NULL && cwd != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		print_error("%s: %s: %s: %s: ",
			PWD_BUILTIN, ERROR_ACCESS_DIR, GETCWD, ERROR_ACCESS_PAR_DIR);
		perror(EMPTY_STR);
	}
	free(pos);
}
