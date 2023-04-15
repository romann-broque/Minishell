/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:43:47 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/14 15:11:13 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(const char *format, ...)
{
	va_list	arg;

	va_start(arg, format);
	ft_dprintf(STDERR_FILENO, format, arg);
	va_end(arg);
}
