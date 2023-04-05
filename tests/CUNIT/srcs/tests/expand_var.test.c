/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:47:05 by mat               #+#    #+#             */
/*   Updated: 2023/04/05 15:03:26 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

void	ASSERT_AND_FREE(char *str1, const char *str2)
{
	CU_ASSERT_STRING_EQUAL(str1, str2);
	free(str1);
}

void	expand_var__test(void)
{
	const char	str_in_t1[] = "$single";
	const char	str_ref_t1[] = "var1";
	const char	str_in_t2[] = "$multiple";
	const char	str_ref_t2[] = "var2";
	const char	str_in_t3[] = "$single bonjour $single";
	const char	str_ref_t3[] = "var1 bonjour var1";
	const char	str_in_t4[] = "$single $single";
	const char	str_ref_t4[] = "var1 var1";
	const char	str_in_t5[] = "$single $multiple";
	const char	str_ref_t5[] = "var1 var2";
	const char	str_in_t6[] = "bonjour $multiple";
	const char	str_ref_t6[] = "bonjour var2";
	const char	str_in_t7[] = "bonjour $single bonjour2";
	const char	str_ref_t7[] = "bonjour var1 bonjour2";
	const char	str_in_t8[] = "bonjour $multiple bonjour2";
	const char	str_ref_t8[] = "bonjour var2 bonjour2";
	const char	str_in_t9[] = "bonjour $single bonjour2 $multiple";
	const char	str_ref_t9[] = "bonjour var1 bonjour2 var2";
	const char	str_in_t10[] = "$$";
	const char	str_ref_t10[] = "";
	const char	str_in_t11[] = "$1bla";
	const char	str_ref_t11[] = "bla";
	const char	str_in_t12[] = "$?bla";
	const char	str_ref_t12[] = "LAST_RET_VALbla";
	const char	str_in_t13[] = "$";
	const char	str_ref_t13[] = "$";
	const char	str_in_t14[] = "$$   $";
	const char	str_ref_t14[] = "   $";
	const char	str_in_t15[] = "$$$";
	const char	str_ref_t15[] = "$";
	const char	str_in_t16[] = "$?";
	const char	str_ref_t16[] = "LAST_RET_VAL";
	const char	str_in_t17[] = "$0";
	const char	str_ref_t17[] = "minishell";
	const char	str_in_t18[] = "$single$single";
	const char	str_ref_t18[] = "var1var1";
	const char	str_in_t19[] = "$    $";
	const char	str_ref_t19[] = "$    $";

	ASSERT_AND_FREE(expand_var(str_in_t1), str_ref_t1);
	ASSERT_AND_FREE(expand_var(str_in_t2), str_ref_t2);
	ASSERT_AND_FREE(expand_var(str_in_t3), str_ref_t3);
	ASSERT_AND_FREE(expand_var(str_in_t4), str_ref_t4);
	ASSERT_AND_FREE(expand_var(str_in_t5), str_ref_t5);
	ASSERT_AND_FREE(expand_var(str_in_t6), str_ref_t6);
	ASSERT_AND_FREE(expand_var(str_in_t7), str_ref_t7);
	ASSERT_AND_FREE(expand_var(str_in_t8), str_ref_t8);
	ASSERT_AND_FREE(expand_var(str_in_t9), str_ref_t9);
	ASSERT_AND_FREE(expand_var(str_in_t10), str_ref_t10);
	ASSERT_AND_FREE(expand_var(str_in_t11), str_ref_t11);
	ASSERT_AND_FREE(expand_var(str_in_t12), str_ref_t12);
	ASSERT_AND_FREE(expand_var(str_in_t13), str_ref_t13);
	ASSERT_AND_FREE(expand_var(str_in_t14), str_ref_t14);
	ASSERT_AND_FREE(expand_var(str_in_t15), str_ref_t15);
	ASSERT_AND_FREE(expand_var(str_in_t16), str_ref_t16);
	ASSERT_AND_FREE(expand_var(str_in_t17), str_ref_t17);
	ASSERT_AND_FREE(expand_var(str_in_t18), str_ref_t18);
	ASSERT_AND_FREE(expand_var(str_in_t19), str_ref_t19);
}
