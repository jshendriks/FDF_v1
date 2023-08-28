/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_atoi.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 12:50:13 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/08/28 14:33:09 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static int	st_rec_atoi(const char *str, int nb, int sgn, int *flw);

static int	st_process_cdigit(const char *str, int nb, int sgn, int *flw)
{	
	if (sgn == 1 || sgn == 0)
	{
		if (nb * 10 + (*str - '0') < 0)
		{
			*flw = 0;
			return (nb);
		}
		return (st_rec_atoi(str + 1, nb * 10 + (*str - '0'), 1, flw));
	}
	else if (nb * 10 - (*str - '0') > 0)
	{
		*flw = 0;
		return (nb);
	}
	return (st_rec_atoi(str + 1, nb * 10 - (*str - '0'), sgn, flw));
}

static int	st_rec_atoi(const char *str, int nb, int sgn, int *flw)
{
	if (*str == '\0')
		return (nb);
	else if (*str == '-' || *str == '+')
	{
		if (*str == '-' && sgn == 0)
			return (st_rec_atoi(str + 1, nb, -1, flw));
		else if (*str == '+' && sgn == 0)
			return (st_rec_atoi(str + 1, nb, 1, flw));
		else
			return (nb);
	}
	else if (*str >= '0' && *str <= '9')
		return (st_process_cdigit(str, nb, sgn, flw));
	else
		return (nb);
}

int	fdf_atoi_overflw(const char *str, int *ptr_num)
{
	int	nb;
	int	flw;
	int	*ptr_flw;

	flw = 1;
	ptr_flw = &flw;
	if (str == NULL)
		return (0);
	nb = st_rec_atoi(str, 0, 0, ptr_flw);
	*ptr_num = nb;
	return (flw);
}
