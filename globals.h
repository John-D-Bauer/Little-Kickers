#ifndef GLOBALS_H
#define GLOBALS_H

#include "images.h"

int oppScore {0};

#define OPP_WIDTH    10
#define OPP_HEIGHT  16
#define OPP_X_OFFSET   WIDTH - OPP_WIDTH
#define OPP_Y_OFFSET   HEIGHT / 2 - OPP_HEIGHT / 2
#define OPP_SPEED  1

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

#define PLAYER_WIDTH    10
#define PLAYER_HEIGHT  16
#define PLAYER_X_OFFSET   WIDTH / 2 - PLAYER_WIDTH / 2
#define PLAYER_Y_OFFSET    HEIGHT / 2 - PLAYER_HEIGHT / 2
#define BALL_RADIUS    4
#define BALL_SIZE    8

int ballx{OPP_X_OFFSET - OPP_WIDTH - 2};
int bally{PLAYER_Y_OFFSET + PLAYER_HEIGHT / 2};

int playerScore {0};

enum Stance {
  Standing,
  RunningR1,
  RunningR2,
  RunningL1,
  RunningL2,
  RunningF1,
  RunningF2,
  RunningB1,
  RunningB2,
};

struct Player {
  int x;
  int y;
  Stance stance;
  bool hasBall;
  char image;
};

Player player = {PLAYER_X_OFFSET, PLAYER_Y_OFFSET, Stance::Standing, false, playerImages};

#endif
