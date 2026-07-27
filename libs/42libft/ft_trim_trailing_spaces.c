/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_trailing_spaces.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 19:49:38 by slayer            #+#    #+#             */
/*   Updated: 2026/07/27 19:51:14 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_trim_trailing_spaces(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'
		|| str[len - 1] == '\n'))
	{
		str[len - 1] = '\0';
		len--;
	}
}
