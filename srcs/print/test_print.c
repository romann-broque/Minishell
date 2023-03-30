/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:26:48 by mat               #+#    #+#             */
/*   Updated: 2023/03/30 10:48:38 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command(char **const token_array)
{
	size_t	i;

	i = 0;
	while (token_array[i] != NULL)
	{
		printf("Element %zu : [%s]\n", i + 1, token_array[i]);
		i++;
	}
}
