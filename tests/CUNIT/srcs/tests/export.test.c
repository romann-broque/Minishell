/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:45:49 by mat               #+#    #+#             */
/*   Updated: 2023/05/05 11:08:50 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

static bool	tvar_cmp(t_var	*ref, t_var *out)
{
	if (ft_strcmp(ref->key, out->key) != 0)
		return (false);
	if (ref->value != NULL)
	{
		if (ft_strcmp(ref->value, out->value) != 0)
			return (false);
	}
	return (true);
}

static t_var	*export_var_from_str(char *str, bool is_only_key)
{
	const size_t	eq_index = abs_index(str, EQUAL_SIGN);
	char *const		name = ft_strndup(str, eq_index);
	char			*value;
	t_var			*new_var;

	value = NULL;
	if (is_only_key == false)
	{
		value = str + eq_index + 1;
		new_var = init_var(name, value, ENV_MASK);
	}
	else
		new_var = init_var(name, value, EXPORT_MASK);
	free(name);
	return (new_var);
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

	out1 = export_var_from_str("bonjour=54", false);
	out2 = export_var_from_str("hola=como", false);
	out3 = export_var_from_str("estoy=ytu?", false);
	out4 = export_var_from_str("BLATA", true);

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


