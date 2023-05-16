/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_statics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:24:19 by rficht            #+#    #+#             */
/*   Updated: 2023/05/16 14:24:32 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	stat_interactive(int val)
{
	static int	interactive;

	if (val >= 0)
		interactive = val;
	return (interactive);
}
