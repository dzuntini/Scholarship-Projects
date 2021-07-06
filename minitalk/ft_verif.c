/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxxx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:51:28 by dzuntini          #+#    #+#             */
/*   Updated: 2021/06/29 13:08:36 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	ft_number(char *str)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (str[i] != '\0')
		t += ft_isdigit(str[i++]);
	return (t);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}
