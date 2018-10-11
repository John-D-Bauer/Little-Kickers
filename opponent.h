#pragma once
#include "images.h"
#include "globals.h"

Sprites sprites;

void drawopponent() {
int frame = opp.stance == OppStance::oppStanding ? 0 : (opp.stance * 2 - 1 + opp.animationFrame);
sprites.drawOverwrite(opp.x,opp.y,opponentImages,frame);
}


void oppAttack() {
  /* Every 30 frames change the stance - this affects how
     quickly the opponent "reacts" to the player movement.
     Experiment with different values than 30. Lower values
     will make the game more difficult (the oponent will
     have faster reaction time). */

  if (arduboy.everyXFrames(30)) {
    if(opp.x < ballx)
{
	opp.stance = OppStance::oppRunningR;
}
else if(opp.x > (ballx + BALL_SIZE))
{
	opp.stance = OppStance::oppRunningL;
}
       if(opp.y + OPP_HEIGHT <= bally)
{
	opp.stance = OppStance::oppRunningF;
}
else if(opp.y > (bally + BALL_SIZE))
{
	opp.stance = OppStance::oppRunningB;
}
  }

  /* Every 5 frames we change the animation frame - this
     will only affect the animation, so choose a value that
     just looks nice. */
  if (arduboy.everyXFrames(5)) {
    opp.animationFrame = (opp.animationFrame + 1) % 2;
  }
  /* Every 7 frames we actually move the opponent in direction
     in which he is facing. */
  if (!opp.hasBall && arduboy.everyXFrames(7)) {
    switch (opp.stance)
    {
     case OppStance::oppRunningR:
	if(opp.x < ballx)
	{
		opp.x += OPP_SPEED;
	}
	break;

case OppStance::oppRunningL:
	if(opp.x > (ballx + BALL_SIZE))
	{
		opp.x -= OPP_SPEED;
	}
	break;

      case OppStance::oppRunningF:
      if(opp.y + OPP_HEIGHT < mapy + TILE_SIZE * WORLD_HEIGHT) {
      opp.y += 1;
    }
        break;

      case OppStance::oppRunningB:
       if(mapy < opp.y + 12) {
      opp.y -= 1;
    }
        break;
    }
  }
} 

void oppGoal()
{
	Rect ballRect = { ballx, bally, BALL_SIZE + 1, BALL_SIZE + 1 };
	Rect oppRect = { opp.x, opp.y, OPP_WIDTH, OPP_HEIGHT };

	if (arduboy.collide(oppRect, ballRect))
	{
		opp.hasBall = true;
		player.hasBall = false;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	if (opp.hasBall) {
	  if (ballx != mapx) {
	    /* Every 30 frames change the stance - this affects how
     quickly the opponent "reacts" to the player movement.
     Experiment with different values than 30. Lower values
     will make the game more difficult (the oponent will
     have faster reaction time). */

  if (arduboy.everyXFrames(30)) {
if(opp.x > (mapx + TILE_SIZE * WORLD_WIDTH))
{
	opp.stance = OppStance::oppRunningL;
}
       if(opp.y < mapy)
{
	opp.stance = OppStance::oppRunningF;
}
else if(opp.y > (mapy + TILE_SIZE * WORLD_HEIGHT))
{
	opp.stance = OppStance::oppRunningB;
}
  }

  /* Every 5 frames we change the animation frame - this
     will only affect the animation, so choose a value that
     just looks nice. */
  if (arduboy.everyXFrames(5)) {
    opp.animationFrame = (opp.animationFrame + 1) % 2;
  }
  /* Every 7 frames we actually move the opponent in direction
     in which he is facing. */
  if (arduboy.everyXFrames(7)) {
    switch (opp.stance)
    {

case OppStance::oppRunningL:
	if(mapx < opp.x) {
      opp.x -= 1;
    }
  
	ballx = opp.x - BALL_SIZE;
	bally = opp.y + (OPP_HEIGHT / 2);
  
	break;

      case OppStance::oppRunningF:
     if(opp.y + OPP_HEIGHT < mapy + TILE_SIZE * WORLD_HEIGHT) {
      opp.y += 1;
    }
        break;

      case OppStance::oppRunningB:
        if(opp.y <= mapy + TILE_SIZE * WORLD_HEIGHT)
	{
		opp.y -= OPP_SPEED;
	}
        break;
    }
  
  if (arduboy.everyXFrames(7)) {
	    ballx -= 1;
	    }
	  }
	}
	else {
	    ballx += 0;
	    opp.x += 0;
	}
	
	if(ballx == mapx)
	{
		oppScore += 1;
	  ballx = PLAYER_X_OFFSET + PLAYER_WIDTH - 2;
    bally = PLAYER_Y_OFFSET + PLAYER_HEIGHT / 2;
    mapx = 0;
    mapy = 0;
    opp.hasBall = false;
    opp.x = WIDTH - OPP_WIDTH;
    opp.y = HEIGHT / 2 - OPP_HEIGHT / 2;
	}
}
}
