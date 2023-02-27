/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isdigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 05:03:26 by pcarella          #+#    #+#             */
/*   Updated: 2021/09/16 05:03:29 by pcarella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isdigit(char *str)
{
	int	idx;

	idx = -1;
	while (str[++idx])
		if (ft_isdigit(str[idx]) == 1)
			return (1);
	return (0);
}
