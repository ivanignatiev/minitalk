/*
** server.h for minitalk_server in /home/ignati_i//test_c/minitalk/server_src
** 
** Made by ivan ignatiev
** Login   <ignati_i@epitech.net>
** 
** Started on  Sun Nov 18 19:11:13 2012 ivan ignatiev
** Last update Sun Nov 18 20:03:11 2012 ivan ignatiev
*/

#ifndef SERVER_H_
#	define SERVER_H_

#define		BLOCK_SIZE	100

typedef struct s_clients
{
  pid_t		pid;
  char		data[BLOCK_SIZE];
  int		bit_len;
  int		block_count;
  struct s_clients *next;
} t_clients;

t_clients	*g_clients;

void		accept_client(t_clients *client);
t_clients	*add_client(pid_t pid);
t_clients	*find_client(pid_t pid);
void		remove_client(pid_t pid);
void		flush_data(t_clients *client);
void		memclear(char*, int);
int		addbit_to_pid(pid_t pid, int bit);
void		receiver(int signal,
			 siginfo_t *info,
			 void *tmp);
void		exit_signal(int signal);

#endif /* !SERVER_H_ */
