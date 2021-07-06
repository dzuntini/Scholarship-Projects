/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 13:12:01 by dzuntini          #+#    #+#             */
/*   Updated: 2021/07/06 15:10:15 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

void	ft_putchar(char c);
void	ft_putnbr(int nb);
void	ft_putstr(char *str);
void	booting(int pid);
void	ft_receive(short i);

#endif
