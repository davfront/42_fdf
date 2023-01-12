/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_hex_char_value.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/12 12:24:19 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	fdf_get_hex_char_value(char c)
{
	char	hex[17];
	char	*s;

	if (!c)
		return (-1);
	ft_strlcpy(hex, "0123456789ABCDEF", 17);
	s = ft_strchr(hex, ft_toupper(c));
	if (s)
		return (s - hex);
	return (-1);
}
