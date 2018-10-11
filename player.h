/* Things needing to be worked on:
 1. Dribbling, shooting, slide tackling, etc.  
 */

#pragma once
#include "images.h"
#include "globals.h"


void drawball() {
  arduboy.fillCircle(ballx + 4, bally + 4, BALL_RADIUS, BLACK);
  arduboy.drawBitmap(ballx, bally, ball, BALL_SIZE, BALL_SIZE, WHITE);
}

void contact () {
Rect ballRect = { ballx, bally, BALL_SIZE, BALL_SIZE};
Rect playerRect = {player.x, player.y, PLAYER_WIDTH, PLAYER_HEIGHT};
  
  if (arduboy.collide(ballRect, playerRect))  {
    player.hasBall = true;
    opp.hasBall = false;
  }
}

void drawplayer() {
player.image = playerImages[player.stance];
arduboy.fillRect(player.x, player.y, PLAYER_WIDTH, PLAYER_HEIGHT, BLACK);  
Sprites::drawExternalMask(player.x, player.y, playerImages, playerImages, player.stance, player.stance);
}

void playerinput() {
  if(arduboy.pressed(UP_BUTTON)) {
    if(mapy < PLAYER_Y_OFFSET + 12) {
      mapy += 1;
    }

    if (arduboy.pressed(UP_BUTTON) && (player.hasBall)) {
      ballx = PLAYER_X_OFFSET + 6;
      bally = PLAYER_Y_OFFSET + 6;
    }
     if ((player.hasBall && arduboy.everyXFrames(8)) || (!player.hasBall && arduboy.everyXFrames(7))) {
  switch(player.stance) {
    case Stance::Standing:
    case Stance::RunningR1:
    case Stance::RunningL1:
    case Stance::RunningF1:
    player.stance = Stance::RunningB1;
    break;

    case Stance::RunningB1:
    player.stance = Stance::RunningB2;
    break;
    
    case Stance::RunningB2:
    case Stance::RunningF2:
    case Stance::RunningL2:
    case Stance::RunningR2:
    player.stance = Stance::RunningB1;
    break;
  }
  }
  
  if (opp.y < player.y && arduboy.everyXFrames(7)) {
    opp.y += 1;
  }
  
   if (arduboy.notPressed(UP_BUTTON) && ( player.stance == Stance::RunningB1 || player.stance == Stance::RunningB2 ) ) {
    player.stance = Stance::Standing; 
    }
  }
  
  
  if(arduboy.pressed(DOWN_BUTTON)) {
    if(PLAYER_Y_OFFSET + PLAYER_HEIGHT < mapy + TILE_SIZE * WORLD_HEIGHT) {
      mapy -= 1;
    }

    if (arduboy.pressed(DOWN_BUTTON) && (player.hasBall)) {
      ballx = PLAYER_X_OFFSET + 1;
      bally = PLAYER_Y_OFFSET + PLAYER_HEIGHT;
    }
    
    if ((player.hasBall && arduboy.everyXFrames(8)) || (!player.hasBall && arduboy.everyXFrames(7))) {
 switch(player.stance) {
    case Stance::Standing:
    case Stance::RunningB1:
    case Stance::RunningR1:
    case Stance::RunningL1:
    player.stance = Stance::RunningF1;
    break;

    case Stance::RunningF1:
    player.stance = Stance::RunningF2;
    break;
    
    case Stance::RunningF2:
    case Stance::RunningL2:
    case Stance::RunningR2:
    case Stance::RunningB2:
    player.stance = Stance::RunningF1;
    break;
  }
  }
  
  if (opp.y > player.y && arduboy.everyXFrames(7)) {
    opp.y -= 1;
  } 
  
   if (arduboy.notPressed(DOWN_BUTTON) && ( player.stance == Stance::RunningF1 || player.stance == Stance::RunningF2 ) ) {
    player.stance = Stance::Standing; 
    }
  }
  
  if(arduboy.pressed(LEFT_BUTTON)) {
    if(mapx < PLAYER_X_OFFSET) {
      mapx += 1;
    }

    if (arduboy.pressed(LEFT_BUTTON) && (player.hasBall)) {
      ballx = PLAYER_X_OFFSET - PLAYER_WIDTH + 2;
      bally = PLAYER_Y_OFFSET + PLAYER_HEIGHT / 2;
    }
    
  if ((player.hasBall && arduboy.everyXFrames(8)) || (!player.hasBall && arduboy.everyXFrames(7))) {
  switch(player.stance) {
    case Stance::Standing:
    case Stance::RunningR1:
    case Stance::RunningB1:
    case Stance::RunningF1:
    player.stance = Stance::RunningL1;
    break;

    case Stance::RunningL1:
    player.stance = Stance::RunningL2;
    break;
    
    case Stance::RunningF2:
    case Stance::RunningL2:
    case Stance::RunningR2:
    case Stance::RunningB2:
    player.stance = Stance::RunningL1;
    break;
  }
  }
  
  if (opp.x < player.x && arduboy.everyXFrames(7)) {
    opp.x += 1;
  }
  
   if (arduboy.notPressed(LEFT_BUTTON) && ( player.stance == Stance::RunningL1 || player.stance == Stance::RunningL2 ) ) {
    player.stance = Stance::Standing; 
    }
  }

  if(arduboy.pressed(RIGHT_BUTTON)) {
    if(PLAYER_X_OFFSET + PLAYER_WIDTH < mapx + TILE_SIZE * WORLD_WIDTH) {
      mapx -= 1;
    }

    if (arduboy.pressed(RIGHT_BUTTON) && (player.hasBall)) {
      ballx = PLAYER_X_OFFSET + PLAYER_WIDTH;
      bally = PLAYER_Y_OFFSET + PLAYER_HEIGHT / 2;
    }
    
  if ((player.hasBall && arduboy.everyXFrames(8)) || (!player.hasBall && arduboy.everyXFrames(7))) {
  switch(player.stance) {
    case Stance::Standing:
    case Stance::RunningL1:
    case Stance::RunningB1:
    case Stance::RunningF1:
    player.stance = Stance::RunningR1;
    break;

    case Stance::RunningR1:
    player.stance = Stance::RunningR2;
    break;
    
    case Stance::RunningF2:
    case Stance::RunningL2:
    case Stance::RunningR2:
    case Stance::RunningB2:
    player.stance = Stance::RunningR1;
    break;
  }
  }
  
 if (opp.x > player.x && arduboy.everyXFrames(7)) {
    opp.x -= 1;
  }
  
   if (arduboy.notPressed(RIGHT_BUTTON) && ( player.stance == Stance::RunningR1 || player.stance == Stance::RunningR2 ) ) {
    player.stance = Stance::Standing; 
    }
  }
}

void scoreGoal() { 
  
  if (ballx + BALL_SIZE >= mapx + TILE_SIZE * WORLD_WIDTH) {
    playerScore += 1; 
    ballx = OPP_X_OFFSET - OPP_WIDTH - 2;
    bally = PLAYER_Y_OFFSET + PLAYER_HEIGHT / 2;
    mapx = 0;
    mapy = 0;
    opp.hasBall = true;
    player.hasBall = false;
    opp.x = WIDTH - OPP_WIDTH;
    opp.y = HEIGHT / 2 - OPP_HEIGHT / 2;
  }
}

void resetGame() {
  ballx = PLAYER_X_OFFSET + PLAYER_WIDTH - 2;
  bally = PLAYER_Y_OFFSET + PLAYER_HEIGHT / 2;
  playerScore = 0;
  oppScore = 0;
  mapx = 0;
  mapy = 0;
}
