/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:54:40 by mat               #+#    #+#             */
/*   Updated: 2023/03/23 10:23:33 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    handle_sigint(int signal)
{
    (void)signal;
    //write(STDIN_FILENO, "\n", 1);
    readline(PROMPT);
    //get_command();
}

void    set_catcher(void)
{
    signal(SIGINT, handle_sigint);
}