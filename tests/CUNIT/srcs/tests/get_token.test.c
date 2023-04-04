/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:35:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/04/04 10:37:30 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cunit.test.h"

#define MAX_TOKEN_LEN 20

void	get_token__test(void)
{
	const char	*str = "hello my friend";
	const char	token1[][MAX_TOKEN_LEN + 1] = {
		"hello",
		"my",
		"friend"
	}
}
