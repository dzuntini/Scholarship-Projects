/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarella <pcarella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:14:35 by dzuntini          #+#    #+#             */
/*   Updated: 2022/02/07 20:09:43 by pcarella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *ms, char **e)
{
	g_sig.exit_code = 0;
	g_sig.pid = 0;
	g_sig.interrupt_hd = 0;
	ms->in_cpy = dup(STDIN_FILENO);
	ms->out_cpy = dup(STDOUT_FILENO);
	buitlin_init(ms, e);
}

int	line_status(char *line)
{
	int		i;
	char	quote;
	int		last_ch_is_pipe;

	if (!*line)
		return (1);
	i = -1;
	quote = 0;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
			quote = line[i] * (quote == 0) + quote * (line[i] != quote);
		if (line[i] == '|')
			last_ch_is_pipe = 1;
		else if (line[i] != ' ')
			last_ch_is_pipe = 0;
	}
	if (quote != 0 || last_ch_is_pipe == 1)
	{
		print_error(0, 4);
		return (258);
	}
	return (0);
}

int	launch2(t_data *ms)
{
	int	ret;

	ret = tokenize(ms);
	free_tabstr(ms->word_tab);
	dup2(ms->in_cpy, STDIN_FILENO);
	if (g_sig.interrupt_hd == 1 || ret)
	{
		free_tkns(ms->tk_tab);
		if (g_sig.interrupt_hd == 1)
			return (1);
		if (ret)
			return (ret);
	}
	parser(ms);
	free_tkns(ms->tk_tab);
	ret = exec(ms);
	free_cmd(ms->cmd, ms->nb_cmd);
	free_tabstr(ms->e);
	return (ret);
}

int	launch(t_data *ms, char *line)
{
	int	ret;

	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	line = ft_strtrim(line, " ");
	ret = line_status(line);
	if (ret)
	{
		free(line);
		return (ret * (ret != 1) + g_sig.exit_code * (ret == 1));
	}
	add_history(line);
	ret = lexer(ms, line);
	free(line);
	if (ret)
	{
		free_tabstr(ms->word_tab);
		return (ret);
	}
	return (launch2(ms));
}

int	main(int ac, char **av, char **e)
{
	t_data	v;
	char	*line;

	(void)av;
	if (ac != 1)
	{
		print_error("Do : ./minishell\n", 3);
		return (1);
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	init_data(&v, e);
	while (1)
	{
		echo_control_seq(0);
		dup2(v.in_cpy, STDIN_FILENO);
		dup2(v.out_cpy, STDOUT_FILENO);
		g_sig.status = 0;
		line = readline("\x1b[34m|Minishell|\x1b[0m@: ");
		g_sig.status = 1;
		g_sig.exit_code = launch(&v, line);
		clear();
		free (line);
	}
	return (g_sig.exit_code);
}
