#ifndef FONT_H
#define FONT_H
#include "A.xpm"
#include "ampersand.xpm"
#include "asciicircum.xpm"
#include "asterisk.xpm"
#include "at.xpm"
#include "B.xpm"
#include "backslash.xpm"
#include "bar.xpm"
#include "braceleft.xpm"
#include "braceright.xpm"
#include "bracketleft.xpm"
#include "bracketright.xpm"
#include "C.xpm"
#include "colon.xpm"
#include "comma.xpm"
#include "D.xpm"
#include "dollar.xpm"
#include "E.xpm"
#include "eight.xpm"
#include "equal.xpm"
#include "exclam.xpm"
#include "F.xpm"
#include "five.xpm"
#include "four.xpm"
#include "G.xpm"
#include "grave.xpm"
#include "greater.xpm"
#include "H.xpm"
#include "hyphen.xpm"
#include "I.xpm"
#include "J.xpm"
#include "K.xpm"
#include "L.xpm"
#include "less.xpm"
#include "M.xpm"
#include "N.xpm"
#include "nine.xpm"
#include "numbersign.xpm"
#include "O.xpm"
#include "one.xpm"
#include "P.xpm"
#include "parenleft.xpm"
#include "parenright.xpm"
#include "percent.xpm"
#include "period.xpm"
#include "plus.xpm"
#include "Q.xpm"
#include "question.xpm"
#include "quotedbl.xpm"
#include "quotesingle.xpm"
#include "R.xpm"
#include "S.xpm"
#include "semicolon.xpm"
#include "seven.xpm"
#include "six.xpm"
#include "space.xpm"
#include "T.xpm"
#include "three.xpm"
#include "two.xpm"
#include "U.xpm"
#include "underscore.xpm"
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
