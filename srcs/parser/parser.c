/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:45:23 by mat               #+#    #+#             */
/*   Updated: 2023/05/30 10:49:47 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const t_tokparse	*init_pars_rules(void)
{
	static const t_tokparse	rules[] = {
	{.curr = T_LCHEVRON, .next = {T_G, T_QG, T_ASN, T_SEP, T_IVD}},
	{.curr = T_RCHEVRON, .next = {T_G, T_QG, T_ASN, T_SEP, T_IVD}},
	{.curr = T_DOUBLE_LCHEVRON, .next = {T_G, T_QG, T_ASN, T_SEP, T_IVD}},
	{.curr = T_DOUBLE_RCHEVRON, .next = {T_G, T_QG, T_ASN, T_SEP, T_IVD}},
	{.curr = T_PIPE, .next = {T_G, T_QG, T_LCH, T_RCH, T_DLCH, T_DRCH,
		T_ASN, T_SEP, T_IVD}},
	{.curr = T_OR, .next = {T_G, T_QG, T_LCH, T_RCH, T_DLCH,
		T_DRCH, T_ASN, T_SEP, T_IVD}},
	{.curr = T_AND, .next = {T_G, T_QG, T_LCH, T_RCH, T_DLCH,
		T_DRCH, T_ASN, T_SEP, T_IVD}},
	{.curr = T_SEPARATOR, .next = {T_G, T_QG, T_LCH, T_RCH, T_DLCH,
		T_DRCH, T_ASN, T_P, T_O, T_A, T_SEP, T_ED, T_IVD}},
	{.curr = T_ASSIGN, .next = {T_G, T_QG, T_LCH, T_RCH, T_DLCH,
		T_DRCH, T_ASN, T_P, T_O, T_A, T_SEP, T_ED, T_IVD}},
	{.curr = T_GENERIC, .next = {T_G, T_QG, T_LCH, T_RCH, T_DLCH,
		T_DRCH, T_ASN, T_P, T_O, T_A, T_SEP, T_ED, T_IVD}},
	{.curr = T_QGENERIC, .next = {T_G, T_QG, T_LCH, T_RCH, T_DLCH,
		T_DRCH, T_ASN, T_P, T_O, T_A, T_SEP, T_ED, T_IVD}},
	{.curr = T_START, .next = {T_G, T_QG, T_LCH,
		T_RCH, T_DLCH, T_DRCH, T_ASN, T_SEP, T_ED, T_IVD}}
	};

	return (rules);
}

static bool	is_valid_token(
	const t_tokparse *rules,
	t_toktype curr_type,
	t_token *next_tok
	)
{
	t_toktype	tok;
	size_t		index;

	index = 0;
	tok = (t_toktype)(rules[curr_type].next[index]);
	while (tok != T_INVALID
		&& tok != get_type_from_tok(next_tok))
	{
		index++;
		tok = (t_toktype)(rules[curr_type].next[index]);
	}
	return (tok != T_INVALID);
}

static void	skip_sep(t_list **tokens)
{
	t_toktype	type;

	type = get_type_from_tok((*tokens)->next->content);
	while (type == T_SEPARATOR)
	{
		*tokens = (*tokens)->next;
		type = get_type_from_tok((*tokens)->next->content);
	}
}

static bool	is_valid_parsing(t_list **tokens, const t_tokparse *rules)
{
	const t_toktype	type = get_type_from_tok((*tokens)->content);

	if (type == T_START || type == T_PIPE)
		skip_sep(tokens);
	return (type != T_END
		&& is_valid_token(rules, type, (*tokens)->next->content) == true);
}

bool	parser(t_list *tokens)
{
	const t_tokparse	*rules = init_pars_rules();

	while (tokens != NULL && is_valid_parsing(&tokens, rules) == true)
		tokens = tokens->next;
	if (get_type_from_tok(tokens->content) != T_END)
		print_pars_error(tokens->next->content);
	return (tokens == NULL || get_type_from_tok(tokens->content) == T_END);
}
