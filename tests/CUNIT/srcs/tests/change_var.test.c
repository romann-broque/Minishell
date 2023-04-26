/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var.test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:34:17 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/21 19:02:35 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

extern t_global	g_global;

void	change_var__test(void)
{
	const char	*var_name1 = "lol";
	const char	*var_value1 = "41";
	const char	*var_name2 = "new";
	const char	*var_value2 = "insane";
	const char	*var_name3 = "empty";
	const char	*var_value3 = "insane";
	const char	*var_name4 = "empty1";
	const char	*var_value4 = "pouet";
	const char	*var_name5 = "empty1";
	const char	*var_value5 = "pouetpouet";

	change_var(var_name1, var_value1);
	CU_ASSERT_STRING_EQUAL(ft_getenv(var_name1), var_value1);

	change_var(var_name2, var_value2);
	CU_ASSERT_STRING_EQUAL(ft_getenv(var_name2), var_value2);

	change_var(var_name3, var_value3);
	CU_ASSERT_STRING_EQUAL(ft_getenv(var_name3), var_value3);

	change_var(var_name4, var_value4);
	CU_ASSERT_STRING_EQUAL(ft_getenv(var_name4), var_value4);

	change_var(var_name5, var_value5);
	CU_ASSERT_STRING_EQUAL(ft_getenv(var_name5), var_value5);
}
