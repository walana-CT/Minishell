/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_terminal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:53:41 by rficht            #+#    #+#             */
/*   Updated: 2023/05/12 13:19:46 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	terminal_reset(t_prog *program)
{
	if (program->term_fd != -1)
	{
		if (tcsetattr(program->term_fd, TCSANOW, &program->term_original))
			return (errno = ENOTSUP);
	}
	return (errno = 0);
}

int	terminal_init(t_prog *program)
{
	program->goon = 1;
	program->pipe = 0;
	if (program->term_fd != -1)
		return (errno = 0);
	if (isatty(STDERR_FILENO))
		program->term_fd = STDERR_FILENO;
	else if (isatty(STDIN_FILENO))
		program->term_fd = STDIN_FILENO;
	else if (isatty(STDOUT_FILENO))
		program->term_fd = STDOUT_FILENO;
	else
		return (errno = ENOTTY);
	if (tcgetattr(program->term_fd, &program->term_original)
		|| tcgetattr(program->term_fd, &program->term_settings))
		return (errno = ENOTSUP);
	tcsetattr(program->term_fd, TCSANOW, &program->term_settings);
	return (errno = 0);
}
