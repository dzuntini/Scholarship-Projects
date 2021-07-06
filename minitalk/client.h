/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 13:19:15 by dzuntini          #+#    #+#             */
/*   Updated: 2021/06/29 13:21:01 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

void	ft_putstr(char *str);
void	ft_putchar(char c);
int		ft_number(char *str);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	ft_sender(char *a, int pid);
void	ft_atob(int a, int pid);
void	ft_kill(short i, int pid);

#endif
