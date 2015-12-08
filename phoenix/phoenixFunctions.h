
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>

struct ship {
  int r,c;
  char ch;
};


struct enemy {
  int r,c;
  int pr,pc;
  int alive; /* 1=alive 0=destroyed */
  char direction; /* 'l'=left 'r'=right */
  char ch;
  int boost;
};

struct laser {
  int r,c;
  int active; /* 1=active 0=inactive */
  char ch;
};

struct tribeam{
  int r,c;
  int active;
  char ch;
};

struct plasma {
  int r,c;
  int active; /* 1=active 0=inactive */
  int loop; /* used to prevent enemy from flashing when ion is dropped */
  char ch;
};

struct options {
  int speed,enemy,beams,ions,ionchance;
};

struct highScore{
  int pscore;
  char *name;
};

void SetInitialEnemyPosition(enemy *rockets);

void moveEnemy( int &loops, options settings,  int &currentions, enemy *rockets, int i, int j, plasma *ion, int random, char &directionX, int &currentrockets);

void moveBullets( int &loops, options settings,  int &currentbeams,  int &currenttribeamRs,  int &currenttribeamLs,  int &currentrockets, laser *beam, tribeam *tribeamR, tribeam *tribeamL, int i, int j, int &score, int firemode, enemy *rockets);

void movePlasma( int &loops, options settings,  int &currentions, plasma *ion, int i);

void gameover(int win);

void readData(highScore *playerScore);

void bubble(highScore *playerScore);

void printData(highScore *playerScore);

