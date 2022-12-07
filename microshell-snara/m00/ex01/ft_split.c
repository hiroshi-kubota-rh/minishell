#include <stdlib.h>
#include <stdbool.h>

size_t	ft_wordcount(char const *s, bool issep())
{
	size_t	word;
	size_t	i;

	word = 0;
	i = 0;
	while (s[i])
	{
		if ((i == 0 || issep(s[i - 1])) && !issep(s[i]))
			word++;
		i++;
	}
	return (word);
}

char	*ft_strcdup(char const *s, bool issep())
{
	size_t	i;
	char	*dst;

	i = 0;
	while (s[i] && !issep(s[i]))
		i++;
	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	dst[i] = '\0';
	while (i--)
		dst[i] = s[i];
	return (dst);
}

void	*ft_free_split(char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split_func(char const *s, bool issep())
{
	char	**arr;
	size_t	word;
	size_t	i;

	arr = (char **)malloc(sizeof(char *) * (ft_wordcount(s, issep) + 1));
	word = 0;
	i = 0;
	while (s[i])
	{
		if ((i == 0 || issep(s[i - 1])) && !issep(s[i]))
		{
			arr[word] = ft_strcdup(&s[i], issep);
			if (!arr[word])
				return (ft_free_split(arr));
			word++;
		}
		i++;
	}
	arr[word] = NULL;
	return (arr);
}
