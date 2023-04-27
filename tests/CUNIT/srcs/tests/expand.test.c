/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:47:05 by mat               #+#    #+#             */
/*   Updated: 2023/04/27 19:47:09 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

void	ASSERT_AND_FREE(char *str1, const char *str2)
{
	CU_ASSERT_STRING_EQUAL(str1, str2);
	free(str1);
}

void	expand__test(void)
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
	const char	str_in_t13[] = "$";
	const char	str_ref_t13[] = "$";
	const char	str_in_t14[] = "$$   $";
	const char	str_ref_t14[] = "   $";
	const char	str_in_t15[] = "$$$";
	const char	str_ref_t15[] = "$";
	const char	str_in_t17[] = "$0";
	const char	str_ref_t17[] = "minishell";
	const char	str_in_t18[] = "$single$single";
	const char	str_ref_t18[] = "var1var1";
	const char	str_in_t19[] = "$    $";
	const char	str_ref_t19[] = "$    $";
	const char	str_in_t20[] = "$lol";
	const char	str_ref_t20[] = "42";
	const char	str_in_t21[] = "\"$lol\"";
	const char	str_ref_t21[] = "42";
	const char	str_in_t22[] = "\'$lol\'";
	const char	str_ref_t22[] = "$lol";
	const char	str_in_t23[] = "\"'$lol'\"";
	const char	str_ref_t23[] = "'42'";
	const char	str_in_t24[] = "'\"$lol\"'";
	const char	str_ref_t24[] = "\"$lol\"";
	const char	str_in_t25[] = "'\"\"\"$lol\"\"\"'";
	const char	str_ref_t25[] = "\"\"\"$lol\"\"\"";
	const char	str_in_t26[] = "'$\"$$\"$$'";
	const char	str_ref_t26[] = "$\"$$\"$$";
	const char	str_in_t27[] = "'\"$\"$\"$$\"$$'";
	const char	str_ref_t27[] = "\"$\"$\"$$\"$$";
	const char	str_in_t28[] = "$'lol'";
	const char	str_ref_t28[] = "lol";
	const char	str_in_t29[] = "$\"lol\"";
	const char	str_ref_t29[] = "lol";
	const char	str_in_t30[] = "'$\"lol\"'";
	const char	str_ref_t30[] = "$\"lol\"";
	const char	str_in_t31[] = "\"ech\"o$wouah'lol'";
	const char	str_ref_t31[] = "echo'pouet pouet'lol";
	const char	str_in_t32[] = "\"$\"";
	const char	str_ref_t32[] = "";
	const char	str_in_t33[] = "$\"wouah$\"";
	const char	str_ref_t33[] = "wouah";
	const char	str_in_t34[] = "$\"$wouah$\"";
	const char	str_ref_t34[] = "'pouet pouet'";
	const char	str_in_t35[] = "$wtf";
	const char	str_ref_t35[] = "''";

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
	ASSERT_AND_FREE(expand_var(str_in_t13), str_ref_t13);
	ASSERT_AND_FREE(expand_var(str_in_t14), str_ref_t14);
	ASSERT_AND_FREE(expand_var(str_in_t15), str_ref_t15);
	ASSERT_AND_FREE(expand_var(str_in_t17), str_ref_t17);
	ASSERT_AND_FREE(expand_var(str_in_t18), str_ref_t18);
	ASSERT_AND_FREE(expand_var(str_in_t19), str_ref_t19);
	ASSERT_AND_FREE(expand_var(str_in_t20), str_ref_t20);
	ASSERT_AND_FREE(expand_var(str_in_t21), str_ref_t21);
	ASSERT_AND_FREE(expand_var(str_in_t22), str_ref_t22);
	ASSERT_AND_FREE(expand_var(str_in_t23), str_ref_t23);
	ASSERT_AND_FREE(expand_var(str_in_t24), str_ref_t24);
	ASSERT_AND_FREE(expand_var(str_in_t25), str_ref_t25);
	ASSERT_AND_FREE(expand_var(str_in_t26), str_ref_t26);
	ASSERT_AND_FREE(expand_var(str_in_t27), str_ref_t27);
	ASSERT_AND_FREE(expand_var(str_in_t28), str_ref_t28);
	ASSERT_AND_FREE(expand_var(str_in_t29), str_ref_t29);
	ASSERT_AND_FREE(expand_var(str_in_t30), str_ref_t30);
	ASSERT_AND_FREE(expand_var(str_in_t31), str_ref_t31);
	ASSERT_AND_FREE(expand_var(str_in_t32), str_ref_t32);
	ASSERT_AND_FREE(expand_var(str_in_t33), str_ref_t33);
	ASSERT_AND_FREE(expand_var(str_in_t34), str_ref_t34);
	ASSERT_AND_FREE(expand_var(str_in_t35), str_ref_t35);
}
