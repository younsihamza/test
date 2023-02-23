/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:35:36 by hyounsi           #+#    #+#             */
/*   Updated: 2023/02/19 11:52:25 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t ft_strlen(char *p)
{
	int i ;
	while(p[i])
		i++;
	return(i);
}
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	j = 0;
	i = 0;
	p = malloc(sizeof(char) * (len_s1 + len_s2) + 1);
	if (!p)
		return (NULL);
	while (*(s1 + j))
		*(p + i++) = *(s1 + j++);
	j = 0;
	while (*(s2 + j))
		*(p + i++) = *(s2 + j++);
	*(p + i) = '\0';
	return (p);
}
