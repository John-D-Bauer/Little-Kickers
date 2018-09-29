
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
  arduboy.setCursor(0, 0);
  arduboy.print("Title Screen\n");
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
  arduboy.setCursor(0, 0);
  arduboy.print("Game Over Screen\n");
  if(arduboy.justPressed(A_BUTTON)) {
    gamestate = GAME_HIGH;
  }
}

void highscore() {
  arduboy.setCursor(0, 0);
  arduboy.print("High Score Screen\n");

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
