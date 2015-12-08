#include "phoenixFunctions.h"



int main() {
   struct ship phoenix;
   struct enemy rockets[55];
   struct laser beam[20];
   struct tribeam tribeamL[20];
   struct tribeam tribeamR[20];
   struct plasma ion[1000];
   struct options settings;
   struct highScore playerScore[10];
   int input, loops=0, i=0, j=0, currentbeams=0, currentions=0, currentrockets=55;
   int currenttribeamRs = 0, currenttribeamLs =0;
   int random=0, score=0, win=-1;
   char scorecard[30];
   char edgechar = '#';
   char menuchoice;
   int firemode;
   int difficulty;
   char directionX = 'r';
   readData(playerScore);
 

   printf("%s\n%s\n%s\n", "s: High Scores", 
           "i: Instructions", 
           "p: Play" );
   scanf(" %c", &menuchoice);

   if(menuchoice == 's'){
      printf("%s\n", "//////////////////// HIGH SCORES ///////////////////");
      printData(playerScore);
      printf("%s\n", "////////////////////////////////////////////////////");
      printf("%s\n%s\n", 
           "i: Instructions", 
           "p: Play" );
      scanf(" %c", &menuchoice);
   }

   if(menuchoice == 'i'){
         printf( "////////////////////////////////////////////////////\n");
         printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", "Left Arrow: move left\n",
                 "Right Arrow: move right\n",
                 "Spacebar: Shoot\n",
                 "If a 'P' appears catch it before it falls and recieve a weapon boost\n",
                 "Shoot down the enemy before they eliminate you\n",
                 "////////////////////////////////////////////////////\n",
                 "p: Play\n",
                 "s: High Scores\n");
         scanf(" %c", &menuchoice);
   }

   if( menuchoice == 'p'){
            printf("////////////////////////////////////////////////////\n");
            printf("choose difficulty (1-3): \n");
            scanf("%d", &difficulty);
            printf("\n////////////////////////////////////////////////////\n");
            printf("Enter Name: \n");
   }

   //initialize screen
   initscr();
   clear();
   noecho();
   cbreak();
   nodelay(stdscr,1);
   keypad(stdscr,1);
   srand(time(NULL)); 

  //initialize color
   start_color();
   init_pair(1, COLOR_BLUE, COLOR_BLACK);
   init_pair(2, COLOR_RED, COLOR_BLACK);
   init_pair(3, COLOR_GREEN, COLOR_BLACK);
   init_pair(4, COLOR_WHITE, COLOR_BLACK);
   init_pair(5, COLOR_YELLOW, COLOR_BLACK);
   init_pair(6, COLOR_CYAN, COLOR_BLACK);
   bkgd(COLOR_PAIR(1)|' ');
   
  //draw game board
  attron(COLOR_PAIR(2));
  for(int i=0; i<COLS;i++){ 
        move(0,i);
        addch(edgechar);
    }
    for(int i=0; i<COLS; i++){
        move(LINES-2,i);
        addch(edgechar);
    }
    for(int i=0; i<LINES-1;i++){ 
        move(i,0);
        addch(edgechar);
    }
    for(int i=0; i<LINES-2; i++){
        move(i,COLS-1);
        addch(edgechar);
    }
  attroff(COLOR_PAIR(2));
 
   /* Set default settings */
   if(difficulty == 1)
      settings.speed = 15000;
   else if(difficulty == 2)
      settings.speed = 13000;
   else if(difficulty == 3)
      settings.speed = 8000;
   settings.enemy = 12;
   settings.beams = 3;
   settings.ions = 10;
   settings.ionchance = 5;

   /* Set phoenix settings */
   phoenix.r = LINES - 3;
   phoenix.c = COLS / 2;
   phoenix.ch = 'W';

   /* Set rockets settings */
  SetInitialEnemyPosition(rockets);

   for (i=0; i<=55; ++i) {   
      rockets[i].pr = 0;
      rockets[i].pc = 0;
      rockets[i].ch = '?';
      rockets[i].alive = 1;
      rockets[i].direction = 'c';
      rockets[i].boost = 0;
   }
   
   /* Set beam settings */
   for (i=0; i<20; ++i) {
      beam[i].active = 0;
      beam[i].ch = '!';
   }
   for (i=0; i<20; ++i) {
      tribeamR[i].active = 0;
      tribeamR[i].ch = '*';
   }
   for (i=0; i<20; ++i) {
      tribeamL[i].active = 0;
      tribeamL[i].ch = '*';
   }
   firemode =0;

 
   /* Set ion settings */
   for (i=0; i<1000; ++i) {
      ion[i].active = 0;
      ion[i].ch = ':';
      ion[i].loop = 0;
   }
   
   /* Display game title,score header,options */
   move (LINES-1,COLS/2-7);
   addstr("Points: ");
   
   while(1) {
      /* Show score */
      sprintf(scorecard, "%d", score);
      move(LINES-1,COLS/2);
      addstr(scorecard);

      
      /* Move phoenix */
      attron(COLOR_PAIR(3));
      move(phoenix.r,phoenix.c);
      addch(phoenix.ch);
      attroff(COLOR_PAIR(3));
     
      /* Move ions */
      movePlasma(loops, settings, currentions, ion, i);
     
      /*Move beam*/
      moveBullets(loops, settings, currentbeams, currenttribeamRs, currenttribeamLs, currentrockets, beam, tribeamR, tribeamL, i, j, score, firemode, rockets);
     
      //move rockets
      moveEnemy(loops, settings, currentions, rockets, i, j, ion, random, directionX, currentrockets);
     
     //check win
      if (currentrockets == 0) {
         win = 1;
         break;
      }

      for (i=0; i<55; ++i) {
            if(rockets[i].r == phoenix.r && rockets[i].c == phoenix.c)
              firemode = 1;

         
      }
      for (i=0; i<1000; ++i) {
         if (ion[i].r == phoenix.r && ion[i].c == phoenix.c) {
            win = 0;
            break;
         }
      }    
      
      move(0,COLS-1);
      refresh();
      usleep(settings.speed);
      ++loops;
      
      input = getch();
      move(phoenix.r,phoenix.c);
      addch(' ');
      
      /* Check input */
      if (input == 'q')
         win = 2;
      else if (input == KEY_LEFT)
         --phoenix.c;
      else if (input == KEY_RIGHT)
         ++phoenix.c;
      else if (input == ' ' && currentbeams < 20 && currenttribeamRs <20 && currenttribeamLs < 20) {
         if(firemode ==0)
            for (i=0; i<20; ++i) {
               if (beam[i].active == 0) {
                  beam[i].active = 1;
                  ++currentbeams;
                  --score;
                  beam[i].r = LINES - 4;
                  beam[i].c = phoenix.c;
                  break;
               }
            }
         
         if(firemode ==1){
            for (i=0; i<20; ++i) {
                  if (beam[i].active == 0 && tribeamR[i].active ==0 && tribeamL[i].active ==0) {
                     beam[i].active = 1;
                     beam[i].r = LINES - 4;
                     beam[i].c = phoenix.c;

                     tribeamR[i].active = 1;
                     tribeamR[i].r = LINES - 4;
                     tribeamR[i].c = phoenix.c+1;

                     tribeamL[i].active = 1;
                     tribeamL[i].r = LINES - 4;
                     tribeamL[i].c = phoenix.c-1;

                     ++currenttribeamLs;
                     ++currenttribeamRs;
                     ++currentbeams;
                     --score;


                     break;
                  }
            }
         }
      }
      
      if (win != -1)
         break;
      
      /* Check for valid phoenix position */
      if (phoenix.c > COLS-3)
         phoenix.c = COLS - 3;
      else if (phoenix.c < 1)
         phoenix.c = 1;  

   }
   
  gameover(win);
  endwin();
  char enames[30];
  printf("Enter Name: ");
  scanf("%s", enames);
  if(score > playerScore[9].pscore){
      playerScore[10].name = enames;
      playerScore[10].pscore = score;
  }
  bubble(playerScore);
  printf("\n/////////////// HIGH SCORES //////////////////\n");
  printData(playerScore);
  printf("//////////////////////////////////////////////////\n");
  printf("Your Score: %d\n", score);

  freopen("highScores", "w", stdout);
    printData(playerScore);
  fclose (stdout);

return 0;
}





