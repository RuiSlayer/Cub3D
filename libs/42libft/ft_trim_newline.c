/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_newline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 23:15:29 by slayer            #+#    #+#             */
/*   Updated: 2026/07/14 23:19:27 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_trim_newline(char *str)
{
	size_t	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}
