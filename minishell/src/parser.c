/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 01:32:15 by dzuntini          #+#    #+#             */
/*   Updated: 2021/10/11 17:11:20 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_string(char *str, int *i)
{
	char	q;
	int		i_tmp;
	char	*tmp;

	tmp = malloc(ft_strlen(str) + 1);
	i_tmp = 0;
	q = 0;
	while (str[*i] && (q != 0 || str[*i] != ' '))
	{
		if (str[*i] == '"' || str[*i] == '\'')
		{
			if (q && q != str[*i])
				tmp[i_tmp++] = str[*i];
			q = str[*i] * (q == 0) + q * (q != str[*i]);
		}
		else
			tmp[i_tmp++] = str[*i];
		(*i)++;
	}
	tmp[i_tmp] = 0;
	return (tmp);
}

char	**divide(t_cmd cmd, t_data *ms)
{
	char	**res;
	int		i_av;
	int		i_str;
	char	*tmp;

	res = malloc(sizeof(char *));
	res[0] = 0;
	i_av = -1;
	while (cmd.av[++i_av])
	{
		expand(&(cmd.av[i_av]), ms);
		i_str = 0;
		while (cmd.av[i_av][i_str])
		{
			tmp = get_next_string(cmd.av[i_av], &i_str);
			res = add_elem(res, tmp);
			free(tmp);
			while (cmd.av[i_av][i_str] == ' ')
				i_str++;
		}
	}
	free_tabstr(cmd.av);
	return (res);
}

void	update_env(t_data *ms)
{
	int		i;
	int		i_e;
	char	*tmp;

	ms->e = malloc((ms->tab_len + 1) * sizeof(char *));
	i = -1;
	i_e = 0;
	while (++i < ms->tab_len)
	{
		if (ms->tab_env[i][1])
		{
			tmp = ft_strjoin(ms->tab_env[i][0], "=");
			ms->e[i_e++] = ft_strjoin(tmp, ms->tab_env[i][1]);
			free(tmp);
		}
	}
	ms->e[i_e] = 0;
}

char	**get_cmd_path(t_data *ms, char *cmd)
{
	char	**ret;
	int		cpt;
	char	*tmp;

	if (!cmd)
	{
		ret = malloc(sizeof(char *));
		ret[0] = 0;
		return (ret);
	}
	tmp = get_tabenv(ms, "PATH");
	ret = ft_split(tmp, ':');
	free(tmp);
	cpt = -1;
	while (ret[++cpt])
	{
		tmp = ft_strjoin(ret[cpt], "/");
		free(ret[cpt]);
		ret[cpt] = ft_strjoin(tmp, cmd);
		free(tmp);
	}
	return (ret);
}

/*
Remplit v em fonction de tk_tab au format demande par la fonction d'execution
	nb_cmd = nb pipe + 1
	Parcours chaque token et remplit la liste des redirection
	et des av dans la commande associee
	Expand chaque av
	Dans chaque av, soustait les quotes et decoupe en fonction des ' ' unquoted
	A partir de av[0], remplit les paths d'execution potentiels
*/		
void	parser(t_data *ms)
{
	int	i_cmd;
	int	i_tkn;

	ms->nb_cmd = 1;
	i_tkn = -1;
	while (ms->tk_tab[++i_tkn].type)
		if (ms->tk_tab[i_tkn].type == PIPE)
			ms->nb_cmd++;
	ms->nb_tkn = i_tkn;
	ms->cmd = malloc(ms->nb_cmd * sizeof(t_cmd));
	i_cmd = -1;
	i_tkn = -1;
	while (++i_cmd < ms->nb_cmd)
	{
		ms->cmd[i_cmd] = fill_cmd(ms, i_cmd, ++i_tkn);
		ms->cmd[i_cmd].av = divide(ms->cmd[i_cmd], ms);
		ms->cmd[i_cmd].path = get_cmd_path(ms, ms->cmd[i_cmd].av[0]);
		while (ms->tk_tab[i_tkn].type && ms->tk_tab[i_tkn].type != PIPE)
			i_tkn++;
	}
	update_env(ms);
}
