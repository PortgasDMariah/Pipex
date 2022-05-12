/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_and_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:04:37 by mdouiri           #+#    #+#             */
/*   Updated: 2022/05/12 16:52:22 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_found_char(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

void	ft_error(int ac, char **av, t_stock *data)
{
	if (ac != 5)
	{
		write(2, "Invalid nb of args \n", 20);
		exit(1);
	}
	if (data->file1 == -1)
	{
		write(2, "bash: ", 6);
		perror(av[1]);
	}
	if (data->file2 == -1)
	{
		write(2, "bash: ", 6);
		perror(av[4]);
	}
	free_well(NULL, 2, data);
}

void	ft_command_not_found(char *av, t_stock *data)
{
	ft_putstr_fd("bash: ", 2);
	if (data->error != 1)
	{
		ft_putstr_fd(av, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
		perror(av);
}

void	free_well(char	**str, int tmp, t_stock *data)
{
	int	i;

	i = 0;
	if (tmp == 1)
	{
		if (!str)
			return ;
		while (str && str[i])
		{
			free(str[i]);
			i++;
		}
	}
	else
	{
		if (data->file2 != -1)
			close(data->file2);
		if (data->file1 != -1)
			close(data->file1);
	}
}
