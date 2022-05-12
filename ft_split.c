/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:08:03 by mdouiri           #+#    #+#             */
/*   Updated: 2022/05/12 16:10:03 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strleni(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static int	ft_charset(char charset, char a)
{
	if (charset == a)
		return (1);
	else
		return (0);
}

static int	ft_word(char sep, char *str)
{
	int	i;
	int	wd;

	i = 0;
	wd = 0;
	while (ft_charset(sep, str[i]) == 1 && str[i])
		i++;
	while (str[i])
	{
		wd++;
		while (ft_charset(sep, str[i]) == 0 && str[i])
			i++;
		while (ft_charset(sep, str[i]) == 1 && str[i])
			i++;
	}
	return (wd);
}

static char	*ft_strdupi(const char *str, char sep)
{
	int		i;
	int		v;
	char	*res;

	i = 0;
	v = 0;
	while (str[i] && ft_charset(sep, str[i]) == 0)
		i++;
	res = (char *)malloc((i + 1) * sizeof (char));
	i = 0;
	if (!res)
		return (0);
	while (ft_charset(sep, str[i]) == 1 && str[i])
		i++;
	while (ft_charset(sep, str[i]) == 0 && str[i])
	{
		res[v] = str[i];
		i++;
		v++;
	}
	res[v] = '\0';
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		v;
	char	**split;

	split = (char **)malloc((ft_word(c, ((char *)s)) + 1) * sizeof(char *));
	if (!split)
		return (0);
	v = 0;
	i = 0;
	while (ft_charset(c, s[i]) == 1 && s[i])
		i++;
	while (s[i])
	{
		split[v] = ft_strdupi(&s[i], c);
		if (!split[v])
			return (0);
		while (ft_charset(c, s[i]) == 0 && s[i])
			i++;
		while (ft_charset(c, s[i]) == 1 && s[i])
			i++;
		v++;
	}
	split[v] = 0;
	return (split);
}
