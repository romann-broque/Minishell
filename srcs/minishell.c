/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:07:50 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/19 18:59:33 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(
	__attribute__((unused)) int ac,
	__attribute__((unused)) char **av,
	char **env)
{
	if (batch_mode(ac, av) == true)
	{
		ft_printf("BATCH MODE\n");
		exec_batch(ac, av);
	}
	else
		prompt(env);
	return (EXIT_SUCCESS);
}
