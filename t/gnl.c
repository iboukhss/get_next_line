#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line.h"
#include "../tap.h"

extern char	buf[BUFFER_SIZE];
extern size_t total_bytes_read;
extern size_t bytes_consumed;

int	main(void)
{
	plan (2);

	int		fd;
	char	*nl;

	fd = open("t/testme.txt", O_RDONLY);

	nl = get_next_line(fd);
	cmp_mem(nl, "this is a test\n", 16);
	// check remaining buffer
	cmp_mem(buf, "this is another t", 18);

	for (int i = 0; i < 32; ++i)
	{
		printf("buf[%d]:  %c\n", i, buf[i]);
	}

	printf("bytes_read: %zu\nbytes_consumed: %zu\n", total_bytes_read, bytes_consumed);

	nl = get_next_line(fd);
	cmp_mem(nl, "this is another test\n", 22);

	printf("bytes_read: %zu\nbytes_consumed: %zu\n", total_bytes_read, bytes_consumed);

	done_testing();
}
