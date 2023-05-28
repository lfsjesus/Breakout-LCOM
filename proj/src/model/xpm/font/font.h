#ifndef FONT_H
#define FONT_H
#include "A.xpm"
#include "B.xpm"
#include "C.xpm"
#include "colon.xpm"
#include "D.xpm"
#include "E.xpm"
#include "eight.xpm"
#include "F.xpm"
#include "five.xpm"
#include "four.xpm"
#include "G.xpm"
#include "H.xpm"
#include "I.xpm"
#include "J.xpm"
#include "K.xpm"
#include "L.xpm"
#include "M.xpm"
#include "N.xpm"
#include "nine.xpm"
#include "O.xpm"
#include "one.xpm"
#include "P.xpm"
#include "Q.xpm"
#include "R.xpm"
#include "S.xpm"
#include "seven.xpm"
#include "six.xpm"
#include "T.xpm"
#include "three.xpm"
#include "two.xpm"
#include "U.xpm"
#include "V.xpm"
#include "W.xpm"
#include "X.xpm"
#include "Y.xpm"
#include "Z.xpm"
#include "zero.xpm"
#include "slash.xpm"
#include "../../../controller/video/graphics.h"
#include "../../sprite.h"

Sprite* twoPoints;
Sprite* slashSprite;

static xpm_map_t digits[10] = {zero, one, two, three, four, five, six, seven, eight, nine};
static xpm_map_t alphabet[] = {A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z};
static Sprite* alphabet_sprites[26];
static Sprite* number_sprites[10];

void init_alphabet_sprites();
void init_number_sprites();
void destroy_alphabet_sprites();
void destroy_number_sprites();
Sprite* get_char(char c);
Sprite* get_number(char c);

#endif
