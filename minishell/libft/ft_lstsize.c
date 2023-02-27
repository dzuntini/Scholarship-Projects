/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:44:47 by dzuntini          #+#    #+#             */
/*   Updated: 2021/01/25 11:51:33 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	ret;

	ret = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		ret++;
		lst = lst->next;
	}
	return (ret);
}
