#pragma once
#include "images.h"

Sprites sprites;

int oppScore {0};

#define OPP_WIDTH    10
#define OPP_HEIGHT  16
#define OPP_X_OFFSET   WIDTH - OPP_WIDTH
#define OPP_Y_OFFSET   64 - OPP_HEIGHT
#define OPP_SPEED  1

Rect oppRect = {
  opp.x, opp.y, OPP_WIDTH, OPP_HEIGHT
};

enum OppStance {
  oppStanding,
  oppRunningR,
  oppRunningL,
  oppRunningF,
  oppRunningB,
};

struct oppVector {
  int x, y;
};

struct Opponent {
  int x;
  int y;
  OppStance stance;
  int animationFrame;
  bool hasBall;
  char image;
};

Opponent opp = {OPP_X_OFFSET, OPP_Y_OFFSET, OppStance::oppStanding, 0, false, opponentImages};


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
    if(ballx > opp.x) {
      opp.stance = OppStance::oppRunningR;
    }
    else if(ballx < opp.x) {
      opp.stance = OppStance::oppRunningL;
    }
    else if (bally > opp.y) {
      opp.stance = OppStance::oppRunningF;
    }
    else if(bally < opp.y) {
      opp.stance = OppStance::oppRunningB;
    }
  }

  /* Every 5 frames we change the animation frame - this
     will only affect the animation, so choose a value that
     just looks nice. */
  if (arduboy.everyXFrames(5))
    opp.animationFrame = (opp.animationFrame + 1) % 2;
  
  /* Every 7 frames we actually move the opponent in direction
     in which he is facing. */
  if (!opp.hasBall && arduboy.everyXFrames(7)) {
    switch (opp.stance)
    {
      case OppStance::oppRunningR:
        opp.x += OPP_SPEED;
        break;

      case OppStance::oppRunningL:
        opp.x -= OPP_SPEED;
        break;

      case OppStance::oppRunningF:
        opp.y += OPP_SPEED;
        break;

      case OppStance::oppRunningB:
        opp.y -= OPP_SPEED;
        break;
    }
  }
} 

void oppGoal() {
if (arduboy.collide(oppRect, ballRect)) {
  opp.hasBall = true;
}
  
  if(opp.hasBall == true) {
    oppScore += 1;
  }
}
