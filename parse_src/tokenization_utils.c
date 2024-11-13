/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:23:02 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/13 18:47:52 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	check_if_pair(char *cmd, int *i, bool *pair)
{
	(*i)++;
	while (cmd[*i] && cmd[*i] == '$')
	{
		*pair = !*pair;
		(*i)++;
	}
	return (*pair);
}

static void	handle_dollar_sign(t_buffer string, int *i, t_env *e, int *index)
{
	bool		in_the_first;
	bool		pair;
	char		var_name[256];
	char		*value;
	int			j;

	in_the_first = true;
	pair = true;
	check_if_pair(string.cmd, i, &pair);
	if (pair)
	{
		extract_var_name(string.cmd, i, var_name, &in_the_first);
		value = replace_env(e, var_name);
		printf("value : %s\n", value);
		if (value)
		{
			j = 0;
			// printf("%lu\n", strlen(value));
			while (value && value[j])
				string.buffer[(*index)++] = value[j++];
			// exit (0);
			free(value);
		}
	}
}

char	*__env(char *cmd, t_env *e)
{
	t_buffer	string;
	int			buffer_index;
	int			i;
	bool		in_single_quotes;
	bool		in_quotes;

	in_single_quotes = false;
	in_quotes = false;
	i = 0;
	buffer_index = 0;
	string.cmd = parse_strdup(cmd);
	string.buffer = __calloc(get_env_size(cmd, e) + 10, 1);
	printf("gggettt : %d\n", get_env_size(cmd, e));
	while (cmd[i])
	{
		quotes_status(cmd, &i, &in_single_quotes, &in_quotes);
		if (cmd[i + 1] && cmd[i] == '$'
			&& cmd[i + 1] != ' ' && !in_single_quotes && cmd[i + 1] != '\"')
			handle_dollar_sign(string, &i, e, &buffer_index);
		else
			string.buffer[buffer_index++] = cmd[i++];
		string.buffer[buffer_index] = '\0';
	}
	free(string.cmd);
	return (remove_q(string.buffer));
}

void	quotes_status(char *cmd, int *i, bool *in_sq, bool *in_quotes)
{
	if (!cmd)
		return ;
	if (!*in_quotes && cmd[*i] == '\'')
		*in_sq = !*in_sq;
	else if (!*in_sq && cmd[*i] == '\"')
		*in_quotes = !*in_quotes;
}

int	__lstsize(t_env *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
