/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:43:47 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/24 23:41:22 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(const char *format, ...)
{
	va_list	arg;

	va_start(arg, format);
	ft_vdprintf(STDERR_FILENO, format, arg);
	va_end(arg);
}
