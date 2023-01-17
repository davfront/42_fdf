/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:05:20 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/23 16:06:15 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_error_exit(char *msg)
{
	ft_putstr_fd("ERROR: ", STDERR_FILENO);
	if (msg && *msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	else
		perror(NULL);
	exit(EXIT_FAILURE);
}
