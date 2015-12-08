#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>
#include <cstdlib>



struct phoeniX {
    int y,x;
    char ch;
};

struct revenge {
    int y,x;
    int py,px;
    int alive; 
    char direction; 
    char ch;
};

struct options {
    int overall,enemies,shots,bombs,bombchance;
};

struct bullet {
    int y,x;
    int active; 
    char ch;
};

struct plasma {
    int y,x;
    int active; 
    int loop; 
    char ch;
};



void gameover(int win);

int main(){
	struct phoeniX phoenix;
	struct revenge enemies[6];
	struct bullet fireball[6];
	struct plasma plasma[100];
	struct options settings;
	unsigned int input;
	unsigned int loops =0;
	unsigned int i = 0;
	unsigned int j =0;
	unsigned int currentShots =0;
	unsigned int currentEnemies=5;
	int random=0, score =0, win =-1;
	char showscore[30];
    	char edgechar = 'Q';
	int maxheight, maxwidth;
	initscr();
	clear();
	noecho();
	cbreak();
	nodelay(stdscr, true);
	keypad(stdscr, true);
	srand(time(0));
	getmaxyx(stdscr, maxheight, maxwidth);
   // drawboard
    for(int i=0; i<maxwidth;i++){ 
        move(0,i);
        addch(edgechar);
    }
    for(int i=0; i<maxwidth; i++){
        move(maxheight-2,i);
        addch(edgechar);
    }
    for(int i=0; i<maxheight-1;i++){ 
        move(i,0);
        addch(edgechar);
    }
    for(int i=0; i<maxheight-2; i++){
        move(i,maxwidth-2);
        addch(edgechar);
    }
   
    settings.overall = 15000;
    settings.enemies = 12;
    settings.shots = 3;
    

    phoenix.y = maxheight -3;
    phoenix.x = maxwidth/2;
    phoenix.ch = 'W';

    for(i=0; i<2; i++){
    	enemies[i].y =2;
    	enemies[i].x = i*3;
    	enemies[i].py = 0;
    	enemies[i].px = 0;
    	enemies[i].ch = 'Y';
    	enemies[i].direction = 'r';
    	enemies[i].alive = 1;
    }
    for(i=3; i<4; i++){
    	enemies[i].y = 4;
    	enemies[i].x = 2;
    	enemies[i].py = 0;
    	enemies[i].px = 0;
    	enemies[i].ch = 'Y';
    	enemies[i].direction = 'r';
    	enemies[i].alive = 1;
	}
	 for(i=4; i<6; i++){
    	enemies[i].y = 6;
    	enemies[i].x = (i/4)*3;
    	enemies[i].py = 0;
    	enemies[i].px = 0;
    	enemies[i].ch = 'Y';
    	enemies[i].direction = 'r';
    	enemies[i].alive = 1;
    }

    for(i=0; i<3; i++){
    	fireball[i].active =0;
    	fireball[i].ch = '^';
    }

    for(i=0; i<100; i++){
    	plasma[i].active = 0;
    	plasma[i].loop = 0;
    	plasma[i].ch = '&';
    }

    //draw score
    move (maxheight-1,1);
    addstr("SCORE: ");
    
    

    while(1){
    	sprintf(showscore, "%d", score);
    	move(maxheight-1 ,8);
    	addstr(showscore);

    	move(phoenix.y, phoenix.x);
    	addch(phoenix.ch);

    	//fireshot
    	if(loops % settings.shots == 0)
    	for( i = 0; i<6; ++i){
    		if(fireball[i].active ==1){
    			if(fireball[i].y > 0){
    				if(fireball[i].y <  maxheight-3){
    					move(fireball[i].y+1, fireball[i].x);
    					addch(' ');
    					}

    				//detect hit
                    for( j= 0; j < 6; j++){ 
    					if(enemies[j].alive ==1 && enemies[j].y == fireball[i].y && enemies[j].px == fireball[i].x){
    						score += 20;
    						enemies[j].alive =0;
    						fireball[i].active=0;
    						--currentShots;
    						--currentEnemies;
    						move(enemies[j].py, enemies[j].px);
    						addch(' ');
    						break;
    					}
    				}
    				if(fireball[i].active == 1){
    					move(fireball[i].y, fireball[i].x);
    					addch(fireball[i].ch);
    					--fireball[i].y;
    				}

    			}
    			else{
    				fireball[i].active = 0;
    				--currentShots;
    				move(fireball[i].y=1, fireball[i].x);
    				addch(' ');

    			}
    		}
    	
    	}
        //move enemies
    	if(loops % settings.enemies ==0)
    		for( i=0; i< 30; i++){
    			if(enemies[i].alive ==1){
    				move(enemies[i].py, enemies[i].px);
    				addch(' ');
    				move(enemies[i].y, enemies[i].x);
    				addch(enemies[i].ch);
    				enemies[i].py = enemies[i].y;
    				enemies[i].px = enemies[i].x;
    				

    				if(enemies[i].direction == 'l')
    					--enemies[i].x;
    				else if(enemies[i].direction == 'r')
    					++enemies[i].x;
    				if(enemies[i].x == maxwidth -3) {
    					++enemies[i].y;
    					enemies[i].direction = 'l';
       				}
       				else if(enemies[i].x ==1){
       					++enemies[i].y;
       					enemies[i].direction = 'r';

       				}

    			}
    		}

    		if(currentEnemies ==0){
    			win =1;
    			break;
    		}
    		for(i=0; i< 5; i++){
    			if(enemies[i].y == maxheight-1){
    				win = 0;
    				break;
    			}
    		}
    		for(i=0; i<100; i++){
    			if(plasma[i].y == phoenix.y && plasma[i].x == phoenix.x){
    				win = 0;
    				break;
    			}
    		}

    		move(0, maxwidth-1);
    		refresh();
    		usleep(settings.overall);
    		++loops;
    		input = getch();
    		move(phoenix.y,phoenix.x);
    		addch(' ');
    		if(input == 'q')
    			win =2;
    		else if(input == KEY_LEFT)
    			--phoenix.x;
    		else if(input == KEY_RIGHT)
    			++phoenix.x;
    		else if(input == ' ' && currentShots < 6){
				for( i= 0; i<6; --i){
					if(fireball[i].active ==0){
						fireball[i].active = 1;
						++currentShots;
						--score;
						fireball[i].y = maxheight-3;
						fireball[i].x = phoenix.x;
						break;
					}
				}
			}
			
			
			if(win != -1)
				break;
			if(phoenix.x > maxwidth-2)
				phoenix.x = maxwidth-2;
			else if(phoenix.x<0)
				phoenix.x =0;
    }

    gameover(win);
    endwin();
    return 0;

}






void gameover(int win) {

   nodelay(stdscr, 0);
   
  
   
}
