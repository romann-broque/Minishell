/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_pwd.test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 01:02:12 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/25 11:37:40 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

void	clean_pwd__test(void)
{
	const char	*str_in_to1 = "..";
	const char	*str_in_curr1 = "/home/screw";
	const char	*str_exp1 = "/home";
	const char	*str_in_to2 = "..";
	const char	*str_in_curr2 = "/";
	const char	*str_exp2 = "/";
	const char	*str_in_to3 = "/../../..";
	const char	*str_in_curr3 = "/";
	const char	*str_exp3 = "/";
	const char	*str_in_to4 = "../../../../";
	const char	*str_in_curr4 = "/";
	const char	*str_exp4 = "/";
	char		*tmp;

	tmp = clean_pwd(str_in_to1, str_in_curr1);
	CU_ASSERT_STRING_EQUAL(tmp, str_exp1);
	free(tmp);
	tmp = clean_pwd(str_in_to2, str_in_curr2);
	CU_ASSERT_STRING_EQUAL(tmp, str_exp2);
	free(tmp);
	tmp = clean_pwd(str_in_to3, str_in_curr3);
	CU_ASSERT_STRING_EQUAL(tmp, str_exp3);
	free(tmp);
	tmp = clean_pwd(str_in_to4, str_in_curr4);
	CU_ASSERT_STRING_EQUAL(tmp, str_exp4);
	free(tmp);
}
