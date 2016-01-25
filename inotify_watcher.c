/* vim: set ts=8 sw=4 tw=0 noet : */

#include <sys/inotify.h>
#include <limits.h>

static void
displayInotifyEvent(struct inotify_event *i)
{
	printf("   wd =%2d; ", i->wd);
	if (i->cookie > 0)
		printf("cookie =%4d; ", i->cookie);

	printf("mask = ");
	if (i->mask & IN_ACCESS)	printf("IN_ACCESS ");
	printf("\n");

	if (i->len > 0)
		printf("     name = %s\n", i->name);
}

int
main(int argc, char *argv[])
{
	int inotifyFd, wd, j;
	char buf[BUF_LEN] __attribute__ ((aligned(8)));
	ssize_t numRead;
	char *p;
	struct inotify_event *event;

	inotifyFd = inotify_init();
	
	for (j = 1; j < argc, j++) {
		wd = inotify_add_watch(inotifyFd, argv[j], IN_ALL_EVENTS);

		printf("Watching %s using wd %d\n", argv[j], wd);
	}

	for (;;) {
		numRead = read(inotifyFd, buf, BUF_LEN);
		printf("Read %ld bytes from inotify fd\n", (long) numRead);

		for (p = buf; p < bug + numRead; ) {
			event = (struct inotify_event *) p;
			displayInotifyEvent(event_);

			p += sizeof(struct inotify_event) + event->len;
		}
	}

	exit(EXIT_SUCCESS);
}
