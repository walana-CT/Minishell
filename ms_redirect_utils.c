/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirect_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:53:26 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/08 14:29:50 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



void	ms_get_infile(t_pipex *p, char **argv)
{
	char	*str;

	if (p->limiter)
	{
		str = get_next_line(0);
		while (ft_strncmp(str, p->limiter, ft_sstrlen(str)) != 10)
		{		
			write(p->pipe[0][1], str, ft_sstrlen(str));
			free(str);
			str = get_next_line(0);
		}
		free(str);
		close(p->pipe[0][1]);
	}
	else
	{
		p->pipe[0][0] = open(argv[1], O_RDONLY);
		if (p->pipe[0][0] == -1)
			px_file_err(argv[1]);
	}
}

