/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:15:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/21 16:16:03 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_cwd_var(void)
{
	char *const	curr_pwd = getcwd(NULL, 0);

	if (curr_pwd != NULL)
	{
		change_var("OLDPWD", ft_getenv("PWD"));
		change_var("PWD", curr_pwd);
	}
	free(curr_pwd);
}
