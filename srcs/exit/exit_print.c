/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:35:37 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/22 12:35:47 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(const int exit_value)
{
	ft_dprintf(STDERR_FILENO, "%s\n", EXIT_MESSAGE);
	exit(exit_value);
}
