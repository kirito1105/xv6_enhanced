//
// Created by bear on 10/31/2022.
//
#include "types.h"
#include "user.h"
#include "socket.h"

int
main(int argc, char *argv[])
{
	int soc, acc, peerlen, ret;
	struct sockaddr_in self, peer;
	unsigned char *addr;
	char buf[2048];

	printf(1, "Starting TCP Echo Server\n");
	soc = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (soc <= 1)
	{
		printf(1, "socket: failure\n");
		exit(-1);
	}
	printf(1, "socket: success, soc=%d\n", soc);
	self.sin_family = AF_INET;
	self.sin_addr.addr = INADDR_ANY;
	self.sin_port = hton16(7);
	int err = bind(soc, (struct sockaddr *)&self, sizeof(self));
	if (err != 0)
	{
		printf(1, "bind: failure\n");
		close(soc);
		exit(err);
	}
	addr = (unsigned char *)&self.sin_addr;
	printf(1, "bind: success, self=%d.%d.%d.%d:%d\n", addr[0], addr[1], addr[2], addr[3], ntoh16(self.sin_port));
	listen(soc, 100);
	printf(1, "waiting for connection...\n");
	peerlen = sizeof(peer);
	acc = accept(soc, (struct sockaddr *)&peer, &peerlen);
	if (acc != 0)
	{
		printf(1, "accept: failure\n");
		close(soc);
		exit(acc);
	}
	addr = (unsigned char *)&peer.sin_addr;
	printf(1, "accept: success, peer=%d.%d.%d.%d:%d\n", addr[0], addr[1], addr[2], addr[3], ntoh16(peer.sin_port));
	while (1)
	{
		ret = recv(acc, buf, sizeof(buf));
		if (ret <= 0)
		{
			printf(1, "EOF\n");
			break;
		}
		printf(1, "recv: %d bytes data received\n", ret);
		hexdump(buf, ret);
		send(acc, buf, ret);
	}
	close(soc);
	return 0;
}