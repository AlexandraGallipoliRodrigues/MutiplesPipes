/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplepipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:29:02 by agallipo          #+#    #+#             */
/*   Updated: 2022/03/15 12:50:51 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_transformer smth, char **env)
{
	char	*command;

	if	(!*smth->command)
		ft_exit_process(1, smth->command);
	command = ft_env_path(env, smth->command, smth->flags);
	if (execve(command, smth->flags, env) < 0)
		ft_exit_process(2, smth->command);
	ft_free_matrix(smth->flags);
	exit(0);
}

void	ft_frst_child(t_transformer smth, char **env, int *fd)
{
	int	fd2;

	close(fd[READ_END]);

	if (smth->fdin != 0)
	{
		dup2(smth->fdin, STDIN_FILENO);  //cambias el stdin para leer el archivo
		close(smth->fdin);
	}
	if (smth->fdout != 1)
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);//extremo de escritura en vez de stdout
		close(fd[WRITE_END]);
	}
/********antes******
	fd2 = open(argv[pipe], O_RDONLY);
	dup2(fd2, STDIN_FILENO);  //cambias el stdin para leer el archivo
	close(fd2);

	dup2(fd[WRITE_END], STDOUT_FILENO);//extremo de escritura en vez de stdout
	close(fd[WRITE_END]);
*/
	if (smth->fdin < 0)
		ft_exit_process(0, );
	ft_execute(argv, env, pipe);
}

void 	ft_mid_child(t_transformer smth, char **env, int *fd)
{

	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);

	dup2(fd[WRITE_END], STDOUT_FILENO);
	close(fd[WRITE_END]);

	ft_execute(smth, env);
}

void	ft_lst_child(t_transformer smth, int *fd, char **env)
{

	//close(fd[WRITE_END); No se si ponerlo aquí
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	
	if (smth->fdout != 1)
	{
		dup2(smth->fdout, STDOUT_FILENO);
		close(smth->fdout);
	}

	if (fd2 < 0)
		ft_exit_process(0, argv[pipe]);
	ft_execute(argv, env, pipe);
}

void	ft_pipes(t_transformer *smth, char **env)
{
	int	fd1[2];
	int	pid;

	pipe(fd1);
	pid = fork();
	if (pid == 0)
		ft_frst_child(smth, env, fd1);
	else
	{
		//mid_child y luego en ccle crear mids si los hay?
		while (smth->next)
		{
			pid = fork();
			if (pid == 0)
				ft_mid_child_pipe(smth, env, fd1);
			else
				wait(&pid);
			smth = smth->next;
		}
		close(fd1[WRITE_END]);
		pid = fork();
		if (pid == 0)
			ft_bastard(smth, env, fd1);
		else
			close(fd1[READ_END]);
		wait(&pid);
	}
}
