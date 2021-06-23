#include "includes/utils.h"
#include <readline/readline.h>

void	passe_non_canonique(struct termios *old, struct termios *new)
{
	tcgetattr(0, old);
	bzero(new, sizeof(*new));
	new->c_cflag = CREAD;
	new->c_iflag = IGNPAR | ICRNL;
	new->c_oflag = 0;
	new->c_lflag = 0;
	new->c_cc[VMIN] = 1;
	new->c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, new);
}

int main()
{
	struct termios old;
	struct termios new;
	char *str;
	passe_non_canonique(&old, &new);
	str = readline("$> ");
	tcsetattr(0, TCSANOW, &old);
}
