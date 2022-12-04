#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sb;
	size_t	j;

	if (s == NULL)
		return (NULL);
	if (strlen(s) <= start || len == 0)
	{
		sb = calloc(1, sizeof(char));
		return (sb);
	}
	j = strlen(s) - start;
	if (len > j)
	{
		if (!(sb = (char *)malloc(sizeof(char) * (j + 1))))
			return (NULL);
		sb = memcpy(sb, (s + start), j);
		sb[j] = '\0';
		return (sb);
	}
	if (!(sb = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	sb = memcpy(sb, (s + start), len);
	sb[len] = '\0';
	return (sb);
}