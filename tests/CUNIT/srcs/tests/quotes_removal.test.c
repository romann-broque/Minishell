/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 21:27:03 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/06 21:32:11 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

static void	assert_free(const char *in, const char *exp)
{
	char *const	out = quotes_removal(in);

	CU_ASSERT_STRING_EQUAL(out, exp);
	free(out);
}

void	quotes_removal__test(void)
{
	const char	in_str1[] = "hello";
	const char	exp_str1[] = "hello";

	assert_free(in_str1, exp_str1);
}
