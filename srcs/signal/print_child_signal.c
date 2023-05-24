/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_child_signal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:21:46 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/24 17:27:13 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_child_signal(const int status)
{
	int	signum;

	if (WIFSIGNALED(status) == true)
	{
		signum = WTERMSIG(status);
		if (signum == SIGQUIT)
			ft_printf(QUIT_CDUMP);
		if (signum == SIGQUIT || signum == SIGINT)
			ft_printf(NEWLINE_STR);
	}
}
