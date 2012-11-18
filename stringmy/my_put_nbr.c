/*
** my_put_nbr.c for my_put_nbr in /home/ignati_i//test_c
** 
** Made by ivan ignatiev
** Login   <ignati_i@epitech.net>
** 
** Started on  Wed Oct  3 15:09:06 2012 ivan ignatiev
** Last update Sun Nov 18 20:32:18 2012 ivan ignatiev
*/

#include	"stringmy.h"

long		my_nbr_get_power(int nb)
{
  long		power;
  int		number;

  number = nb;
  power = 1;
  while (number > 0)
    {
      number = number / 10;
      power *= 10;
    }
  return (power / 10);
}

void		my_put_nbr(int nb)
{
  int		number;
  int		digit;
  long		power;

  number = nb;
  if (number < 0)
    {
      my_putchar('-');
      number = -number;
    }
  else if (number == 0)
    {
      my_putchar('0');
      return ;
    }
  power = my_nbr_get_power(number);
  while (power > 0)
    {
      digit = (number / power) % 10;
      my_putchar('0' + digit);
      power /= 10;
    }
}
