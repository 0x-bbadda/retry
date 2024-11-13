/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:04:29 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/13 17:58:15 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*remove_q(char *s_command)
{
	bool	in_single_quotes;
	bool	in_quotes;
	char	*buffer;
	int		buffer_index;
	int		i;

	in_single_quotes = false;
	in_quotes = false;
	buffer = malloc(parse_strlen(s_command) + 1);
	i = -1;
	buffer_index = 0;
	while (s_command[++i])
	{
		if (!in_quotes && s_command[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && s_command[i] == '\"')
			in_quotes = !in_quotes;
		else
			buffer[buffer_index++] = s_command[i];
	}
	buffer[buffer_index] = '\0';
	free(s_command);
	return (buffer);
}

char	*add_token(char *buffer, int *buffer_index)
{
	char	*s;

	s = NULL;
	if (*buffer_index > 0)
	{
		buffer[*buffer_index] = '\0';
		s = parse_strdup(buffer);
		*buffer_index = 0;
	}
	return (s);
}

int	get_lenth(char *cmd, int x)
{
	int	lenth;

	lenth = 0;
	while (cmd[x] && (ft_isalnum(cmd[x]) || cmd[x] == '_' || cmd[x] == '?'))
	{
		x++;
		lenth++;
	}
	return (lenth);
}

char	*init_and_alloc(char *cmd, int *i)
{
	char	*var_name;
	int		x;
	int		j;

	j = 0;
	x = *i;
	var_name = (char *)malloc(get_lenth(cmd, x) + 1);
	while (cmd[*i] && (ft_isalnum(cmd[*i]) || cmd[*i] == '_' || cmd[*i] == '?'))
	{
		var_name[j] = cmd[*i];
		(j)++;
		(*i)++;
	}
	var_name[j] = '\0';
	return (var_name);
}

int	get_env_size(char *cmd, t_env *e)
{
	t_index		index;
	int			size;
	char		*var_name;
	char		*tmp;

	size = 0;
	index.i = -1;
	while (cmd[++index.i])
	{
		if (cmd[index.i] == '$' && (cmd[index.i + 1] || cmd [index.i] == ' '))
		{
			index.i++;
			var_name = init_and_alloc(cmd, &index.i);
			tmp = replace_env(e, (var_name));
			free(var_name);
			size += parse_strlen(tmp);
			free(tmp);
			index.i--;
		}
		else
			size++;
	}
	return (size);
}
