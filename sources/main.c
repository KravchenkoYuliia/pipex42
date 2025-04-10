/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:18:14 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/10 21:13:09 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

int	main()
{
	char *str;

	
	str = malloc(sizeof(char) * ft_strlen(strerror(1)));
	str = strerror(2);
	ft_printf("%s", str);
}
