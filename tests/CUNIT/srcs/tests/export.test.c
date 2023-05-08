/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:45:49 by mat               #+#    #+#             */
/*   Updated: 2023/05/05 14:47:25 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

static bool	tvar_cmp(t_var	*ref, t_var *out)
{
	if (ft_strcmp(ref->key, out->key) != 0)
		return (false);
	if (ref->value != NULL && out->value != NULL)
	{
		if (ft_strcmp(ref->value, out->value) != 0)
			return (false);
	}
	if ((ref->value == NULL && out->value != NULL) || (ref->value != NULL && out->value == NULL))
		return (false);
	return (true);
}

void	export_var_from_str__test(void)
{
	t_var	ref1 = {.key = "bonjour", .value = "54"};
	t_var	ref2 = {.key = "hola", .value = "como"};
	t_var	ref3 = {.key = "estoy", .value = "ytu?"};
	t_var	ref4 = {.key = "BLATA", .value = NULL};
	t_var		*out1;
	t_var		*out2;
	t_var		*out3;
	t_var		*out4;

	out1 = export_var_from_str("bonjour=54", true);
	out2 = export_var_from_str("hola=como", true);
	out3 = export_var_from_str("estoy=ytu?", true);
	out4 = export_var_from_str("BLATA", false);

	CU_ASSERT_TRUE(tvar_cmp(&ref1, out1));
	CU_ASSERT_TRUE(tvar_cmp(&ref2, out2));
	CU_ASSERT_TRUE(tvar_cmp(&ref3, out3));
	CU_ASSERT_TRUE(tvar_cmp(&ref4, out4));
	free_var(out1);
	free_var(out2);
	free_var(out3);
	free_var(out4);
	return ;
}


