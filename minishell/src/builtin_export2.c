/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:29:21 by pcarella          #+#    #+#             */
/*   Updated: 2021/09/27 09:22:49 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **print)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(print[0], STDOUT_FILENO);
	if (print[1])
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(print[1], STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

char	**min_export(t_data *ms, char **min)
{
	int		idx;
	char	**cur;

	idx = 0;
	while (ft_strcmp(min[0], ms->tab_env[idx][0]) >= 0)
		idx++;
	cur = ms->tab_env[idx];
	while (ms->tab_env[++idx])
	{
		if (ft_strcmp(min[0], ms->tab_env[idx][0]) < 0
			&& ft_strcmp(cur[0], ms->tab_env[idx][0]) > 0)
			cur = ms->tab_env[idx];
	}
	print_export(cur);
	return (cur);
}

char	**split_export(char *param)
{
	char	**tmp;
	char	**split;

	tmp = NULL;
	if (join_export(NULL, param, 1) == 1)
		tmp = ft_split(param, '+');
	else
		tmp = ft_split(param, '=');
	split = malloc(sizeof(char *) * 3);
	split[0] = ft_strdup(tmp[0]);
	if (tmp[1] == 0)
		split[1] = 0;
	else
	{
		split[1] = ft_strdup(ft_strchr(param, '=') + 1);
		split[2] = 0;
	}
	free_tabstr(tmp);
	return (split);
}

int	sort_export(t_data *ms)
{
	int		idx[2];
	char	**min;

	idx[0] = 0;
	min = ms->tab_env[idx[0]];
	while (ms->tab_env[++idx[0]])
	{
		if (ft_strcmp(min[0], ms->tab_env[idx[0]][0]) > 0)
			min = ms->tab_env[idx[0]];
	}
	print_export(min);
	idx[1] = -1;
	while (++idx[1] < ms->tab_len - 1)
		min = min_export(ms, min);
	return (0);
}

int	error_export(char *param)
{
	if (param[0] == '-')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putchar_fd(param[0], 2);
		ft_putchar_fd(param[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
	else
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(param, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	return (1);
}
