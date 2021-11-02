/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:32:17 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/02 17:15:39 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	*ft_test_malloc(size_t size, int failure_point)
{
	static int count;

	printf("Malloc: %d\n", count);
	count++;
	if (count == failure_point)
		return (NULL);
	else 
		return (malloc(size));
}
