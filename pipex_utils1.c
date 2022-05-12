/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:58:05 by mdouiri           #+#    #+#             */
/*   Updated: 2022/05/12 16:59:01 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_command_exist(char *cmd, char **env, t_stock *data)
{
	char	*path;
	char	*path_bis;
	char	*new_path;

	path = (ft_path(env) + 5);
	if (ft_found_char(cmd, '/') != -1)
	{
		if (cmd && access(cmd, X_OK) == 0)
			return (cmd);
		else
			return (data->error = 1, NULL);
	}
	while (cmd && path && (ft_found_char(path, ':') != -1))
	{
		path_bis = ft_strdup(path, ft_found_char(path, ':'));
		new_path = ft_strjoin(path_bis, cmd);
		free(path_bis);
		if (cmd && access(new_path, X_OK) == 0)
		{
			return (new_path);
		}
		free(new_path);
		path = path + (ft_found_char(path, ':') + 1);
	}
	return (NULL);
}

int	ft_check_file(char *str, int tmp)
{
	int	fd;

	if (tmp == 1)
		fd = open(str, O_RDONLY);
	else
		fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd < 0)
		return (-1);
	return (fd);
}

char	*ft_path(char **env)
{
	char	**enva;
	int		i;

	i = 0;
	enva = env;
	while (enva[i] && (ft_str(enva[i], "PATH=") == 0))
		i++;
	if (!enva[i])
		return (NULL);
	return (enva[i]);
}

int	ft_str(char *env, char *find)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i] == find[i])
		i++;
	if (find[i] == '\0')
		return (1);
	return (0);
}

void	init(t_stock *data, int ac, char **av, char **env)
{
	data->ac = ac;
	data->av = av;
	data->env = env;
	data->file1 = 0;
	data->file2 = 0;
	data->fd[0] = 0;
	data->fd[1] = 0;
	data->cut1 = NULL;
	data->cut2 = NULL;
	data->cmd1 = NULL;
	data->cmd2 = NULL;
	data->error = 0;
}
