/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_var_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:51:30 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/29 18:30:05 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_var_len(char *line, size_t	index)
{
	size_t	len;

	len = 0;
	index++;
	while (ft_isalnum(line[index]) == 1 || line[index] == '_')
	{
		index++;
		len++;
	}
	return (len);
}

char	*get_var_name(char *line, size_t index)
{
	char	*var;
	size_t	len;
	size_t	i;

	

	len = get_var_len(line, index);
	var = malloc(sizeof(char) * len + 1);
	while (ft_isalnum(line[index]) == 1 || line[index] == '_')
	{
		var
	}

}

static int	get_new_line_len(char *line)
{
	size_t	len;
	size_t	i;
	char	*var_name;
	char	*var_value;

	while(line[i] =! '\0')
	{
		while (line[i++] != '$')
			len++;
		if (line[i] == '\0')
			return (len);
		var_name = get_var_name(line, i);
		len -= ft_strlen(var_name);
		var_value = getenv(var_name);
		len += ft_strlen(var_value);
	}
}

char	*create_var_line(char *line)
{
	char	*new_line;
	size_t	len;

	len = get_new_line_len(line);


}