// Created by Zhao Qi‘ao on 2022/11/15.
//
#include <user.h>
#include <netdb.h>
#include <socket.h>
#include <inet.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf(2, "Usage nslookup [-option] [name | -] [server]\n");
		return -1;
	}
	char *hostname = argv[1];

	struct hostent *hptr;
	if (!(hptr = (struct hostent *)gethostbyname(hostname)))
	{
		printf(2, "Cannot query name %s\n", hostname);
		return -1;
	}
	printf(1, "HOST NAME: %s\n", hptr->h_name);
	char **p_alias = hptr->h_aliases;
	char **p_addr = hptr->h_addr_list;
	while (*p_alias)
	{
		printf(1, "ALIAS: %s\n", *p_alias);
		p_alias++;
	}
	while (*p_addr)
	{
		if (hptr->h_addrtype == AF_INET)
		{
			printf(1, "ADDR: %s\n", inet_ntoa(*(struct in_addr *)*p_addr));
			p_addr++;
		}
		else
		{
			printf(2, "Unknown address type\n");
		}
	}
	return 0;
}