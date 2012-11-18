/*
** signals.c for minitalk_server in /home/ignati_i//test_c/minitalk
** 
** Made by ivan ignatiev
** Login   <ignati_i@epitech.net>
** 
** Started on  Sun Nov 18 19:53:10 2012 ivan ignatiev
** Last update Sun Nov 18 20:26:13 2012 ivan ignatiev
*/

#include	<stdlib.h>
#include	<signal.h>
#include	"stringmy.h"
#include	"server.h"

int		addbit_to_pid(pid_t pid, int bit)
{
  t_clients	*client;
  int		len;

  if ((client = find_client(pid)) != NULL)
    {
      len = (client->bit_len / (sizeof(char) * 8));
      if (len >= BLOCK_SIZE)
	{
	  client->data[len] = '\0';
	  flush_data(client);
	}
      client->data[len] = ((client->data[len] << 1) | bit);
      ++client->bit_len;
      if ((client->bit_len % (sizeof(char) * 8)) == 0
	  && client->data[len] == '\0')
	flush_data(client);
      return (1);
    }
  return (0);
}

void		receiver(int signal,
			 siginfo_t *info,
			 void *tmp)
{
  if (info != NULL && tmp != NULL)
    {
      if (!addbit_to_pid(info->si_pid, signal == SIGUSR1))
	my_puterror("server: Message crashed.\n");
    }
}

void		exit_signal(int signal)
{
  t_clients	*tmp;

  if (signal == SIGINT)
    {
      if (g_clients)
      while (g_clients)
	{
	  my_put_nbr(g_clients->pid);
	  tmp = g_clients;
	  g_clients = g_clients->next;
	  free(tmp);
	}
      exit(0);
    }
}
