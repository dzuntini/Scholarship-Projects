/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 04:45:41 by pcarella          #+#    #+#             */
/*   Updated: 2021/09/27 17:49:24 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char *key, char *val)
{
	char	**ret;

	ret = malloc(2 * sizeof(char *));
	ret[0] = ft_strdup(key);
	if (val)
		ret[1] = ft_strdup(val);
	else
		ret[1] = 0;
	return (ret);
}

void	get_env(t_data *ms, char **env)
{
	int		idx;

	idx = -1;
	ms->tab_len = ft_tablen((void **)env);
	ms->tab_env = malloc(sizeof(char **) * (ms->tab_len + 1));
	while (++idx != ms->tab_len)
	{
		ms->tab_env[idx] = ft_split(env[idx], '=');
		if (ft_strcmp(ms->tab_env[idx][0], "OLDPWD") == 0)
		{
			free(ms->tab_env[idx][1]);
			ms->tab_env[idx][1] = 0;
		}
	}
	ms->tab_env[idx] = NULL;
}

int	print_env(t_data *ms)
{
	int		idx;

	idx = -1;
	while (ms->tab_env[++idx])
	{
		if (ms->tab_env[idx][1])
		{
			ft_putstr_fd(ms->tab_env[idx][0], STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(ms->tab_env[idx][1], STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
	}
	return (0);
}

int	builtin_env(t_data *ms, char **param)
{
	if (!param[0])
	{
		print_env(ms);
		return (0);
	}
	else if (param[0] || param[0][0] == '-')
	{
		ft_putstr_fd("minishell: env: --", 2);
		ft_putchar_fd(param[0][1], 2);
		ft_putstr_fd(": invalid option\nenv: usage: env\n", 2);
		return (1);
	}
	return (0);
}
