/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_quotes_closed.test.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 00:48:53 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/14 10:38:06 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

void	are_quotes_closed__test(void)
{
	const char	str_t1[] = "hello";
	const char	str_t2[] = "\"hello\"";
	const char	str_t3[] = "ech\"o\"";
	const char	str_t4[] = "\"\"";
	const char	str_t5[] = "ec\"ho\" he\"l\"lo";
	const char	str_t6[] = "ec\"ho\" he\'\"\'l\"lo\"";
	const char	str_t7[] = "\"\'\'          \'\'   \"\'\'\'\'\"\"";
	const char	str_t8[] = "   heeey les   \"\"  \'  \'\'\'       amis";
	const char	str_t9[] = "             ";
	const char	str_t10[] = "echo \"\"\" \"";
	const char	str_t11[] = "he\"l\"   \"o\""; 
	const char	str_t12[] = "\"hel \"   \" lo\"";
	const char	str_t13[] = "\"hel \"   \" lo\"      ";
	const char	str_t14[] = "hel\" \' \'\"lo";
	const char	str_t15[] = "\"\'\" \"\"";
	const char	str_t16[] = "\"\'\'\'\" \"\" \"\'\'\'\'\"";
	const char	str_t17[] = "po\"u\'e\'t\" o\'k\'\'\' t\"\"\"rop r\'igo\'lo ce \"test\"\"    ";

	const char	str_f1[] = "\"hello";
	const char	str_f2[] = "\"hello\'";
	const char	str_f3[] = "\"\'\'          \'\'   \"\'\'\'\"";
	const char	str_f4[] = "\"\'\"\'  \"        \'\'   \"\'\'\'\"";
	const char	str_f5[] = "\"\'\"\'  \'\'hello        \'\'   \"\'\'\'\"";
	const char	str_f6[] = "\'\"\'\"";

	CU_ASSERT_TRUE(are_quotes_closed(str_t1));
	CU_ASSERT_TRUE(are_quotes_closed(str_t2));
	CU_ASSERT_TRUE(are_quotes_closed(str_t3));
	CU_ASSERT_TRUE(are_quotes_closed(str_t4));
	CU_ASSERT_TRUE(are_quotes_closed(str_t5));
	CU_ASSERT_TRUE(are_quotes_closed(str_t6));
	CU_ASSERT_TRUE(are_quotes_closed(str_t7));
	CU_ASSERT_TRUE(are_quotes_closed(str_t8));
	CU_ASSERT_TRUE(are_quotes_closed(str_t9));
	CU_ASSERT_TRUE(are_quotes_closed(str_t10));
	CU_ASSERT_TRUE(are_quotes_closed(str_t11));
	CU_ASSERT_TRUE(are_quotes_closed(str_t12));
	CU_ASSERT_TRUE(are_quotes_closed(str_t13));
	CU_ASSERT_TRUE(are_quotes_closed(str_t14));
	CU_ASSERT_TRUE(are_quotes_closed(str_t15));
	CU_ASSERT_TRUE(are_quotes_closed(str_t16));
	CU_ASSERT_TRUE(are_quotes_closed(str_t17));

	CU_ASSERT_FALSE(are_quotes_closed(str_f1));
	CU_ASSERT_FALSE(are_quotes_closed(str_f2));
	CU_ASSERT_FALSE(are_quotes_closed(str_f3));
	CU_ASSERT_FALSE(are_quotes_closed(str_f4));
	CU_ASSERT_FALSE(are_quotes_closed(str_f5));
	CU_ASSERT_FALSE(are_quotes_closed(str_f6));
}
