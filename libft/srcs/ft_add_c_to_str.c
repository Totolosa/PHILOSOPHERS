#include "libft.h"

static int	init(char **new, int *len, char **str)
{
	if (*str != NULL)
	{
		*new = ft_calloc(ft_strlen(*str) + 2, 1);
		if (*new == NULL)
			return (0);
		*len = ft_strlen(*str);
	}
	else
	{
		*new = ft_calloc(2, 1);
		if (*new == NULL)
			return (0);
		*len = 0;
	}
	return (1);
}

int	ft_add_c_to_str(char c, char **str)
{
	char	*new;
	int		len;
	int		i;

	len = 0;
	new = NULL;
	if (!init(&new, &len, str))
		return (0);
	i = -1;
	while (++i < len)
		new[i] = (*str)[i];
	new[i] = c;
	i++;
	new[i] = '\0';
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
	*str = new;
	return (1);
}
