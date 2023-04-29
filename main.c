/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:05:51 by rficht            #+#    #+#             */
/*   Updated: 2023/04/29 15:27:50 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../Includes/minishell.h"
 
/* Restore terminal to original settings
*/
static int terminal_reset(t_program *program)
{
    if (program->term_fd != -1)
	{
        if(tcsetattr(program->term_fd, TCSANOW, &program->term_original))
			return errno = ENOTSUP;
	}
	return errno = 0;
}
 

/* Initialize terminal for non-canonical, non-echo mode,
 * that should be compatible with standard C I/O.
 * Returns 0 if success, nonzero errno otherwise.
*/
static int terminal_init(t_program *program)
{

	/* Already initialized? */
	if (program->term_fd != -1)
		return (errno = 0);

	/* Which standard stream is connected to our TTY? */
	if (isatty(STDERR_FILENO))
		program->term_fd = STDERR_FILENO;
	else if (isatty(STDIN_FILENO))
		program->term_fd = STDIN_FILENO;
	else if (isatty(STDOUT_FILENO))
		program->term_fd = STDOUT_FILENO;
	else
		return (errno = ENOTTY);

	/* Obtain terminal settings. */
	if (tcgetattr(program->term_fd, &program->term_original) ||
		tcgetattr(program->term_fd, &program->term_settings))
		return errno = ENOTSUP;


	/* Let BREAK cause a SIGINT in input. */
	program->term_settings.c_iflag &= ~IGNBRK;
	program->term_settings.c_iflag |=  BRKINT;

	/* Ignore framing and parity errors in input. */
	program->term_settings.c_iflag |=  IGNPAR;
	program->term_settings.c_iflag &= ~PARMRK;

	/* Do not strip eighth bit on input. */
	program->term_settings.c_iflag &= ~ISTRIP;

	/* Do not do newline translation on input. */
	program->term_settings.c_iflag &= ~(INLCR | IGNCR | ICRNL);

	#ifdef IUCLC
	/* Do not do uppercase-to-lowercase mapping on input. */
	program->term_settings.c_iflag &= ~IUCLC;
	#endif

	/* Use 8-bit characters. This too may affect standard streams,
		* but any sane C library can deal with 8-bit characters. */
	program->term_settings.c_cflag &= ~CSIZE;
	program->term_settings.c_cflag &= ~CS8;

	/* Enable receiver. */
	program->term_settings.c_cflag |=  CREAD;

	/* Let INTR/QUIT/SUSP/DSUSP generate the corresponding signals. */
	program->term_settings.c_lflag |=  ISIG;

	/* Enable noncanonical mode.
		* This is the most important bit, as it disables line buffering etc. */
	program->term_settings.c_lflag |= ICANON;

	/* Disable echoing input characters. */
	program->term_settings.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);

	/* Disable implementation-defined input processing. */
	program->term_settings.c_lflag &= ~IEXTEN;

	/* To maintain best compatibility with normal behaviour of terminals,
		* we set TIME=0 and MAX=1 in noncanonical mode. This means that
		* read() will block until at least one byte is available. */
	/*program->term_settings.c_cc[VTIME] = 0;
	program->term_settings.c_cc[VMIN] = 1;*/

	/* Set the new terminal settings.
		* Note that we don't actually check which ones were successfully
		* set and which not, because there isn't much we can do about it. */
	tcsetattr(program->term_fd, TCSANOW, &program->term_settings);

	/* Done. */
	return errno = 0;
}

void on_new_line(t_program *program)
{
	(void) program;

	write(1, "minishell >$", 13);
}

int main(void)
{
	t_program program;
	const char *line;


	if (terminal_init(&program))
	{
		if (errno == ENOTTY)
			fprintf(stderr, "This program requires a terminal.\n");
		else
			fprintf(stderr, "Cannot initialize terminal: %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}

	write(1, "Press CTRL+C to quit\n", 22);
	while (1)
	{
		line = readline(" ~ ");
		printf("%s\n", line);
	}

	/* At exit() or return from main(),
		* restore the original settings. */
	if (terminal_reset(&program))
		return errno = ENOTSUP;

	printf("Done.\n");

	return EXIT_SUCCESS;
}