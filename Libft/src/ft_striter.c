/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:20:31 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/28 23:08:12 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char*))
{
	if (!s || !f)
		return ;
	while (*s != '\0')
	{
		f(s);
		s++;
	}
}
