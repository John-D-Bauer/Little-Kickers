#include <Arduboy2.h>
Arduboy2 arduboy;

#include "maps.h"
#include "player.h"
#include "opponent.h"
#include "globals.h"

#define GAME_INTRO  0
#define GAME_TITLE  1
#define GAME_PLAY 2
#define GAME_OVER 3
#define GAME_HIGH 4
int gamestate = GAME_TITLE;

void titlescreen() {
  arduboy.drawBitmap(0, 0, titleScreen, 128, 64, WHITE);
  arduboy.setCursor(50, 28);
  arduboy.print("Press\n");
   arduboy.setCursor(50, 38);
  arduboy.print(" A\n");
  if(arduboy.justPressed(A_BUTTON)) {
    gamestate = GAME_PLAY;
  }
}

void gameplay() {
  arduboy.setCursor(0, 0);
  arduboy.print("Gameplay\n");

 contact(); 
 playerinput();
 drawworld();
 drawball(); 
 drawplayer();
 scoreGoal();
 drawopponent();
 if (!opp.hasBall) {
  oppAttack();
}
oppGoal();

  if (playerScore == 5) {
    gamestate = GAME_HIGH;
  }

  if (oppScore == 5) {
    gamestate == GAME_OVER;
  }
}

void gameover() {
  arduboy.drawBitmap(54, 28, losescreen, 64, 16, WHITE);
  arduboy.setCursor(54, 38);
  arduboy.print("Press A to try again\n");
  if(arduboy.justPressed(A_BUTTON)) {
    gamestate = GAME_HIGH;
  }
}

void highscore() {
   arduboy.drawBitmap(0, 0, winscreen, 64, 64, WHITE);
  
  arduboy.setCursor(56, 28);
  arduboy.print("You won!\n         Press A to \n         start again");

  if (gamestate == GAME_HIGH) {
    resetGame();
  }
  if(arduboy.justPressed(A_BUTTON)) {
    gamestate = GAME_TITLE;
  }
}

void gameloop() {
  switch(gamestate) {
    case GAME_TITLE:
      titlescreen();
      break;

    case GAME_PLAY:
      gameplay();
      break;

    case GAME_OVER:
      gameover();
      break;

    case GAME_HIGH:
      highscore();
      break;
  }
}



void setup() {
  arduboy.begin();
  arduboy.setFrameRate(45);
  arduboy.display();

  arduboy.initRandomSeed();
  
  arduboy.clear();
}

void loop() {
  if(!(arduboy.nextFrame())) {
    return;
  }

  arduboy.pollButtons();

  arduboy.clear();

  gameloop();

  arduboy.display();
}
