/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:21:30 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/21 14:07:44 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

extern t_global	g_global;

void	ft_getenv__test(void)
{
	const char	*var_name1 = "lol";
	const char	*var_value1 = "42";
	const char	*var_name2 = "UNKNOWN";
	const char	*var_value2 = NULL;
	const char	*var_name3 = "strange";
	const char	*var_value3 = "=2=1==42";
	const char	*var_name4 = "empty";
	const char	*var_value4 = "";
	const char	*var_name5 = "";
	const char	*var_value5 = NULL;
	const char	*var_name6 = "empty1";
	const char	*var_value6 = "1";

	CU_ASSERT_STRING_EQUAL(ft_getenv(var_name1), var_value1);
	CU_ASSERT_PTR_EQUAL(ft_getenv(var_name2), var_value2);
	CU_ASSERT_STRING_EQUAL(ft_getenv(var_name3), var_value3);
	CU_ASSERT_STRING_EQUAL(ft_getenv(var_name4), var_value4);
	CU_ASSERT_PTR_EQUAL(ft_getenv(var_name5), var_value5);
	CU_ASSERT_STRING_EQUAL(ft_getenv(var_name6), var_value6);
}
