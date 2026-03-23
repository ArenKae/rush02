#ifndef RUSH_H
# define RUSH_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include "../libft/include/libft.h"
#include "../libft/gnl/get_next_line.h"

typedef struct	s_dict
{
	char	*key;
	char	*value;
	struct s_dict	*next;
}				t_dict;

char	*ft_trim(char *str);
t_dict	*new_dict_node(char *buffer);
void	ft_free(t_dict *dict);

#endif
