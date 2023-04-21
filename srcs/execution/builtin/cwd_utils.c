/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:15:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/21 17:27:54 by rbroque          ###   ########.fr       */
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
	free(curr_pwd);
}

void	print_pos(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
		ft_printf("%s\n", cwd);
	free(cwd);
}
