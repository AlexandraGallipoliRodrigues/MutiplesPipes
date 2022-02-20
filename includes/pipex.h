/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallipo <agallipo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:41:20 by agallipo          #+#    #+#             */
/*   Updated: 2022/02/20 13:36:47 by agallipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define READ_END 0
# define WRITE_END 1
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> //dup2
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>

char	*ft_env_path(char **env, char *argv, char **flags);
char	**ft_path_split(char **env);
int		ft_pipe(char **argv, char **env);
void	ft_print_error(char *error, char *arg);
void	ft_exit_process(int condition, char *argv);
#endif
