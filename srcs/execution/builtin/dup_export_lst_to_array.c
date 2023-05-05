/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_export_lst_to_array.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:09:02 by mat               #+#    #+#             */
/*   Updated: 2023/05/05 11:06:56 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_assign_from_export_var(t_var *var)
{
	char	*tmp;
	char	*tmp2;
	char	*assign;

	tmp = NULL;
	if (var->value != NULL)
	{
		tmp = ft_strjoin("\"", var->value);
		tmp2 = ft_strjoin_free(tmp, "\"");
		tmp = ft_strjoin(EQUAL_SIGN_STR, tmp2);
		free(tmp2);
	}
	assign = ft_strjoin(var->key, tmp);
	free(tmp);
	return (assign);
}

char	**dup_export_lst_to_array(t_list *env_lst)
{
	return (get_env_array(env_lst, EXPORT_MASK,
			get_assign_from_export_var));
}
