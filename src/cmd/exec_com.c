/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:39:44 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 19:13:14 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*fill_join_word(char **path, int i, char *word)
{
	int		j;
	int		k;
	int		count;
	char	*new;

	j = -1;
	k = -1;
	count = ft_len(path[i]) + ft_len(word);
	new = (char *)malloc(sizeof(char) * (count + 2));
	if (!new)
		return (NULL);
	while (path[i][++k])
		new[++j] = path[i][k];
	new[++j] = '/';
	k = -1;
	while (word[++k])
		new[++j] = word[k];
	new[++j] = '\0';
	return (new);
}

char	**join_word(char **path, char *word)
{
	char	**new_path;
	int		i;

	i = 0;
	while (path[i])
		i++;
	new_path = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_path)
		return (NULL);
	new_path[i] = 0;
	i = -1;
	while (path[++i])
	{
		new_path[i] = fill_join_word(path, i, word);
		if (new_path[i] == NULL)
		{
			ft_free_tab(new_path);
			return (NULL);
		}
	}
	return (new_path);
}

void	launch_exec_cmd_path(t_sh *sh, char *word, char **list_arg)
{
	char	*value;
	char	**path;
	int		i;
	char	**path_complete;

	i = 0;
	value = get_lst_value_of(sh, "PATH");
	path = ft_split(value, ':');
	if (path == NULL)
		ft_error(sh, strerror(errno), NULL, NULL);
	path_complete = join_word(path, word);
	if (path_complete == NULL)
		ft_error(sh, strerror(errno), NULL, NULL);
	while (path_complete[i]
		&& execve(path_complete[i], list_arg, sh->tab_env) == -1)
	{
		if (!path_complete[i + 1]
			&& execve(path_complete[i], list_arg, sh->tab_env) == -1)
			ft_error(sh, "command not found", word, NULL);
		i++;
	}
	ft_free_tab(path);
	ft_free_tab(path_complete);
}

void	launch_exec(t_sh *sh, char *spl, char *word, char **list_arg)
{
	struct stat	stock;

	if (word[0] == '/' || word[0] == '.')
	{
		stat(word, &stock);
		if (S_ISDIR(stock.st_mode))
			ft_error(sh, "is a directory", word, NULL);
		if (execve(word, list_arg, sh->tab_env) == -1)
			ft_error(sh, strerror(errno), word, NULL);
	}
	else
		launch_exec_cmd_path(sh, word, list_arg);
}
