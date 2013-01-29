/*
 *      Author:  Jordan Bayles (baylesj), baylesj@engr.orst.edu
 *     Created:  01/27/2013 07:44:06 PM
 *    Filename:  myar.c
 *
 * Description:  Implementation of UNIX archive "ar" utility
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ar.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// use lstat instead of stat!
// almost all code for this project is in textbook
// 71 while numRead read read section is helpful

// must be run before get_next_header
bool check_file(int fd)
{
	char buf[ SARMAG ];

	read (fd, buf, SARMAG);
	assert (strncmp (buf, ARMAG, sizeof (buf)) == 0);

	return (true);
}

// assumes file offset only edited by self and check_file()
// pass in header to get, output offset of contents
off_t get_next_header(int fd, struct ar_hdr *out)
{
	char buf[ sizeof( struct ar_hdr ) ];
	ssize_t was_read;
	off_t content_offset;

	/* Read and make sure we got everything */
	was_read = read (fd, buf, sizeof (struct ar_hdr));
	if (was_read == (sizeof (struct ar_hdr))) {

		/* Try filling the struct with a cast */
		//*out = (struct ar_hdr) buf;
		memcpy (out, buf, sizeof (*out));

		/* Record content offset in case we care */
		content_offset = lseek (fd, 0, SEEK_CUR);

		/* Advance past content */
		lseek (fd, atoi (out->ar_size) + 1, SEEK_CUR);

	} else {
		content_offset = (off_t)(-1);
	}

	return (content_offset);
}

struct stat *get_stats(struct ar_hdr *hdr)
{

	return (NULL);
}

bool add_file(int fd, struct ar_hdr *hdr, char *contents)
{

	return (true);
}

bool delete_file(int fd, struct ar_hdr *hdr)
{

	return (true);
}

bool extract_file(int fd, struct ar_hdr *hdr)
{

	return (true);
}

bool print_concise (int fd)
{
	struct ar_hdr *tmp = malloc (sizeof (struct ar_hdr));

	if (check_file (fd)) {
		while (get_next_header(fd, tmp) != -1) {
			printf ("-%s-", (char *)tmp);
			//printf ("%.*s", (int)(sizeof (tmp->ar_name)), tmp->ar_name);

		}
	}
	// To print non null terminated:
	// printf("%.*s", length, string);
	return (true);
}

bool print_verbose (int fd)
{

	return (true);
}

int main(int argc, char **argv)
{
	char *archive;
	int fd;
	char key;

	/* Syntax "myar key afile name ..." where afile=archive, key=opt */
	assert(argc >= 3);
	assert(strlen(argv[1]) == 2);

	assert(argv[1][0] == '-');

	/* operation key */
	key = argv[1][1];

	/* archive should be second argument */
	archive = argv[2];

	/* open archive */
	fd = open (archive, O_RDWR);

	switch (key) {
	case 'q':		// quickly append named files to archive

		break;
	case 'x':		// extract named files

		break;
	case 't':		// print a concise table of contents of archive
		print_concise (fd);
		break;
	case 'v':		// print a verbose table of contents of archive
		print_verbose (fd);
		break;
	case 'd':		// delete named files from archive

		break;
	case 'A':		// quickly append all "regular" files in the current dir

		break;
	case 'w':		// for a timeout, add all modified files to the archive

		break;
	default:		// unsupported operation

		break;
	}

	return (EXIT_SUCCESS);
}
