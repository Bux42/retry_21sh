/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 17:30:33 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/17 21:20:14 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	check_fd(t_sh *sh, int fd)
{
	int		save_fd[3];

	if (fd != -1 && fcntl(fd, F_GETFD) == -1)
	{
		sve_fd(save_fd);
		reset_fd(save_fd);
		ft_putstr_fd("21sh: ", 2);
		ft_putnbr_fd(fd, 2);
		ft_putendl_fd(": bad file descriptor", 2);
		sh->aggr_fail = 0;
	}
}

void	do_aggre(t_listc *cmd, t_pipe *tabtube, int i)
{
	check_fd(g_sh, cmd->redirs->redir[2]);
	if (cmd->redirs->file == NULL)
		tabtube[i].cote[0] = cmd->redirs->redir[2];
	else
	{
		if (cmd->redirs->redir[1] == AGGR + AGGRFILE)
			tabtube[i].cote[0] = open(cmd->redirs->file, O_RDWR | O_APPEND
				| O_CREAT, S_IRWXU);
		else if (cmd->redirs->redir[1] == AGGR + AGGRFILE + AGGROUT)
			tabtube[i].cote[0] = open(cmd->redirs->file, O_RDWR | O_TRUNC
				| O_CREAT, S_IRWXU);
	}
	tabtube[i].cote[1] = cmd->redirs->redir[0];
	if (cmd->redirs->redir[1] == AGGR + AGGRFILE && tabtube[1].cote[0] == -1)
		close(tabtube[1].cote[1]);
	else if (cmd->redirs->redir[1] == LAGGRIN && tabtube[i].cote[0] == -1)
		close(tabtube[i].cote[1]);
	else if (cmd->redirs->redir[1] == AGGR + AGGRFILE + AGGROUT
		&& tabtube[i].cote[0] == -1)
		close(tabtube[i].cote[1]);
	else if (cmd->redirs->redir[1] == CLOSEAGGR)
		close(tabtube[i].cote[1]);
}
