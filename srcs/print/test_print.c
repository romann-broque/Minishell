/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:26:48 by mat               #+#    #+#             */
/*   Updated: 2023/04/03 17:43:08 by mat              ###   ########.fr       */
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
