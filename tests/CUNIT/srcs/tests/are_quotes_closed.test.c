/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_quotes_closed.test.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 00:48:53 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/03 09:55:37 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

void	are_quotes_closed__test(void)
{
	const char	str1[] = "hello";
	const char	str2[] = "\"hello";
	const char	str3[] = "\"hello\"";

	CU_ASSERT_TRUE(are_quotes_closed(str1));
	CU_ASSERT_FALSE(are_quotes_closed(str2));
	CU_ASSERT_TRUE(are_quotes_closed(str3));
}
