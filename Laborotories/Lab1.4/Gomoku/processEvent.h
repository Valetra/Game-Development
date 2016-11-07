#ifndef GOMOKU_PROCESSEVENT_H
#define GOMOKU_PROCESSEVENT_H

#include "stdafx.h"
#include "constants.h"

void ProcessEvent(GameObject &object, GameCell &cell, Event &event, RenderWindow &window);
void CreateSquare(GameObject &object, GameCell &cell, const float &cellPositionX, const float &cellPositionY);
void CreateCircle(GameObject &object, GameCell &cell, const float &cellPositionX, const float &cellPositionY);

#endif