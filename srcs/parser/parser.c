/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:45:23 by mat               #+#    #+#             */
/*   Updated: 2023/04/20 14:13:24 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const t_tokparse	*init_pars_rules(void)
{
	static const t_tokparse	rules[] = {
	{.curr = T_LCHEVRON, .next = {T_GENERIC, T_ASSIGN, T_INVALID}},
	{.curr = T_RCHEVRON, .next = {T_GENERIC, T_ASSIGN, T_INVALID}},
	{.curr = T_DOUBLE_LCHEVRON, .next = {T_GENERIC, T_ASSIGN, T_INVALID}},
	{.curr = T_DOUBLE_RCHEVRON, .next = {T_GENERIC, T_ASSIGN, T_INVALID}},
	{.curr = T_PIPE, .next = {
		T_GENERIC, T_LCHEVRON, T_RCHEVRON, T_DOUBLE_LCHEVRON,
		T_DOUBLE_RCHEVRON, T_ASSIGN, T_INVALID}},
	{.curr = T_OR, .next = {
		T_GENERIC, T_LCHEVRON, T_RCHEVRON, T_DOUBLE_LCHEVRON,
		T_DOUBLE_RCHEVRON, T_ASSIGN, T_INVALID}},
	{.curr = T_AND, .next = {
		T_GENERIC, T_LCHEVRON, T_RCHEVRON, T_DOUBLE_LCHEVRON,
		T_DOUBLE_RCHEVRON, T_ASSIGN, T_INVALID}},
	{.curr = T_ASSIGN, .next = {
		T_GENERIC, T_LCHEVRON, T_RCHEVRON, T_DOUBLE_LCHEVRON,
		T_DOUBLE_RCHEVRON, T_ASSIGN, T_PIPE, T_OR, T_AND, T_END, T_INVALID}},
	{.curr = T_GENERIC, .next = {
		T_GENERIC, T_LCHEVRON, T_RCHEVRON, T_DOUBLE_LCHEVRON,
		T_DOUBLE_RCHEVRON, T_ASSIGN, T_PIPE, T_OR, T_AND, T_END, T_INVALID}},
	{.curr = T_START, .next = {T_GENERIC, T_LCHEVRON, T_RCHEVRON,
		T_DOUBLE_LCHEVRON, T_DOUBLE_RCHEVRON, T_ASSIGN, T_END, T_INVALID}}
	};

	return (rules);
}

static bool	is_valid_token(
	const t_tokparse *rules,
	t_toktype curr_type,
	t_token *next_tok
	)
{
	size_t			index;

	index = 0;
	while (rules[curr_type].next[index] != T_INVALID
		&& (rules[curr_type].next[index] != get_type_from_tok(next_tok)))
		index++;
	return (rules[curr_type].next[index] != T_INVALID);
}

static bool	is_valid_parsing(t_list *tokens, const t_tokparse *rules)
{
	return (tokens != NULL && get_type_from_tok(tokens->content) != T_END
		&& is_valid_token(rules, get_type_from_tok(tokens->content),
			tokens->next->content) == true);
}

bool	parser(t_list *tokens)
{
	const t_tokparse	*rules = init_pars_rules();

	while (is_valid_parsing(tokens, rules) == true)
		tokens = tokens->next;
	if (get_type_from_tok(tokens->content) != T_END)
		print_pars_error(tokens->next->content);
	return (tokens == NULL || get_type_from_tok(tokens->content) == T_END);
}
