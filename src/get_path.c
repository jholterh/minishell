#include "minishell.h"

char	**get_paths(char **envp)
{
	int		i;
	char	*env_path;
	char	**paths;

	env_path = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env_path = ft_strdup(envp[i] + 5);
			if (env_path == NULL)
				return (NULL);
			break ;
		}
		i++;
	}
	if (env_path == NULL)
		return (NULL);
	paths = ft_split(env_path, ':');
	free(env_path);
	if (paths == NULL)
		return (NULL);
	return (paths);
}

char	*find_path(char **paths, char *command)
{
	int		i;
	char	*tmp_path;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		if (tmp_path == NULL)
			return (NULL);
		full_path = ft_strjoin(tmp_path, command);
		free(tmp_path);
		if (full_path == NULL)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	**prepare_args(char **paths, char *command)
{
	char	**args;
	char	*full_path;

	args = ft_split(command, ' ');
	if (args == NULL)
		return (NULL);
	full_path = find_path(paths, args[0]);
	if (full_path == NULL)
	{
		ft_strfree(args);
		return (NULL);
	}
	free(args[0]);
	args[0] = full_path;
	return (args);
}
