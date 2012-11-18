/*
** main.c<2> for minitalk_client in /home/ignati_i//test_c/minitalk
** 
** Made by ivan ignatiev
** Login   <ignati_i@epitech.net>
** 
** Started on  Mon Nov 12 14:28:30 2012 ivan ignatiev
** Last update Sun Nov 18 20:27:35 2012 ivan ignatiev
*/

#include	<stdlib.h>
#include	<sys/types.h>
#include	<unistd.h>
#include	<signal.h>
#include	"stringmy.h"

int		sendchar(pid_t server_pid, char c)
{
  int		bit;
  int		signal;

  bit = (sizeof(char) * 8) - 1;
  while (bit >= 0 )
    {
      if (((c >> bit) & 1) == 1)
	signal = SIGUSR1;
      else
	signal = SIGUSR2;
      if (kill(server_pid, signal) != 0)
	{
	  my_puterror("client: I can't send message.\n");
	  return (0);
	}
      pause();
      --bit;
    }
  return (1);
}

int		sendmessage(pid_t server_pid,
			    char *message)
{
  int		i;

  my_putstr("Trying send message to ");
  my_put_nbr(server_pid);
  my_putstr("\n");
  i = 0;
  while (message[i] != '\0')
    {
      if (!sendchar(server_pid, message[i]))
	return (EXIT_FAILURE);
      ++i;
    }
  sendchar(server_pid, '\0');
  my_putstr("Message sended: ");
  my_putstr(message);
  my_putstr("\n");
  return (EXIT_SUCCESS);
}

void		receiver(int  signal)
{
  if (signal)
    {
    }
}

int		flush_server_random(pid_t server_pid)
{
  unsigned int	c;

  while (1)
    {
      sendchar(server_pid, (c % 26 + 'a'));
      if (c % 1000 == 0)
	my_putstr("I Sended 1000\n");
      c = c + 1;
    }
  return (EXIT_SUCCESS);
}

int		main(int argc, char **argv)
{
  pid_t		server_pid;

  if (argc > 1)
    {
      signal(SIGUSR1, receiver);
      server_pid = (pid_t)my_getnbr(argv[1]);
      if (server_pid < 1)
	{
	  my_puterror("client: Server PID incorrect.\n");
	  return (EXIT_FAILURE);
	}
      my_putstr("My PID: ");
      my_put_nbr(getpid());
      my_putstr("\n");
      if (argc > 2)
	return (sendmessage(server_pid, argv[2]));
      else
	return (flush_server_random(server_pid));
    }
  else
    my_puterror("client: Too few arguments.\n");
  return (EXIT_SUCCESS);
}
