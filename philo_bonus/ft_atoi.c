/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:33:46 by hyounsi           #+#    #+#             */
/*   Updated: 2023/02/14 13:21:01 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	llm(char const *str, int i, int sin)
{
	int	j;
	int	result;

	j = 0;
	result = 0;
	while (*(str + i) == 48)
		i++;
	while ((*(str + i) >= 48) && (*(str + i) <= 57))
	{
		result = result * 10;
		result += *(str + i) - '0';
		i++;
		if (j >= 19)
		{
			if (sin == -1)
				return (0);
			return (-1);
		}
		j++;
	}
	return (result * sin);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	result;

	result = 0;
	s = 1;
	i = 0;
	while ((*(str + i) == 32) || (*(str + i) >= 9 && *(str + i) <= 13))
		i++;
	if (*(str + i) == '-')
	{
		s = -1;
		i++;
	}
	else if (*(str + i) == '+')
		i++;
	return (llm(str, i, s));
}
