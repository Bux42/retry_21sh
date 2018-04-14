/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 17:30:41 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/11 17:30:42 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	sve_fd(int save_fd[3])
{
	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	save_fd[2] = dup(STDERR_FILENO);
}

void	reset_fd(int save_fd[3])
{
	dup2(save_fd[0], 0);
	close(save_fd[0]);
	dup2(save_fd[1], 1);
	close(save_fd[1]);
	dup2(save_fd[2], 2);
	close(save_fd[2]);
}

void	builtin_redir(t_listc *cp, int (*func)(char **, t_sh*), t_sh *sh)
{
	int		save_fd[3];
	t_pipe	*p;

	sve_fd(save_fd);
	if (!(p = (t_pipe *)malloc(sizeof(t_pipe) * ((2)))))
		return ;
	redirect(cp, p, 0, &cp->redirs);
	func = cp->func;
	sh->retval = func(cp->cont, sh);
	reset_fd(save_fd);
	close_tabtube(2, p);
}

int		condition_is_valid(t_sh *sh, t_listc *cmd)
{
	if (cmd->prev)
	{
		if (cmd->prev->sep_type & AND)
			if (WEXITSTATUS(sh->retval) != 0 || sh->retval == 127)
				return (0);
		if (cmd->prev->sep_type & OR)
			if (WEXITSTATUS(sh->retval) == 0 && sh->retval != 127)
				return (0);
	}
	return (1);
}

void	count_heredoc(t_listc *cmd)
{
	t_redir *cp;
	int i;

	i = 0;
	cp = cmd->redirs;
	while (cmd->redirs)
	{
		if (cmd->redirs->redir[1] == HEREDOC)
			i++;
		cmd->redirs = cmd->redirs->next;
	}
	cmd->redirs = cp;
	cmd->nb_here = i;
	//printf("i = [%d]\n", i);
}

void	execute_tokens(t_listc **tok, t_sh *sh)
{
	t_listc	*cp;
	int		(*func)(char **, t_sh*);

	if (!(cp = (*tok)))
		return ;
	while (cp)
	{
		if (cp->func && cp->sep_type != PIPE && condition_is_valid(sh, cp))
		{
			func = cp->func;
			(cp->redirs) ? builtin_redir(cp, func, sh) :
				(sh->retval = func(cp->cont, sh));
		}
		else if (cp->sep_type != 2 && condition_is_valid(sh, cp))
			exec_cli(cp->cont[0], cp, sh);
		else if (cp->sep_type & PIPE)
		{
			prepare_pipe(cp);
			exec_cli(cp->cont[0], cp, sh);
			while (cp->next && cp->sep_type & PIPE)
				cp = cp->next;
		}
		cp = cp->next;
	}
}
