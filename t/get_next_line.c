#include "../tap.h"
#include "../get_next_line.h"

#include <fcntl.h>		// provides open()
#include <unistd.h>		// provides read() and lseek()
#include <string.h>

int	main(void)
{
	plan(23245);

	/* 2MB buffer to fit the entire file */
	char buf[2000000] = { 0 };
	char *line;
	size_t i;
	size_t ofst;

	int fd = open("t/moby10b.txt", O_RDONLY);
	ssize_t rd = read(fd, buf, sizeof(buf));

	lseek(fd, 0, SEEK_SET);

	i = 0;
	for (int x = 1; x < 23245; ++x)
	{
		line = get_next_line(fd);
		ofst = strcspn(&buf[i], "\n");
		cmp_mem(line, &buf[i], ofst + 1, "Read %zu bytes at line %d", ofst + 1, x);
		i += ofst + 1;
	}
	cmp_mem(get_next_line(fd), NULL, 0, "Read 0 bytes at EOF");

	done_testing();
}
