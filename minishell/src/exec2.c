/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:12:15 by dzuntini          #+#    #+#             */
/*   Updated: 2021/10/11 17:12:36 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	atomic_exec(t_data *ms, int cpt)
{
	if (ms->cmd[cpt].av[0])
	{
		if (is_builtin(ms->cmd[cpt].av[0]))
			exit(builtin(ms, cpt));
		exec_binary(ms->cmd[cpt], ms->e);
	}
	else
		exit(0);
}

int	get_exit_code(t_data *ms)
{
	int	cpt;

	cpt = -1;
	while (++cpt < ms->nb_cmd)
		waitpid(ms->cmd[cpt].pid, &(ms->cmd[cpt].exit_code), 0);
	if (g_sig.exit_code == 130)
		return (130);
	if (g_sig.exit_code == 131)
		return (131);
	return (WEXITSTATUS(ms->cmd[cpt - 1].exit_code));
}
