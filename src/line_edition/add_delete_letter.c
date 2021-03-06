/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_delete_letter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:30:59 by jamerlin          #+#    #+#             */
/*   Updated: 2018/04/19 15:31:00 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		overwrite_remaining(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		nb;

	nb = 0;
	if ((cp = get_to_pos(inp)))
	{
		nb += print_inp(cp, sh);
		restore_cursor_pos(nb, sh);
	}
}

void		overwrite_deleted(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		dec;

	dec = 0;
	if ((cp = get_to_pos(inp)))
	{
		if (cp->pos == 2 && (dec++ > -1))
		{
			ft_putchar(cp->c);
			check_endline(sh);
		}
		dec += print_inp(cp, sh);
	}
	ft_putchar(' ');
	check_endline(sh);
	custom_left(sh);
	while (dec > sh->width)
	{
		dec -= sh->width;
		ft_putstr(tgetstr("up", NULL));
	}
	while (dec--)
		custom_left(sh);
}

void		delete_beginning(t_inp **inp, t_inp *cp)
{
	if (cp->next)
	{
		(*inp) = (*inp)->next;
		(*inp)->previous = NULL;
		(*inp)->pos = 2;
		free(cp);
	}
	else
	{
		free((*inp));
		(*inp) = NULL;
	}
}

void		delete_letter(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;

	if ((cp = get_to_pos(inp)))
	{
		if (cp->pos == 1)
		{
			custom_left(sh);
			if (cp->previous)
			{
				cp->previous->next = cp->next;
				cp->previous->pos = 1;
				if (cp->next)
					cp->next->previous = cp->previous;
				free(cp);
			}
			else
				delete_beginning(inp, cp);
			overwrite_deleted(sh, inp);
		}
	}
}

void		add_delete_letter(t_sh *sh)
{
	if (sh->buff[0] != 127)
	{
		ft_putchar(sh->buff[0]);
		check_endline(sh);
		inp_insert_posat(&sh->inpl->inp, sh->buff[0]);
		overwrite_remaining(sh, &sh->inpl->inp);
	}
	else
		delete_letter(sh, &sh->inpl->inp);
}
