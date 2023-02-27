/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:27:39 by pcarella          #+#    #+#             */
/*   Updated: 2021/09/27 18:28:09 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_export(t_data *ms, char *param)
{
	int		idx;
	char	**find;

	idx = -1;
	if (param[0] == '=')
		return (1);
	find = split_export(param);
	if (!find || builtin_check(find[0]) == 1)
	{
		if (find)
			free_tabstr(find);
		return (1);
	}
	while (ms->tab_env[++idx])
	{
		if (ft_strcmp(ms->tab_env[idx][0], find[0]) == 0)
		{
			free_tabstr(find);
			if (join_export(NULL, param, 1) == 1)
				return (4);
			return (3);
		}
	}
	free_tabstr(find);
	return (0);
}

int	add_export(t_data *ms, char *param)
{
	int		idx;
	char	***new_env;

	ms->tab_len += 1;
	new_env = malloc(sizeof(char **) * (ms->tab_len + 1));
	if (!new_env)
		return (1);
	idx = -1;
	while (++idx < ms->tab_len - 1)
	{
		new_env[idx] = malloc(2 * sizeof(char *));
		new_env[idx][0] = ft_strdup(ms->tab_env[idx][0]);
		if (ms->tab_env[idx][1])
			new_env[idx][1] = ft_strdup(ms->tab_env[idx][1]);
		else
			new_env[idx][1] = NULL;
	}
	new_env[idx] = split_export(param);
	if (!new_env[idx])
		return (1);
	new_env[idx + 1] = NULL;
	free_matrix(ms->tab_env);
	ms->tab_env = new_env;
	return (0);
}

int	update_export(t_data *ms, char *param)
{
	int		idx;
	char	**update;
	char	***new_env;

	update = split_export(param);
	new_env = malloc(sizeof(char **) * (ms->tab_len + 1));
	if (!update || !new_env)
		return (1);
	idx = -1;
	while (ms->tab_env[++idx])
	{
		if (ft_strcmp(ms->tab_env[idx][0], update[0]) == 0)
			new_env[idx] = copy_env(ms->tab_env[idx][0], update[1]);
		else
			new_env[idx] = copy_env(ms->tab_env[idx][0], ms->tab_env[idx][1]);
	}
	new_env[idx] = NULL;
	free_matrix(ms->tab_env);
	ms->tab_env = new_env;
	free_tabstr(update);
	return (0);
}

int	join_export(t_data *ms, char *param, int select)
{
	int		idx;
	char	*tmp;
	char	**join;

	idx = -1;
	if (select == 1)
	{
		while (param[++idx])
			if (param[idx] == '+' && param[idx + 1] == '=')
				return (1);
		return (0);
	}
	join = split_export(param);
	while (ms->tab_env[++idx])
	{
		if (ft_strcmp(ms->tab_env[idx][0], join[0]) == 0)
		{
			tmp = ft_strjoin(ms->tab_env[idx][1], join[1]);
			free(ms->tab_env[idx][1]);
			ms->tab_env[idx][1] = ft_strdup(tmp);
			free(tmp);
		}
	}
	free_tabstr(join);
	return (0);
}

int	builtin_export(t_data *ms, char **param)
{
	int		idx;
	int		ret;

	idx = -1;
	ret = 0;
	if (!param[0] || !param)
		return (sort_export(ms));
	while (param[++idx])
	{
		ret = find_export(ms, param[idx]);
		if (ret == 1)
			return (error_export(param[idx]));
		else if ((ret == 3 && update_export(ms, param[idx]) == 1)
			|| (ret == 0 && add_export(ms, param[idx]) == 1)
			|| (ret == 4 && join_export(ms, param[idx], 0) == 1))
			return (1);
	}
	return (0);
}
