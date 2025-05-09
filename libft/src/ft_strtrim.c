/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:01:20 by aadyan            #+#    #+#             */
/*   Updated: 2025/01/25 18:26:16 by aadyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_str(char c, char const *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		++i;
	}
	return (0);
}

static int	get_arr(int start, int end, char *arr, char const *s1)
{
	int	i;

	i = 0;
	while (start + i <= end)
	{
		arr[i] = s1[start + i];
		++i;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*arr;

	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1) - 1;
	while (end >= 0 && in_str(s1[end], set))
		--end;
	start = 0;
	while (s1[start] && in_str(s1[start], set))
		++start;
	if (start > end)
		return (ft_strdup(""));
	arr = (char *)malloc((end - start + 2) * sizeof(char));
	if (!arr)
		return (NULL);
	i = get_arr(start, end, arr, s1);
	arr[i] = '\0';
	return (arr);
}
