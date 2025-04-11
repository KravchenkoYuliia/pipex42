/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:43:36 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/11 17:58:35 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

void	ft_exit(int infile, int outfile)
{
	if (infile != 0)
		close(infile);
	else if (outfile != 0)
		close(outfile);
	exit(EXIT_FAILURE);
}
