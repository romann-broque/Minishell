/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:47:29 by mat               #+#    #+#             */
/*   Updated: 2023/04/21 16:13:57 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(__attribute__((unused)) t_command *cmd_data)
{
	char	*cwd;

	update_cwd_var();
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
		ft_printf("%s\n", cwd);
	free(cwd);
}
