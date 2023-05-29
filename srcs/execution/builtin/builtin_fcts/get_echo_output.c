/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:04:29 by rbroque           #+#    #+#             */
/*   Updated: 2023/05/29 16:05:02 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_echo_output_size(char **strs, const bool n_option)
{
	const size_t	strs_size = get_size_strs(strs);
	size_t			i;
	size_t			output_size;

	output_size = (n_option == false);
	i = 0;
	while (i < strs_size)
	{
		output_size += ft_strlen(*strs);
		++i;
	}
	if (strs_size > 0)
		output_size += (strs_size - 1);
	return (output_size);
}

static void	fill_echo_output(char *output, char **strs, const bool n_option)
{
	size_t	output_index;

	output_index = 0;
	while (*strs != NULL)
	{
		ft_strcpy(output + output_index, *strs);
		output_index += ft_strlen(*strs);
		if (*(strs + 1) != NULL)
		{
			ft_strcpy(output + output_index, SPACE_STR);
			++output_index;
		}
		++strs;
	}
	if (n_option == false)
	{
		ft_strcpy(output + output_index, NEWLINE_STR);
		++output_index;
	}
	output[output_index] = '\0';
}

char	*get_echo_output(char **strs, const bool n_option)
{
	const size_t	output_size = get_echo_output_size(strs, n_option);
	char			*output;

	output = (char *)malloc((output_size + 1) * sizeof(char));
	if (output != NULL)
		fill_echo_output(output, strs, n_option);
	return (output);
}
