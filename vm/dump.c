/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfedorko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 18:36:49 by lfedorko          #+#    #+#             */
/*   Updated: 2017/10/27 18:36:56 by lfedorko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

char	*ft_itoa_memory(uintmax_t n, long long int base)
{
	int			len;
	char		*temp;
	char		*ptr;

	len = 2;
	ptr = (char *)malloc(len);
	bzero(ptr, len + 1);
	ptr[len] = '\0';
	if (ptr == NULL)
		return (NULL);
	temp = ptr;
	while (len > 0)
	{
		if (n % base < 10)
			*(ptr + len - 1) = (n % base + '0');
		else
			*(ptr + len - 1) = (('a' + n % base) - 10);
		n = n / base;
		--len;
	}
	return (temp);
}

int		ft_count_base(uintmax_t nb, long long int base)
{
	if (nb == 0)
		return (1);
	if (nb < (uintmax_t)base)
		return (1);
	else
		return (ft_count_base(nb / base, base) + 1);
}

char	*ft_itoa_base(uintmax_t n, long long int base)
{
	int			len;
	char		*temp;
	char		*ptr;

	len = ft_count_base(n, base);
	ptr = ft_strnew(len);
	if (ptr == NULL)
		return (NULL);
	temp = ptr;
	while (len > 0)
	{
		if (n % base < 10)
			*(ptr + len - 1) = (n % base + '0');
		else
			*(ptr + len - 1) = (('a' + n % base) - 10);
		n = n / base;
		--len;
	}
	return (temp);
}

void	output_dump2(int j)
{
	char	*num;
	int		i;

	ft_putstr("0x");
	i = 0;
	num = ft_itoa_base(j * 64, 16);
	if (ft_strlen(num) != 4)
	{
		while (ft_strlen(num) + i < 4)
		{
			ft_putstr("0");
			i++;
		}
	}
	ft_putstr(num);
	ft_putstr(" : ");
	free(num);
}

void	output_dump(t_mstruc *ms)
{
	int		i;
	int		j;
	int		k;
	char	*num;

	i = 0;
	j = 0;
	k = 0;
	while (k < MEM_SIZE)
	{
		i = 0;
		output_dump2(j);
		++j;
		while (i < 64 && i < MEM_SIZE)
		{
			num = ft_itoa_memory(ms->memory[k], 16);
			ft_putstr(num);
			ft_putchar(' ');
			free(num);
			++i;
			++k;
		}
		ft_putchar('\n');
	}
}
