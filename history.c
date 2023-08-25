#include "shell.h"

/**
 * write_history - Writes the history list to the history file.
 * @info: Pointer to the info_t struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644); /* Open for writing */
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd); /* Write each history entry to the file */
		_putfd('\n', fd); /* Add a newline after each entry */
	}
	_putfd(BUF_FLUSH, fd); /* Flush the output buffer */
	close(fd);
	return (1);
}

/**
 * read_history - Reads the history from the history file.
 * @info: Pointer to the info_t struct.
 *
 * Return: The number of history entries read, 0 on failure.
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY); /* Open history file for reading */
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize); /* Read the contents of the history file */
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++); /* Build list */
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX) /* Trim list to HIST_MAX entries */
		delete_node_at_index(&(info->history), 0);
	renumber_history(info); /* Renumber the history entries */
	return (info->histcount);
}

/**
 * build_history_list - Adds an entry to the history linked list.
 * @info: Pointer to the info_t struct.
 * @buf: Buffer containing the history entry.
 * @linecount: Line count of the history entry.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount); /* Adding entry to the linked list */

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Renumber the history linked list after changes.
 * @info: Pointer to the info_t struct.
 *
 * Return: The new histcount (number of history entries).
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++; /* Renumber the history entries */
		node = node->next;
	}
	return (info->histcount = i); /* Update the histcount */
}

/**
 * get_history_file - Generates the path to the history file.
 * @info: Pointer to the info_t struct.
 *
 * Return: Allocated string containing history file path, or NULL on failure.
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME="); /* Get the HOME directory from the enviro. */
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE); /* Concat the HOME directory and history file name */
	return (buf);
}
