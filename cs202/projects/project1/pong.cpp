#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


// functions 
void finish(int sig);
void moveBat(int c, int maxy, char batChar);
void printBat(int y, int x, char bc);
void moveBall(int maxy, int maxx, char bc);
int  checkCollisions(int y, int x, int by, int bx);
int  checkBatCollision(int ry, int rx, int by, int bx);
void updateScore();
int  checkEqualPosition(int y1, int x1, int y2, int x2);
int  checkQuit(int c);
int  isBatBelowBottom(int maxy);
int  isBatAboveTop();
void bounceBall();
int  isOutOfBounds(int pos, int low, int high);
void printStats(int maxy, int maxx);
int  isCorrect(int maxy, int maxx);
int  computeScore(int hits, int whiffs);

//ball related storage
double speedx, speedy;    // global variables for ball speed in x and y directions
double ballPositionY;     // initial location of ball
double ballPositionX;

//bat related storage
double batVelocityX, batVelocityY;
double batVelocityChange;
double batPositionX, batPositionY;

//score related storage
int    hits = 0;
int    whiffs = 0;
int    score = 0;

//statistics
unsigned long int numberOfIterations = 0;
FILE *fp;
int paused;

void initialize(){

   fp = fopen("Grading.data", "w");
   if (fp == NULL){
     fprintf(stderr, "Cannot open grading file for writing\n Exiting....\n");
     exit(1);
   }
   paused = 0;            // paused is false

   //initialize terminal graphics
   (void) initscr();      /* initialize the curses library */
   start_color();
   keypad(stdscr, TRUE);  /* enable keyboard mapping */
   (void) nonl();         /* tell curses not to do NL->CR/NL on output */
   (void) cbreak();       /* take input chars one at a time, no wait for \n */
   (void) noecho();       /* don't echo input */
   nodelay(stdscr, TRUE); /* modify getch() for nonblocking reads */
   init_pair(1, COLOR_CYAN, COLOR_BLACK);
   init_pair(2, COLOR_YELLOW, COLOR_WHITE);

   //initialize game global variables
   speedx = 0.0001;        // initial speeds in x and y direction, adjust this for your HW
   speedy = 0.00005;       // adjust this to change game difficulty
   batVelocityX = 0.0;
   batVelocityY = 0.0001;
   batVelocityChange = 0.00005;

   return;
}	

void printWelcomeScreen(int maxy, int maxx){
  erase(); // clear screen
  attron(COLOR_PAIR(1));  //change color
  mvprintw(maxy/2, maxx/2 - 10, "Welcome to NOT PONG"); // print welcome, approximately middle of screen
  refresh(); //refresh screen
  attroff(COLOR_PAIR(1)); // go back to default colors
  sleep(1); // sleep for a second by calling the linux/unix sleep library call
  return;
}

/*
  Checks if p or P have been pressed. 
  Toggles the global variable paused between 'p"aused (1) and unpaused (0)
 */
int isPaused(int c){
  if(c == 'p' || c == 'P'){
    paused = 1 - paused;
  }
  return paused;
}

/* returns TRUE if user inputs q or Q 
   c: user input
*/
int checkQuit(int c){ // parameter c, the character that was read in
  return (c == 'q' || c == 'Q');
}

/* main function. Program starts here
 */
int main(int argc, char *argv[])
{
  /* initialize your non-curses data structures here */
  int input;
  int maxx, maxy;                    // maxx and maxy size of terminal

  initialize();                      // initialize curses
  getmaxyx(stdscr, maxy, maxx);      // get current screen size 
  printWelcomeScreen(maxy, maxx);    // Print welcome screen
  erase();                           // Clearscreen
  
  // initialize ball and bat positions
  ballPositionX = maxx/2 - 2 ;       // initial location of ball (middle)
  ballPositionY = maxy/2;                    
  batPositionX = maxx -2;            // initial location of bat (right edge)
  batPositionY = maxy/2;

  while (true) {                        // infinite game loop (for ever!)
    numberOfIterations++;
    getmaxyx(stdscr, maxy, maxx); // get current screen size (in case user resizes screen during gameplay)
    input = getch();                  // get input (if any)
    if(checkQuit(input)){             // Check if it is time to quit
      break;                      // if user types q or Q, break out of infinite loop
    }

    if (! isPaused(input))
      moveBall(maxy, maxx, '0'); // move the ball
    moveBat(input, maxy, '|');     // get User input and move bat
    
    if(checkCollisions((int) batPositionY, (int) batPositionX, 
			 (int) ballPositionY, (int) ballPositionX)){
      hits++;               // update number of times you blocked the ball for scoring
      bounceBall();           // Bounce ball away from bat
    }
    
    if(ballPositionX >= maxx){           // If ball passed your bat
      whiffs++;                          // update number of whiffs for your score
    }
    
    updateScore();            // score is hits - whiffs

    if (! isCorrect(maxy, maxx) ){ // Checks that the ball stays within bounds
      break;
    }

    if(numberOfIterations % 1000 == 0) // prints some statistics on the screen every 1000 iterations
      printStats(maxy, maxx); 
  } // end for (;;)
  finish(0);                           // we're done, wrapup and shutdown gracefully 
  return 0;
}


void printStats(int maxy, int maxx){
  mvprintw(0, 1, "loopCount: %lu", numberOfIterations);
  mvprintw(1, 1, "Ball");
  mvprintw(2, 2, "x: %3i", (int) ballPositionX);
  mvprintw(3, 2, "y: %3i", (int) ballPositionY);

  mvprintw(0, maxx - 20, "  Hits: %4i", hits);
  mvprintw(1, maxx - 20, "Whiffs: %4i", whiffs);
  mvprintw(maxy - 1, maxx - 20, "Score: %4i", score);

}

void bounceBall(){
  mvaddch((int) ballPositionY, (int) ballPositionX, ' ');
  ballPositionX = (int) ballPositionX - 1; // move ball back away from bat
  speedx = -1.0 * speedx;            // reverse ball motion
}

/* Takes and modifies ball location. Checks if ball is beyond the game
   boundary and, if so, reflects the ball
   maxx:  max x direction (min is 0)
   maxy:  max y direction (min is 0)
   bc  :  ball character ('0')
*/
void moveBall(int maxy, int maxx, char bc){
  mvaddch ((int) ballPositionY, (int) ballPositionX, ' '); // erase old ball
  ballPositionY = speedy + ballPositionY;                  // new location
  ballPositionX = speedx + ballPositionX;
  //  if(ballPositionY <= 0 || ballPositionY >= maxy){         // if beyond y boundary, reflect
  if(isOutOfBounds((int) ballPositionY, 0, maxy)) { //
    speedy = -1.0 * speedy;
  }
  //  if(ballPositionX <= 0 || ballPositionX >= maxx){         // if beyond x boundary, reflect
  if(isOutOfBounds((int) ballPositionX, 0, maxx)){ //
    speedx = -1.0 * speedx;
  }
  attron(COLOR_PAIR(2));
  mvaddch((int)ballPositionY, (int) ballPositionX, bc);    // print ball in new location
  attroff(COLOR_PAIR(2));  
  return;
}


/* Takes and modifies bat/paddle location. Checks if bat is beyond the game
   boundary and, if so, reflects the bat
   y: bat y location
   x: bat x location
   batChar  :  bat character
*/
void moveBat(int c, int maxy, char batChar){
  //void moveBat(int c, int &y, int &x, int maxy, char batChar){
  printBat((int) batPositionY, (int) batPositionX, ' '); // erase old bat
  //  if(batPositionY + 1 >= maxy){
  if(isBatBelowBottom(maxy) ){ //batPositionY + 1 >= maxy){
    batVelocityY = 0.0;
    batPositionY = (int) batPositionY - 1;
  } else if ( isBatAboveTop()) { // batPositionY - 1 < 0) {
    batVelocityY = 0.0;
    batPositionY = 1; //(int) batPositionY + 1;
  } else {
    batPositionY = batPositionY + batVelocityY;
  }

  //  y = batVelocityY + y;
  switch(c){           // respond to key (if any)
  case KEY_UP:
    batVelocityY = batVelocityY - batVelocityChange;
    break;
  case KEY_DOWN:
    batVelocityY = batVelocityY + batVelocityChange;
    break;
  case ' ':
    batVelocityY = 0.0;
    break;
  default:
    break;
  }
  attron(COLOR_PAIR(2));
  printBat((int) batPositionY, (int) batPositionX , batChar); // print bat at new bat location
  attroff(COLOR_PAIR(2));
}

// simple function to print 3 characters in a column for bat
void printBat(int y, int x, char bc){
  mvaddch(y-1, x, bc);
  mvaddch(y,   x, bc);
  mvaddch(y+1, x, bc);	
  return;
}

int checkCollisions(int batPositionY, int batPositionX, int ballPositionY, int ballPositionX){
  if (checkEqualPosition(batPositionY - 1, batPositionX - 1 , ballPositionY, ballPositionX) 
      || checkEqualPosition(batPositionY, batPositionX - 1, ballPositionY, ballPositionX) 
      || checkEqualPosition(batPositionY + 1, batPositionX - 1, ballPositionY, ballPositionX) ) {
    return TRUE;
  } else {
    return FALSE;
  }
}

int checkEqualPosition(int y1, int x1, int y2, int x2){
  return (y1 == y2 && x1 == x2);
}

void updateScore(){
  score = computeScore(hits, whiffs);
}

// finish
void finish(int sig)
{
    endwin();
    /* do your non-curses wrapup here */
    // print a nice message
    if(score > 0){
      printf ("\nWell played. Good game, see you for a rematch soon\n");
    } else {
      printf ("\nPractice and come back for a rematch :-) \n");
    }
    fclose(fp); // close the file that we opened at the beginning (for grading)

    return;//    exit(0);
}
