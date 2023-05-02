/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:07:50 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/02 17:57:03 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

int	main(
	__attribute__((unused)) int ac,
	__attribute__((unused)) char **av,
	char **env)
{
	init_shell(env);
	prompt();
	return (EXIT_SUCCESS);
}
