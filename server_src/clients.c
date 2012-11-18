/*
** clients.c for minitalk_server in /home/ignati_i//test_c/minitalk/server_src
** 
** Made by ivan ignatiev
** Login   <ignati_i@epitech.net>
** 
** Started on  Sun Nov 18 19:13:29 2012 ivan ignatiev
** Last update Sun Nov 18 20:03:32 2012 ivan ignatiev
*/

#include	<stdlib.h>
#include	<signal.h>
#include	"server.h"
#include	"stringmy.h"

void		accept_client(t_clients *client)
{
  if (client != NULL)
    {
      if (g_clients != NULL)
	client->next = g_clients;
      g_clients = client;
    }
}

t_clients	*add_client(pid_t pid)
{
  t_clients	*client;

  my_putstr("Added new client ");
  my_put_nbr(pid);
  my_putstr("\n");
  client = (t_clients*)malloc(sizeof(t_clients));
  if (client != NULL)
    {
      client->pid = pid;
      client->bit_len = 0;
      client->next = NULL;
      client->block_count = 0;
      memclear(client->data, BLOCK_SIZE);
    }
  accept_client(client);
  return (client);
}

t_clients	*find_client(pid_t pid)
{
  t_clients	*nav;

  nav = g_clients;
  while (nav)
    {
      if (nav->pid == pid)
	return (nav);
      nav = nav->next;
    }
  return (add_client(pid));
}

void		remove_client(pid_t pid)
{
  t_clients	*nav;
  t_clients	*tmp;

  my_putstr("Client ");
  my_put_nbr(pid);
  my_putstr(" disconnected\n");
  nav = g_clients;
  if (nav->pid == pid)
    {
      tmp = g_clients;
      g_clients = g_clients->next;
      free(tmp);
      return ;
    }
  while (nav->next && nav->next->pid != pid);
  tmp = nav->next;
  nav->next = nav->next->next;
  free(tmp);
}

void		flush_data(t_clients *client)
{
  my_putstr("Receive block ");
  my_put_nbr(client->block_count);
  my_putstr(" of data from PID ");
  my_put_nbr(client->pid);
  my_putstr(" : '");
  my_putstr(client->data);
  my_putstr("'\n");
  memclear(client->data, BLOCK_SIZE);
  client->bit_len = 0;
  ++client->block_count;
}
