/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 23:08:23 by dzuntini          #+#    #+#             */
/*   Updated: 2021/10/11 17:12:44 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_pipes(t_data *ms, int cpt)
{
	if (cpt >= 1)
	{
		dup2(ms->cmd[cpt - 1].pipefd[0], STDIN_FILENO);
		close(ms->cmd[cpt - 1].pipefd[0]);
		close(ms->cmd[cpt - 1].pipefd[1]);
	}
	if (cpt < ms->nb_cmd - 1)
	{
		dup2(ms->cmd[cpt].pipefd[1], STDOUT_FILENO);
		close(ms->cmd[cpt].pipefd[0]);
		close(ms->cmd[cpt].pipefd[1]);
	}
}

void	close_pipes(t_data *ms, int cpt)
{
	if (cpt >= 1)
	{
		close(ms->cmd[cpt - 1].pipefd[0]);
		close(ms->cmd[cpt - 1].pipefd[1]);
	}
}

void	exec_binary(t_cmd cmd, char **e)
{
	int		cpt;

	cpt = -1;
	if (cmd.av[0][0] == '.' || cmd.av[0][0] == '/')
	{
		execve(cmd.av[0], cmd.av, e);
		print_error(cmd.av[0], 2);
		exit(127);
	}
	while (cmd.path[++cpt])
	{
		execve(cmd.path[cpt], cmd.av, e);
	}
	print_error(cmd.av[0], 0);
	exit(127);
}

int	exec_pipeline(t_data *ms)
{
	int	cpt;
	int	ret;

	cpt = -1;
	while (++cpt < ms->nb_cmd)
	{
		if (cpt < ms->nb_cmd - 1)
			pipe(ms->cmd[cpt].pipefd);
		ms->cmd[cpt].pid = fork();
		if (ms->cmd[cpt].pid == -1)
			exit(128);
		if (!ms->cmd[cpt].pid)
		{
			dup_pipes(ms, cpt);
			ret = redir(ms->cmd[cpt].redir_tab);
			if (ret)
				exit(ret);
			atomic_exec(ms, cpt);
		}
		close_pipes(ms, cpt);
	}
	return (get_exit_code(ms));
}

int	exec(t_data *ms)
{
	int	ret;

	if (ms->nb_cmd == 1)
	{
		if (ms->cmd[0].av[0] && is_builtin(ms->cmd[0].av[0]))
		{
			ret = redir(ms->cmd[0].redir_tab);
			if (ret)
				return (ret);
			return (builtin(ms, 0));
		}
	}
	return (exec_pipeline(ms));
}
