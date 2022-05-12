/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:46:15 by mdouiri           #+#    #+#             */
/*   Updated: 2022/05/12 16:58:50 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

void	child_one(t_stock *data)
{
	close(data->fd[1]);
	dup2(data->fd[0], 0);
	close(data->fd[0]);
	if (data->av[3] && data->av[3][0] != '\0')
	{
		data->cut2 = ft_split(data->av[3], ' ');
		data->cmd2 = ft_command_exist(data->cut2[0], data->env, data);
	}
	if (!data->cmd2)
	{
		ft_command_not_found(data->av[3], data);
		free_well(data->cut2, 1, data);
		free(data->cut2);
		free_well(NULL, 2, data);
		exit(127);
	}
	execve(data->cmd2, data->cut2, data->env);
	exit(0);
}

void	child_two(t_stock *data)
{
	close(data->fd[0]);
	dup2(data->fd[1], 1);
	close(data->fd[1]);
	if (data->av[2] && data->av[2][0] != '\0')
	{
		data->cut1 = ft_split(data->av[2], ' ');
		data->cmd1 = ft_command_exist(data->cut1[0], data->env, data);
	}
	if (!data->cmd1)
	{
		ft_command_not_found(data->av[2], data);
		free_well(data->cut1, 1, data);
		free(data->cut1);
		free_well(NULL, 2, data);
		exit(1);
	}
	execve(data->cmd1, data->cut1, data->env);
	exit(0);
}

void	ft_begin_processes(t_stock *data)
{
	dup2(data->file1, 0);
	dup2(data->file2, 1);
	data->status = 0;
	if (pipe(data->fd) == -1)
		return ;
	data->pid = fork();
	if (data->pid == -1)
		return ;
	else if (data->pid == 0)
		child_one(data);
	else
	{
		data->pid2 = fork();
		if (data->pid2 == -1)
			return ;
		else if (data->pid2 == 0)
			child_two(data);
		else
		{
			close(data->fd[0]);
			close(data->fd[1]);
			waitpid(data->pid, &data->status, 0);
			waitpid(data->pid2, &data->status, 0);
		}
	}
}

void	ft_parsing(t_stock *data)
{
	if (data->ac == 5)
	{
		data->file1 = ft_check_file(data->av[1], 1);
		data->file2 = ft_check_file(data->av[4], 0);
		if ((data->file1 != -1) && (data->file2 != -1))
		{
			ft_begin_processes(data);
		}
	}
	ft_error(data->ac, data->av, data);
}

int	main(int ac, char **av, char **env)
{
	t_stock	data;

	if (env)
	{
		init(&data, ac, av, env);
		ft_parsing(&data);
		free_well(NULL, 2, &data);
	}
	return (0);
}
