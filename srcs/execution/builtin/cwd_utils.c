/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:15:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/22 15:30:53 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_cwd_var(void)
{
	char *const	curr_pwd = getcwd(NULL, 0);

	if (curr_pwd != NULL)
	{
		change_var(OLDPWD_VAR, ft_getenv(PWD_VAR));
		change_var(PWD_VAR, curr_pwd);
	}
	else
	{
		print_error("%s: %s: %s: %s: ",
			CHDIR, ERROR_ACCESS_DIR, GETCWD, ERROR_ACCESS_PAR_DIR);
		perror(EMPTY_STR);
	}
	free(curr_pwd);
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
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		print_error("%s: %s: %s: %s: ",
			PWD_BUILTIN, ERROR_ACCESS_DIR, GETCWD, ERROR_ACCESS_PAR_DIR);
		perror(EMPTY_STR);
	}
	free(cwd);
}
