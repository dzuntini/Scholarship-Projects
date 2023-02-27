/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 10:32:51 by dzuntini          #+#    #+#             */
/*   Updated: 2022/04/25 11:32:27 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	replace_letter(t_cub *cub, char torep, char with)
{
	int	i;
	int	j;

	i = -1;
	while (cub->data.parsed[++i])
	{
		j = -1;
		while (cub->data.parsed[i][++j])
		{
			if (cub->data.parsed[i][j] == torep)
				cub->data.parsed[i][j] = with;
		}
	}
}

int	check_letter_line(char *str, char *base)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (check_letter(str[i], base) == false)
			return (false);
	}
	return (true);
}

int	check_letter(char c, char *base)
{
	int	i;

	i = -1;
	while (base[++i])
	{
		if (c == base[i])
			return (true);
	}
	return (false);
}

int	ft_atoi2(const char *str)
{
	long long int	total;
	int				n;
	int				i;

	total = 0;
	n = 0;
	i = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
		n++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
		total = total * 10 + (str[i++] - '0');
	if (n == 1)
		total = -total;
	if (total > 255 || total < 0)
		return (-1);
	return (total);
}

void	freestuff(char c, t_cub *cub)
{
	if (c == 't')
	{
		ft_freetab(cub->data.text_tab);
		cub->fflags.text_tab = false;
	}
	if (c == 's')
	{
		ft_freetab(cub->data.sf);
		cub->fflags.sf = false;
	}
}
