#ifndef GOMOKU_INIT_H
#define GOMOKU_INIT_H


#include "stdafx.h"
#include "constants.h"

void InitSettings(ContextSettings &settings);
void SetField(GameObject &object, GameCell &cell, RenderWindow &window);
void InitText(Text &text, Font &font);

#endif