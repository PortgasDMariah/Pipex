/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:00:28 by mdouiri           #+#    #+#             */
/*   Updated: 2022/05/12 16:02:00 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		v;

	res = malloc((ft_strleni(s1) + ft_strleni(s2) + 2) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	v = 0;
	while (s1[i])
	{
		res[v] = s1[i];
		i++;
		v++;
	}
	res[v] = '/';
	v++;
	i = -1;
	while (s2[++i])
	{
		res[v] = s2[i];
		v++;
	}
	res[v] = '\0';
	return (res);
}

char	*ft_strdup(char *s, int i)
{
	int		j;
	char	*res;

	res = malloc((i + 1) * sizeof (char));
	if (!res)
		return (0);
	j = 0;
	while (s[j] && j < i)
	{
		res[j] = s[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}
