/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 06:02:39 by dzuntini          #+#    #+#             */
/*   Updated: 2022/04/17 14:00:56 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		ft_putchar_fd(s[i++], fd);
}

void	ft_puterr(char *str)
{
	ft_putstr_fd("Error : \n", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
}

void	ft_puterrexit(char *str, int code)
{
	ft_puterr(str);
	exit(code);
}
