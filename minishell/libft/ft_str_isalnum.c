/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isalnum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 20:20:54 by pcarella          #+#    #+#             */
/*   Updated: 2021/09/08 20:22:48 by pcarella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isalnum(char *str)
{
	int	idx;

	idx = -1;
	while (str[++idx])
		if (ft_isalnum(str[idx]) == 1)
			return (1);
	return (0);
}
