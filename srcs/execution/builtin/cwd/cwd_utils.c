/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:15:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/08 15:43:28 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_cwd_var(const char *pwd)
{
	const char	*curr_path = ft_getenv(PWD_VAR);
	char *const	new = clean_pwd(pwd, curr_path);

	update_var(OLDPWD_VAR, curr_path, ENV_MASK);
	update_var(PWD_VAR, new, ENV_MASK);
	free(new);
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

int	print_pos(void)
{
	const char	*cwd = ft_getenv(PWD_VAR);
	char		*pos;

	pos = getcwd(NULL, 0);
	if (pos != NULL)
	{
		if (cwd != NULL && is_cmd_accessible(cwd) == true)
			ft_printf("%s\n", cwd);
		else
			ft_printf("%s\n", pos);
	}
	else
	{
		print_error("%s: %s: %s: %s: ",
			PWD_BUILTIN, ERROR_ACCESS_DIR, GETCWD, ERROR_ACCESS_PAR_DIR);
		perror(EMPTY_STR);
		free(pos);
		return (EXIT_FAILURE);
	}
	free(pos);
	return (EXIT_SUCCESS);
}
