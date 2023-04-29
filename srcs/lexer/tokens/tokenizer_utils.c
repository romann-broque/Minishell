/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:53:49 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/29 17:53:58 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_assign(const char *word)
{
	return (streq(word, ASSIGN_EQ) == true);
}

bool	is_qword(const char *word)
{
	return (word[0] == SINGLE_QUOTE || word[0] == DOUBLE_QUOTE);
}
