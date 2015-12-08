#include "phoenixFunctions.h"

void moveEnemy( int &loops, options settings,  int &currentions, enemy *rockets, int i, int j, plasma *ion, int random, char &directionX, int &currentrockets){

 if (loops % settings.enemy == 0)
      for (i=0; i<=55; ++i) {
       
         if (rockets[i].alive == 1) {
            move(rockets[i].pr,rockets[i].pc);
            addch(' ');
            
            

            if(rockets[i].boost = 1){
               attron(COLOR_PAIR(4));
               move(rockets[i].r,rockets[i].c);
               addch(rockets[i].ch);
               attroff(COLOR_PAIR(4));
            }
           

            
            rockets[i].pr = rockets[i].r;
            rockets[i].pc = rockets[i].c;
            
            /* Check if enemy should drop ion */
            random = 1+(rand()%100);
            if ((settings.ionchance - random) >= 0 && currentions < 1000) {
               for (j=0; j<1000; ++j) {
                  if (ion[j].active == 0) {
                     ion[j].active = 1;
                     ++currentions;
                     ion[j].r = rockets[i].r + 1;
                     ion[j].c = rockets[i].c;
                     break;
                  }
               }
            }
             
            /* Set enemy's next position */
            if (rockets[i].direction == 'z'){
               --rockets[i].c;
               ++rockets[i].r;}
            else if (rockets[i].direction == 'c'){
               ++rockets[i].c;
               ++rockets[i].r;}
            else if(rockets[i].direction =='q'){
               --rockets[i].c;
               --rockets[i].r;}
            else if(rockets[i].direction == 'e'){
               ++rockets[i].c;
               --rockets[i].r;}
            else if(rockets[i].direction == 'd')
               ++rockets[i].r;
               
            /* Check enemy's next positions */
            if (rockets[i].c == COLS - 2){
               ++rockets[i].r;
               rockets[i].direction = 'z';
               directionX = 'l';
            }
             
               else if(rockets[i].r == (LINES/2) && directionX == 'l')
                  rockets[i].direction = 'q';
            
               else if(rockets[i].r == 2 && directionX == 'l')
                  rockets[i].direction = 'z';

            else if (rockets[i].c == 2) {
               ++rockets[i].r;
               rockets[i].direction = 'c';
               directionX = 'r';
            }

               else if(rockets[i].r == (LINES/2) && directionX == 'r')
                  rockets[i].direction = 'e';
              
               else if(rockets[i].r == 2 && directionX == 'r')
                  rockets[i].direction = 'c';

               if(rockets[i].r > LINES/2){
                  rockets[i].c = (COLS/2);
                  rockets[i].direction = 'd';
                  rockets[i].ch = 'P';
                  rockets[i].boost = 1;
                  --currentrockets;
               }
               if(rockets[i].r > LINES -3){
                  rockets[i].alive =0;

               }
         }
       
      }

}


void moveBullets( int &loops, options settings,  int &currentbeams,  int &currenttribeamRs,  int &currenttribeamLs,  int &currentrockets, laser *beam, tribeam *tribeamR, tribeam *tribeamL, int i, int j, int &score, int firemode, enemy *rockets){
if (loops % settings.beams == 0)
         for (i=0; i<20; ++i) {
            attron(COLOR_PAIR(6));
            if (beam[i].active == 1) {
               if (beam[i].r > 0) {
                  if (beam[i].r < LINES - 4) {
                     move(beam[i].r + 1,beam[i].c);
                     addch(' ');
                  }
               
                  for (j=0; j<=55; ++j) {
                     if (rockets[j].alive == 1 && rockets[j].r == beam[i].r && rockets[j].pc == beam[i].c) {
                        score += 20;
                        rockets[j].alive = 0;
                        beam[i].active = 0;
                        --currentbeams;
                        --currentrockets;
                        move(rockets[j].pr,rockets[j].pc);
                        addch(' ');
                        
                        break;
                     }
                  }
               
                  if (beam[i].active == 1) {
                     move(beam[i].r,beam[i].c);
                     addch(beam[i].ch);
                  
                     --beam[i].r;
                  }
               }
               else {
                  beam[i].active = 0;
                  --currentbeams;
                  move(beam[i].r + 1,beam[i].c);
                  addch(' ');
               }
            }
            attroff(COLOR_PAIR(6));
         } 

     /*If boost acquired turn on Tri beam*/  
      if(firemode == 1){
         if (loops % settings.beams == 0)
         for (i=0; i<20; ++i) {
            attron(COLOR_PAIR(6));
            if (tribeamL[i].active == 1) {
               if(tribeamL[i].c > 1 && tribeamL[i].c < COLS-1){
               if (tribeamL[i].r > 0  ) {
                  if (tribeamL[i].r < LINES - 4 ) {
                     move(tribeamL[i].r + 1,tribeamL[i].c+1);
                     addch(' ');
                  }
               
                  for (j=0; j<=55; ++j) {
                     if (rockets[j].alive == 1 && rockets[j].r == tribeamL[i].r && rockets[j].pc == tribeamL[i].c) {
                        score += 20;
                        rockets[j].alive = 0;
                        tribeamL[i].active = 0;
                        --currenttribeamLs;
                        --currentrockets;
                        move(rockets[j].pr,rockets[j].pc);
                        addch(' ');
                     
                        break;
                     }
                  }
               
                  if (tribeamL[i].active == 1) {
                     move(tribeamL[i].r,tribeamL[i].c);
                     addch(tribeamL[i].ch);
                  
                     --tribeamL[i].r;
                     --tribeamL[i].c;
                  }
               }
               }
               else {
                  tribeamL[i].active = 0;
                  --currenttribeamLs;
                  move(tribeamL[i].r + 1,tribeamL[i].c+1);
                  addch(' ');
               }
            }
            attroff(COLOR_PAIR(6));
         }

      
         if (loops % settings.beams == 0)
         for (i=0; i<20; ++i) {
            attron(COLOR_PAIR(6));
            if (tribeamR[i].active == 1) {
               if( tribeamR[i].c > 1 && tribeamR[i].c < COLS-1){
               if (tribeamR[i].r > 0 ) {
                  if (tribeamR[i].r < LINES - 4 ) {
                     move(tribeamR[i].r + 1,tribeamR[i].c-1);
                     addch(' ');
                  }
               
                  for (j=0; j<=55; ++j) {
                     if (rockets[j].alive == 1 && rockets[j].r == tribeamR[i].r && rockets[j].pc == tribeamR[i].c) {
                        score += 20;
                        rockets[j].alive = 0;
                        tribeamR[i].active = 0;
                        --currenttribeamRs;
                        --currentrockets;
                        move(rockets[j].pr,rockets[j].pc);
                        addch(' ');
                     
                     break;
                     }
                  }
               
                  if (tribeamR[i].active == 1) {
                     move(tribeamR[i].r,tribeamR[i].c);
                     addch(tribeamR[i].ch);
                  
                     --tribeamR[i].r;
                     ++tribeamR[i].c;
                  }
               }
               }
            
               else {
                  tribeamR[i].active = 0;
                  --currenttribeamRs;
                  move(tribeamR[i].r + 1,tribeamR[i].c-1);
                  addch(' ');
               }
            }
           attroff(COLOR_PAIR(6)); 
         }
      }
}

void movePlasma( int &loops, options settings,  int &currentions, plasma *ion, int i){
if (loops % settings.ions == 0)
      for (i=0; i<1000; ++i) {
         attron(COLOR_PAIR(5));
         if (ion[i].active == 1) {
            if (ion[i].r < LINES-2) {
               if (ion[i].loop != 0) {
                  move(ion[i].r-1,ion[i].c);
                  addch(' ');
               }
               else
                  ++ion[i].loop;
               
               move(ion[i].r,ion[i].c);
               addch(ion[i].ch);
               
               ++ion[i].r;
            }
            else {
               ion[i].active = 0;
               ion[i].loop = 0;
               --currentions;
               move(ion[i].r - 1,ion[i].c);
               addch(' ');
            }
         }
         attroff(COLOR_PAIR(5));
      }
}

/* This function handles displaying the win/lose screen */
void gameover(int win) {

   nodelay(stdscr, 0);
   
   if (win == 0) {
      clear();
      move((LINES/2)-1,(COLS/2)-5);
      addstr("GAME OVER!");
      move((LINES/2),(COLS/2)-5);
      addstr("Press Enter ");

      move(LINES/2,COLS/2);
      refresh();
      getch();
   
   }
   
   else if (win == 1) {
      clear();
      move((LINES/2)-1,(COLS/2)-5);
      addstr("GAME OVER. You have Won!");
      move((LINES/2),(COLS/2)-11);
      addstr("Press Enter ");
      move(0,COLS-1);
      refresh();
      getch();
   }
}

void readData(highScore *playerScore){
        FILE *fp;
        fp = fopen("highScores", "r");

        for(int i = 0; i < 10; i++){
                playerScore[i].name = new char [30];
                fscanf(fp, "%s %d", playerScore[i].name, &(playerScore[i].pscore));
        }
        fclose(fp);

}

void swap(highScore *playerScore, int i, int j){
  highScore tmp = playerScore[i];
  playerScore[i] = playerScore[j];
  playerScore[j] = tmp;
}


void bubble(highScore *playerScore){
  bool sorted = false;
  while(!sorted){
    sorted = true;
    for(int i = 0; i < 10; i++){
      if (playerScore[i].pscore < playerScore[i+1].pscore){
        swap(playerScore, i, i+1);
        sorted = false;
      }
    }
  }
}

void printData(highScore *playerScore){
   for(int i = 0; i< 10; i++){
      printf("%s %d\n", playerScore[i].name, playerScore[i].pscore);
   }
}

void SetInitialEnemyPosition(enemy *rockets){
   rockets[0].r = 2;
   rockets[0].c = 2;

   rockets[1].r = 2;
   rockets[1].c = 4;
  
   rockets[2].r = 2;
   rockets[2].c = 6;

   rockets[3].r = 2;
   rockets[3].c = 10;

   rockets[4].r = 2;
   rockets[4].c = 14;

   rockets[5].r = 2;
   rockets[5].c = 16;

   rockets[6].r = 2;
   rockets[6].c = 18;

   rockets[7].r = 3;
   rockets[7].c = 3;

   rockets[8].r = 3;
   rockets[8].c = 5;

   rockets[9].r = 3;
   rockets[9].c = 7;

   rockets[10].r = 3;
   rockets[10].c = 9;

   rockets[11].r = 3;
   rockets[11].c = 10;

   rockets[12].r = 3;
   rockets[12].c = 11;

   rockets[13].r = 3;
   rockets[13].c = 13;

   rockets[14].r = 3;
   rockets[14].c = 15;

   rockets[15].r = 3;
   rockets[15].c = 17;

   rockets[16].r = 4;
   rockets[16].c = 4;

   rockets[17].r = 4;
   rockets[17].c = 7;

   rockets[18].r = 4;
   rockets[18].c = 8;

   rockets[19].r = 4;
   rockets[19].c = 10;

   rockets[20].r = 4;
   rockets[20].c = 12;

   rockets[21].r = 4;
   rockets[21].c = 13;

   rockets[22].r = 4;
   rockets[22].c = 16;

   rockets[23].r = 5;
   rockets[23].c = 3;

   rockets[24].r = 5;
   rockets[24].c = 5;

   rockets[25].r = 5;
   rockets[25].c = 8;

   rockets[26].r = 5;
   rockets[26].c = 9;

   rockets[27].r = 5;
   rockets[27].c = 10;

   rockets[28].r = 5;
   rockets[28].c = 11;

   rockets[29].r = 5;
   rockets[29].c = 12;

   rockets[30].r = 5;
   rockets[30].c = 15;

   rockets[31].r = 5;
   rockets[31].c = 17;

   rockets[32].r = 6;
   rockets[32].c = 4;

   rockets[33].r = 6;
   rockets[33].c = 9;

   rockets[34].r = 6;
   rockets[34].c = 10;

   rockets[35].r = 6;
   rockets[35].c = 11;

   rockets[36].r = 6;
   rockets[36].c = 16;

   rockets[37].r = 7;
   rockets[37].c = 10;

   rockets[38].r = 2;
   rockets[38].c = 20;

   rockets[39].r = 3;
   rockets[39].c = 21;

   rockets[40].r = 4;
   rockets[40].c = 22;

   rockets[41].r = 5;
   rockets[41].c = 23;

   rockets[42].r = 6;
   rockets[42].c = 24;

   rockets[43].r = 5;
   rockets[43].c = 25;

   rockets[44].r = 4;
   rockets[44].c = 26;

   rockets[45].r = 3;
   rockets[45].c = 27;

   rockets[46].r = 2;
   rockets[46].c = 28;

   rockets[47].r = 2;
   rockets[47].c = 23;

   rockets[48].r = 2;
   rockets[48].c = 25;

   rockets[49].r = 3;
   rockets[49].c = 24;

   rockets[50].r = 5;
   rockets[50].c = 19;

   rockets[51].r = 5;
   rockets[51].c = 21;

   rockets[52].r = 6;
   rockets[52].c = 20;

   rockets[53].r = 5;
   rockets[53].c = 27;

   rockets[54].r = 5;
   rockets[54].c = 29;

   rockets[55].r = 6;
   rockets[55].c = 28;
}
