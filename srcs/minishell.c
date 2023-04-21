/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:07:50 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/21 10:53:30 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

int	main(
	__attribute__((unused)) int ac,
	__attribute__((unused)) char **av,
	char **env)
{
	prompt(env);
	return (EXIT_SUCCESS);
}
