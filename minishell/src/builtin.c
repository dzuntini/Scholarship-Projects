/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 04:52:02 by pcarella          #+#    #+#             */
/*   Updated: 2021/10/10 18:37:26 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	buitlin_init(t_data *ms, char **env)
{
	int			idx;

	idx = -1;
	get_env(ms, env);
	while (++idx != ms->tab_len)
	{
		if (ft_strcmp(ms->tab_env[idx][0], "PWD") == 0)
			ms->pwd = ft_strdup(ms->tab_env[idx][1]);
		if (ft_strcmp(ms->tab_env[idx][0], "HOME") == 0)
			ms->home = ft_strdup(ms->tab_env[idx][1]);
	}
	return ;
}

int	builtin_check(char *check)
{
	int	idx;

	idx = 0;
	if (check[0] != '_' && ft_isalpha(check[0]) == 0)
		return (1);
	while (check[++idx])
	{
		if (check[idx] != '_' && ft_isalnum(check[idx]) == 0)
			return (1);
	}
	return (0);
}

int	builtin_select(t_data *ms, t_cmd cmd)
{
	if (ft_strcmp(cmd.av[0], "env") == 0)
		return (builtin_env(ms, cmd.av + 1));
	else if (ft_strcmp(cmd.av[0], "echo") == 0)
		return (builtin_echo(cmd.av + 1));
	else if (ft_strcmp(cmd.av[0], "pwd") == 0)
		return (builtin_pwd(ms, cmd.av + 1));
	else if (ft_strcmp(cmd.av[0], "cd") == 0)
		return (builtin_cd(ms, cmd.av + 1));
	else if (ft_strcmp(cmd.av[0], "export") == 0)
		return (builtin_export(ms, cmd.av + 1));
	else if (ft_strcmp(cmd.av[0], "unset") == 0)
		return (builtin_unset(ms, cmd.av + 1));
	else if (ft_strcmp(cmd.av[0], "exit") == 0)
		return (builtin_exit(ms, cmd.av + 1));
	return (84);
}

int	builtin(t_data *ms, int cpt)
{
	return (builtin_select(ms, ms->cmd[cpt]));
}
