/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_updt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:23:20 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/28 23:07:50 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_updt(char *str, char *update)
{
	char *nw;

	nw = update;
	if (str != NULL)
		free(str);
	str = update;
	return (str);
}
