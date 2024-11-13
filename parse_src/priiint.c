/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priiint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:22:54 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/13 17:25:09 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	priiint(t_lst *lst)
{
	int	p;

	while (lst)
	{
		printf("cmd : %s\n", lst->token->command);
		p = 0;
		while (lst->token->arg[p])
		{
			printf("c.arg[%d] : %s\n", p, lst->token->arg[p]);
			p++;
		}
		t_opr *tmp2 = lst->token->file;
		while (tmp2)
		{
			printf("file name : %s\n", tmp2->file_name);
			printf("opr       : %s\n", tmp2->opr);
			tmp2 = tmp2->next;
		}
		t_herdoc *tmp1 = lst->token->herdoc;
		while(tmp1)
		{
			printf("herdoc : %s\n", tmp1->herdoc);
			printf("del       : %s\n", tmp1->del);
			tmp1 = tmp1->next;
		}
		lst = lst->next;
	}
}