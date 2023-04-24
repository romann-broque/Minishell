/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:30:16 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/24 18:28:15 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_pwd(const char *new_pwd, const char *curr_path)
{
	char	*new;
	char	*tmp;

	tmp = ft_strjoin(curr_path, FWD_SLASH_STR);
	new = ft_strjoin(tmp, new_pwd);
	free(tmp);
	if (ft_strstr(new, BACKPATH) != NULL)
		tmp = rm_backpath(new);
	else
		tmp = ft_strdup(new);
	free(new);
	new = rm_double_slash(tmp);
	free(tmp);
	return (new);
}
