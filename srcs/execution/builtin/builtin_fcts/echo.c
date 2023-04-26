/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:28:37 by mdorr             #+#    #+#             */
/*   Updated: 2023/04/26 16:23:08 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n_option(char *first_argument)
{
	return (first_argument != NULL && streq("-n", first_argument) == true);
}

void	echo_builtin(t_command *cmd_data)
{
	bool	n_option;
	char	**str_ptr;
	size_t	i;

	str_ptr = cmd_data->command + 1;
	n_option = is_n_option(str_ptr[0]);
	if (n_option == true)
		str_ptr++;
	i = 0;
	while (str_ptr[i] != NULL)
	{
		printf("%s", str_ptr[i]);
		if (str_ptr[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_option == false)
		printf("\n");
}
