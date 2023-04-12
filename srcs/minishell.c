/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:07:50 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/11 17:24:10 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(
	__attribute__((unused)) int ac,
	__attribute__((unused)) char **av,
	const char **env)
{
	prompt(env);
	return (EXIT_SUCCESS);
}
