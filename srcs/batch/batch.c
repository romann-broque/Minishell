/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   batch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:50:59 by mat               #+#    #+#             */
/*   Updated: 2023/04/19 19:05:08 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	batch_mode(int ac, char **av)
{
	if (ac > 1)
	{
		if (ft_strcmp(BATCH_OPT, av[1]) == 0)
			return (true);
	}
	return (false);
}

void	exec_batch(int ac, char **av)
{
	(void)ac;
	(void)av;
	return ;
}
