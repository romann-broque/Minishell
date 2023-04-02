/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_quotes_closed.test.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 00:48:53 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/03 00:53:47 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

void	are_quotes_closed__test(void)
{
	const char	str[] = "hello";

	CU_ASSERT_FATAL(are_quotes_closed(str) == true);
}
