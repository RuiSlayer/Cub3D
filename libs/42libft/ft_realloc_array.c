/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:18:07 by slayer            #+#    #+#             */
/*   Updated: 2026/07/22 02:18:10 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_array(char **old, int old_capacity, int new_capacity)
{
	char	**new_arr;
	int		i;

	new_arr = malloc(sizeof(char *) * new_capacity);
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < old_capacity)
	{
		new_arr[i] = old[i];
		i++;
	}
	free(old);
	return (new_arr);
}
