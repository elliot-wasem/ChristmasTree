/**
 * @Author: Elliot Wasem
 * @Github: http://github.com/elliot-wasem
 * This project: http://github.com/elliot-wasem/ChristmasTree
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>

// quick color definitions, for ease of use.
// colors declared inside main
#define GREEN  1
#define RED    2
#define BLUE   3
#define YELLOW 4
#define WHITE  5
#define NEEDLE_CHAR "^"

// usage message, for ease of use, so that it is uniform whenever produced
#define USAGE  "\nUsage: christmas [options]\n\noptions:\n\t-t/--time <time> -- \
time in milliseconds between each tick of the program. Default 150\n"

// method declarations, to avoid order of operations issues
void draw_tree();
void print_point();
void print_point_large();
void draw_snowflakes();

// simple point struct so that snowflakes can easily be kept track of
struct flake {
    int y;
    int x;
};

int main(int argc, char *argv[])
{
    /* time is used to set the delay between each iteration */
    char *end;
    char c;
    int i, max_y, max_x, reset_index, time;

    time = 150;

    /* input parsing */
    for(i = 1; i < argc; i++) {
	/* if an argument is either "-h" or "--help", display usage and exit */
	if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
	    printf(USAGE);
	    return EXIT_SUCCESS;
	}

	/*
	 * if an argument is either "-t" or "--time", check if there is a
	 * valid integer argument immediately following it, and if not,
	 * display error message
	 */
	else if (!strcmp(argv[i], "-t") || !strcmp(argv[i], "--time")) {
	    if(argv[i + 1] == NULL) {
		printf("Option \"%s\" must have a valid integer argument.\n",
		       argv[i]);
		return EXIT_FAILURE;
	    }
	    time = strtol(argv[i+1], &end, 10);
	    if(end[0] != '\0') {
		printf("Bad argument \"%s\" for option \"%s\".\nOption \"%s\" \
must have a valid integer argument.\n", argv[i + 1], argv[i], argv[i]);
		return EXIT_FAILURE;
	    }
	    i++;
	}

	/* if invalid, print error message */
	else {
	    printf("Argument \"%s\" not recognized.\n", argv[i]);
	    printf(USAGE);
	    return EXIT_FAILURE;
	}
    }

    /* initialize screen */
    initscr();

    /* enables colors */
    start_color();

    /* initially refreshes screen, emptying it */
    refresh();

    /* keypresses will not be displayed on screen */
    noecho();

    /* 
     * sets getch timeout (and I assume other hanging operations' timeouts, but 
     * I haven't confirmed that). This is used for the timing functionality
     */
    timeout(time);

    /* sets color pairs to numbers defined above */
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);

    /*
     * listens for input, so that the main loop can listen for the user hitting
     * 'q' to quit 
     */
    c = '0';

    /* stores the maximum y and x coordinates of the screen at the time. */
    getmaxyx(stdscr, max_y, max_x);

    /*
     * stores each snowflake, with exactly one per incremental x coordinate from
     * 0 to max_x 
     */
    struct flake flakes[max_x];

    /* 
     * fills snowflakes with initial positions, such that the y-coordinate is 
     * random, and the x-coordinate is iterative 
     */
    for(i = 0; i < max_x; i++) {
	flakes[i].x = i;
	flakes[i].y = rand() % max_y - 5;
    }

    /* 
     * reset_index is used to randomly select 1 snowflake and set its 
     * y-coordinate to 0. this allows for gentle snowfall throughout 
     * the execution of the program. 
     */
    reset_index = rand() % max_x;

    /* 
     * c is used to store user input, so the while-loop listens for the user to 
     * press 'q', indicating the user wishes to terminate the program. 
     */
    while(c != 'q'){

	/* overwrites all characters on screen with blanks */
	erase();

	/* calls draw_snowflakes(), which will give the appearance of snowing */
	draw_snowflakes(flakes, max_x, reset_index);

	/* draws the tree, flashing lights and all */
	draw_tree();

	/* picks a new reset_index for next call to draw_snowflakes(). */
	reset_index = rand() % max_x;

	/* updates the display */
	refresh();

	/* hangs for 'time' in milliseconds */
	c = getch();
    }

    /* terminates the ncurses window */
    endwin();
    return EXIT_SUCCESS;
}

/**
 * This function is responsible for drawing the tree on-screen
 */
void draw_tree()
{
    /* 
     * this function is a bunch of very specific mathematical mumbo jumbo.
     * read through carefully to get an idea of what's going on
     *
     * row is the row we're on, col is the number of columns of tree expected 
     *     in a row, measured from center of tree to extremities.
     *
     * stars is the number of stars in a row
     *
     * max_y/max_x are the maximum screen coordinates. 
     */
    int cur_y, row, col, stars, max_y = 0, max_x = 0;

    /* get current screen coordinates */
    getmaxyx(stdscr, max_y, max_x);

    /* subtract 5 from max_y just for spacing */
    max_y -= 5;

    /* 
     * initially sets row to -3, math just seems to work out better. I didn't 
     * feel like refactoring that. I believe it was because I just wanted to add 
     * 3 rows to the bottom without changing the values everywhere. 
     */
    row = -3;

    /* initially should be 21 columns from center of tree to tips of rows */
    col = 21;

    /* starts with 43 stars */
    stars = 43;

    /* 
     * from here to the 'if' statement, we are just drawing out the trunk and 
     * presents. mostly just hardcoding. 
     */
    move(max_y - row - 1, max_x / 2 - 8);

    /* 
     * this method prints a string to the window. like 'printf()' but prints to 
     * stdscr 
     */
    printw("> Press q to quit <");
    row += 3;

    /* this turns a certain color attribute on. */
    attron(COLOR_PAIR(GREEN));

    /* 
     * this statement moves the cursor to the coordinates defined in the 
     * arguments 
     */
    move(max_y - row, max_x / 2 - 2);
    printw("*****");

    /* and this turns it off */
    attroff(COLOR_PAIR(GREEN));
    attron(COLOR_PAIR(RED));
    printw("   ##");
    attroff(COLOR_PAIR(RED));
    attron(COLOR_PAIR(WHITE));
    printw("#");
    attroff(COLOR_PAIR(WHITE));
    attron(COLOR_PAIR(RED));
    printw("##");
    attroff(COLOR_PAIR(RED));
    attron(COLOR_PAIR(BLUE));
    printw(" ###");
    attroff(COLOR_PAIR(BLUE));
    attron(COLOR_PAIR(WHITE));
    printw("#");
    attroff(COLOR_PAIR(WHITE));
    attron(COLOR_PAIR(BLUE));
    printw("###");
    attroff(COLOR_PAIR(BLUE));
    row++;

    move(max_y - row, max_x / 2 - 2);
    attron(COLOR_PAIR(GREEN));
    printw("*****");
    attroff(COLOR_PAIR(GREEN));
    attron(COLOR_PAIR(RED));
    printw("   ##");
    attroff(COLOR_PAIR(RED));
    attron(COLOR_PAIR(WHITE));
    printw("#");
    attroff(COLOR_PAIR(WHITE));
    attron(COLOR_PAIR(RED));
    printw("##");
    attroff(COLOR_PAIR(RED));
    attron(COLOR_PAIR(WHITE));
    printw(" #######");
    attroff(COLOR_PAIR(WHITE));
    row++;

    move(max_y - row, max_x / 2 - 19);
    printw("HAPPY NEW YEAR   ");
    attron(COLOR_PAIR(GREEN));
    printw("*****");
    attroff(COLOR_PAIR(GREEN));
    attron(COLOR_PAIR(WHITE));
    printw("   #####");
    attroff(COLOR_PAIR(WHITE));
    attron(COLOR_PAIR(BLUE));
    printw(" ###");
    attroff(COLOR_PAIR(BLUE));
    attron(COLOR_PAIR(WHITE));
    printw("#");
    attroff(COLOR_PAIR(WHITE));
    attron(COLOR_PAIR(BLUE));
    printw("###");
    attroff(COLOR_PAIR(BLUE));
    row++;

  
    move(max_y - row, max_x / 2 - 15);
    printw("AND A        ");
    attron(COLOR_PAIR(GREEN));
    printw("*****");
    attroff(COLOR_PAIR(GREEN));
    attron(COLOR_PAIR(RED));
    printw("   ##");
    attroff(COLOR_PAIR(RED));
    attron(COLOR_PAIR(WHITE));
    printw("#");
    attroff(COLOR_PAIR(WHITE));
    attron(COLOR_PAIR(RED));
    printw("##");
    attroff(COLOR_PAIR(RED));
    row++;

    move(max_y - row, max_x / 2 - 19);
    printw("MERRY CHRISTMAS  ");
    attron(COLOR_PAIR(GREEN));
    printw("*****");
    attroff(COLOR_PAIR(GREEN));
    attron(COLOR_PAIR(RED));
    printw("   ##");
    attroff(COLOR_PAIR(RED));
    attron(COLOR_PAIR(WHITE));
    printw("#");
    attroff(COLOR_PAIR(WHITE));
    attron(COLOR_PAIR(RED));
    printw("##");
    attroff(COLOR_PAIR(RED));
    attron(COLOR_PAIR(GREEN));
    row++;
    attron(COLOR_PAIR(GREEN));

    move(max_y - row, max_x / 2 - 2);
    printw("*****");
    row++;

    cur_y = 0;
    getmaxyx(stdscr, cur_y, max_x);

    /* 
     * checks bounds of the screen and draws a small, medium, or large tree 
     * respectively 
     */
    if(cur_y < 32 || max_x <= 42) {
	/* 
	 * small tree, so sets stars to 21 and cols to 10, then draws a little 
	 * triangular tree 
	 */
	stars = 21;
	col = 10;
	while(col >= 0) {
	    move(max_y - row, max_x / 2 - col);
	    print_point(stars);
	    col--;
	    row++;
	    stars -= 2;
	}
    } else if(cur_y < 38) {
	/* medium tree, so draws a medium triangular tree */
	while(col >= 0) {
	    move(max_y - row, max_x / 2 - col);
	    print_point(stars);
	    col--;
	    row++;
	    stars -= 2;
	}
    } else {
	/* large tree, so draws a large complex tree */
	while(col > 3) {
	    move(max_y - row, max_x / 2 - col);
	    print_point_large(stars);
	    col-= 2;
	    row++;
	    stars -= 4;

	    move(max_y - row, max_x / 2 - col);
	    print_point_large(stars);
	    col -= 2;
	    row++;
	    stars -= 4;

	    move(max_y - row, max_x / 2 - col);
	    print_point_large(stars);
	    col += 2;
	    row++;
	    stars += 4;
	}
	move(max_y - row, max_x / 2);
	print_point(1);
	move(0, 0);
    }
    move(max_y+4, max_x / 2 - 18);
    printw("github.com/elliot-wasem/ChristmasTree");
}

/**
 * recursive function to print points from start position onward until num_reps 
 * is depleted
 */
void print_point(int num_reps) {
    /*
     * chooses a random number, then subtracts 45 from it.
     * if it is below 1, it prints a light.
     * otherwise, it prints a tree star. 
     */
    int color = rand() % 50;
    color -= 45;
    if(color <= 0) {
	color = 0;
    }
    attron(COLOR_PAIR(color + 1));
    if(color)
	printw("o");
    else
	printw(NEEDLE_CHAR);
    attroff(COLOR_PAIR(color + 1));
    if(num_reps > 1)
	print_point(num_reps - 1);
}

void print_point_large(int num_reps)
{
    /*
     * for the large tree, it draws lights deterministically,
     * and instead picks a random color each time a light is drawn 
     */
    int color = rand() % 4 + 2;
    if(!((num_reps + 2) % 6)) {
	attron(COLOR_PAIR(color));
	printw("o");
	attroff(COLOR_PAIR(color));
    } else {
	color = 1;
	attron(COLOR_PAIR(color));
	printw(NEEDLE_CHAR);
	attroff(COLOR_PAIR(color));
    }
    if(num_reps > 1)
	print_point_large(num_reps - 1);
}

void draw_snowflakes(struct flake flakes[], int len, int reset_index)
{
    int max_y = 0, max_x = 0;
    getmaxyx(stdscr, max_y, max_x);
    for(int i = 0; i < len; i++) {
	int random = rand() % 3;
	mvprintw(flakes[i].y,
		 flakes[i].x,
		 (random == 2 ? "*" : (random == 1 ? "+" : "x")));
	if(flakes[i].y < max_y - 5)
	    flakes[i].y++;
    }
    flakes[reset_index].y = 0;
}
