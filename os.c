#include "kernel/display/display.h"
#include "kernel/drivers/ps2.h"
#include "kernel/core/io.h"
#include "kernel/std/stdio.h"
#include "kernel/std/time.h"
#include "kernel/std/string.h"
#include "kernel/unittest/unittest.h"

string username = 0;

void print_time()
{
	struct time tm;
	gettime(&tm);

	output("%d.%d.%d, %d:%d:%d", tm.day, tm.month, tm.year, tm.hour, tm.minute, tm.second);
}

void set_username(new)
{
	username = 0;
	string untmp = 0;
	if (new == 1)
		output("Please enter your new username: ");
	else
		output("\nPlease enter your username: ");
	
	gets(untmp);
	username = untmp;
	if (new == 1)
		output("Your new username is: %s", username);
	else
		output("Welcome, %s, to NimgOS!", username);
	untmp = 0;
}

void kern_main()
{
	gdt_init();
	display_init();
	PS2_init();
	std_test();

	output("NimgOS started successfully on ");
	print_time();
	set_username();
	output("\nType \"help\" to see all available commands.\nEnter a command:\n");

	string cmd = 0;

	while (true) {
		output("%s> ", username);
		gets(cmd);

		str2lower(cmd);

		if (strcmp(cmd, "help") == 0)
			output("Commands: help - about - credits - clear -  time - restart - todolist");
		else if (strcmp(cmd, "about") == 0)
			output("NimgOS Alpha\nCopyright (c) 2016 Njifra and contributors.\nType \"credits\" to see a list of all contributors.");
		else if (strcmp(cmd, "credits") == 0)
			output("\nThanks to the following people, who contributed to this project:"
			       "\n\tKrock (SmallJoker)"
			       "\n\tZumza (Zumza123)"
			       "\n\txerox123 (xerox123official)"
			       "\n\tF4ncy (xshotD)"
			       "\n\tbulldozer (bulldozer548)"
			       "\n\tNjifra (Njifra)");
		else if (strcmp(cmd, "clear") == 0)
			display_clear();
		else if (strcmp(cmd, "setname") == 0)
			set_username(1);
		else if (strcmp(cmd, "restart") == 0)
			reboot();
		else if (strcmp(cmd, "todolist") == 0)
			output("TODO list:\n\t- fix non-removable CTRL+C\n\t- add scrolling\n\t- add a command manager (no hardcoded commands, please)");
		else if (strcmp(cmd, "setcur") == 0)
			display_set_cursor(10, 10);
		else if (strcmp(cmd, "time") == 0) {
			output("Current time: ");
			print_time();
		}
		else
			write_string("Command not found.");

		output("\n");

		cmd = 0;
	}
}
