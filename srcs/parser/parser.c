/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:45:23 by mat               #+#    #+#             */
/*   Updated: 2023/04/06 15:27:13 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const t_tokparse	*init_pars_rules(void)
{
	static const t_tokparse	rules[] = {
	{.curr = T_LCHEVRON, .next = {T_GENERIC, T_INVALID}},
	{.curr = T_RCHEVRON, .next = {T_GENERIC, T_INVALID}},
	{.curr = T_DOUBLE_LCHEVRON, .next = {T_GENERIC, T_INVALID}},
	{.curr = T_DOUBLE_RCHEVRON, .next = {T_GENERIC, T_INVALID}},
	{.curr = T_PIPE, .next = {T_GENERIC, T_INVALID}},
	{.curr = T_OR, .next = {T_GENERIC, T_INVALID}},
	{.curr = T_AND, .next = {T_GENERIC, T_INVALID}},
	{.curr = T_ASSIGN, .next = {T_GENERIC, T_INVALID}},
	{.curr = T_GENERIC, .next = {
		T_GENERIC, T_LCHEVRON, T_RCHEVRON, T_DOUBLE_LCHEVRON,
		T_DOUBLE_RCHEVRON, T_ASSIGN, T_PIPE, T_END, T_INVALID}},
	{.curr = T_START, .next = {
		T_GENERIC, T_LCHEVRON, T_RCHEVRON, T_DOUBLE_LCHEVRON,
		T_DOUBLE_RCHEVRON, T_ASSIGN, T_END, T_INVALID}}
	};

	return (rules);
}

static t_toktype	get_type_from_tok(t_token *tok)
{
	return (tok->type);
}

bool	parser(t_list *tokens)
{
	const t_tokparse	*rules = init_pars_rules();
	t_toktype			tmp_type;
	size_t				index_next_tok;
	bool				is_valid;

	if (tokens->next->content == NULL)
		return (true);
	while (tokens != NULL && get_type_from_tok(tokens->content) != T_END)
	{
		index_next_tok = 0;
		is_valid = false;
		tmp_type = get_type_from_tok(tokens->content);
		while (rules[tmp_type].next[index_next_tok] != T_INVALID)
		{
			if (rules[tmp_type].next[index_next_tok]
				== get_type_from_tok(tokens->next->content))
				is_valid = true;
			index_next_tok++;
		}
		if (is_valid == false)
			break ;
		tokens = tokens->next;
	}
	return (is_valid);
}
