/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:10:38 by dzuntini          #+#    #+#             */
/*   Updated: 2021/10/11 17:11:30 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	fill_cmd(t_data *ms, int ic, int i)
{
	int	c;
	int	i2;
	int	i_av;

	ms->cmd[ic].redir_tab = malloc((ms->nb_tkn + 1) * sizeof(t_token));
	ms->cmd[ic].av = malloc((ms->nb_tkn + 1) * sizeof(char *));
	c = 0;
	i2 = 0;
	i_av = 0;
	while (ms->tk_tab[i + c].type && ms->tk_tab[i + c].type != PIPE)
	{
		if (ms->tk_tab[i + c].type != TXT)
		{
			ms->cmd[ic].redir_tab[i2].type = ms->tk_tab[i + c].type;
			ms->cmd[ic].redir_tab[i2++].str = ft_strdup(ms->tk_tab[i + c].str);
		}
		else
			ms->cmd[ic].av[i_av++] = ft_strdup(ms->tk_tab[i + c].str);
		c++;
	}
	ms->cmd[ic].redir_tab[i2].type = END;
	ms->cmd[ic].av[i_av] = 0;
	return (ms->cmd[ic]);
}

char	**add_elem(char **av, char *str)
{
	char	**res;
	int		i;

	res = malloc((ft_tablen((void **)av) + 2) * sizeof(char *));
	i = -1;
	while (av[++i])
	{
		res[i] = ft_strdup(av[i]);
		free(av[i]);
	}
	if (str)
		res[i++] = ft_strdup(str);
	res[i] = 0;
	free(av);
	return (res);
}
