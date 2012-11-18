/*
** main.c for minitalk_server in /home/ignati_i//test_c/minitalk
** 
** Made by ivan ignatiev
** Login   <ignati_i@epitech.net>
** 
** Started on  Mon Nov 12 14:27:49 2012 ivan ignatiev
** Last update Sun Nov 18 20:04:12 2012 ivan ignatiev
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<unistd.h>
#include	<signal.h>
#include	"stringmy.h"
#include	"server.h"

void		memclear(char *message, int len)
{
  int		i;

  i = 0;
  while (i < len)
    {
      message[i] = 0;
      ++i;
    }
}

void		listen_server()
{
  t_clients	*nav;
  unsigned int	status;
  unsigned int	i;

  status = 0;
  while (1)
    {
      usleep(200);
      nav = g_clients;
      i = 0;
      while (nav)
	{
	  if (i == status)
	  if (kill(nav->pid, SIGUSR1) != 0)
	    remove_client(nav->pid);
	  nav = nav->next;
	  i = i + 1;
	}
      if (i)
	status = (status + 1) % i;
    }
}

int		main()
{
  pid_t			server_pid;
  struct sigaction	action;

  action.sa_sigaction = receiver;
  action.sa_flags = SA_SIGINFO | SA_ONSTACK;
  g_clients = NULL;
  if (sigaction(SIGUSR1, &action, NULL) == 0 &&
      sigaction(SIGUSR2, &action, NULL) == 0 &&
      signal(SIGINT, exit_signal) == 0)
    {
      server_pid = getpid();
      my_putstr("Server started: ");
      my_put_nbr((int)server_pid);
      my_putstr("\n");
      listen_server();
      return (0);
    }
  else
    my_puterror("Server start failed.\n");
  return (1);
}
