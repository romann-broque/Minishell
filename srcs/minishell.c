/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:07:50 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/21 11:50:03 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

int	main(
	__attribute__((unused)) int ac,
	__attribute__((unused)) char **av,
	char **env)
{
	init_env(&g_global, env);
	prompt();
	return (EXIT_SUCCESS);
}
