/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 21:27:03 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/07 11:16:48 by rbroque          ###   ########.fr       */
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
	const char	in_str2[] = "\"hello\"";
	const char	exp_str2[] = "hello";
	const char	in_str3[] = "\"hel\'lo\"";
	const char	exp_str3[] = "hel\'lo";
	const char	in_str4[] = "";
	const char	exp_str4[] = "";
	const char	in_str5[] = "\"\"";
	const char	exp_str5[] = "";
	const char	in_str6[] = "\"\'\"";
	const char	exp_str6[] = "\'";
	const char	in_str7[] = "a\"b\'c\"d";
	const char	exp_str7[] = "ab\'cd";
	const char	in_str8[] = "a\"\'b\'c\'\"d";
	const char	exp_str8[] = "a\'b\'c\'d";
	const char	in_str9[] = "\"\"ech\"o\" he\'l\'lo\'\'";
	const char	exp_str9[] = "echo hello";
	const char	in_str10[] = "\"\"ech\"o\" he\'l\'lo\'\'       ";
	const char	exp_str10[] = "echo hello       ";
	const char	in_str11[] = "\"\'\"\"\"ech\"o\" he\'l\'lo\'\'       ";
	const char	exp_str11[] = "\'echo hello       ";
	const char	in_str12[] = "\"\'\"\"\"ech\"o\" he\'l\'lo\'\'       b\'a\'t";
	const char	exp_str12[] = "\'echo hello       bat";
	const char	in_str13[] = "\"\'\"\"\"ech\"o\" he\'l\'lo\'\'  \'$lol\'     b\'a\'t";
	const char	exp_str13[] = "\'echo hello  $lol     bat";

	assert_free(in_str1, exp_str1);
	assert_free(in_str2, exp_str2);
	assert_free(in_str3, exp_str3);
	assert_free(in_str4, exp_str4);
	assert_free(in_str5, exp_str5);
	assert_free(in_str6, exp_str6);
	assert_free(in_str6, exp_str6);
	assert_free(in_str7, exp_str7);
	assert_free(in_str8, exp_str8);
	assert_free(in_str9, exp_str9);
	assert_free(in_str10, exp_str10);
	assert_free(in_str11, exp_str11);
	assert_free(in_str12, exp_str12);
	assert_free(in_str13, exp_str13);
}
