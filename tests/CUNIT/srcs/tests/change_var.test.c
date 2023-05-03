/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var.test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:34:17 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/03 16:10:47 by rbroque          ###   ########.fr       */
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

	update_var(var_name1, var_value1, ENV_MASK);
	CU_ASSERT_STRING_EQUAL(ft_getenv(var_name1), var_value1);

	update_var(var_name2, var_value2, ENV_MASK);
	CU_ASSERT_STRING_EQUAL(ft_getenv(var_name2), var_value2);

	update_var(var_name3, var_value3, ENV_MASK);
	CU_ASSERT_STRING_EQUAL(ft_getenv(var_name3), var_value3);

	update_var(var_name4, var_value4, ENV_MASK);
	CU_ASSERT_STRING_EQUAL(ft_getenv(var_name4), var_value4);

	update_var(var_name5, var_value5, ENV_MASK);
	CU_ASSERT_STRING_EQUAL(ft_getenv(var_name5), var_value5);
}
