/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:46:43 by rphuyal           #+#    #+#             */
/*   Updated: 2022/12/29 19:27:18 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end_node;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	end_node = ft_lstlast(*lst);
	end_node -> next = new;
}
