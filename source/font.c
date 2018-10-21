#include <stdio.h>
#include <stdlib.h>

int *fontchar;
uint32_t fcw;

void allocFontChar(char c, uint8_t mult) {

  if(fontchar == NULL) fontchar = (int*) malloc( sizeof(int) * 10 * mult );
  else fontchar = (int*) realloc( fontchar, sizeof(int) * 10 * mult );

  fcw = 128;

  switch(c) {
    case ' ':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0000000;
    fontchar[1 * mult + xt] = 0b0000000;
    fontchar[2 * mult + xt] = 0b0000000;
    fontchar[3 * mult + xt] = 0b0000000;
    fontchar[4 * mult + xt] = 0b0000000;
    fontchar[5 * mult + xt] = 0b0000000;
    fontchar[6 * mult + xt] = 0b0000000;
    fontchar[7 * mult + xt] = 0b0000000;
    fontchar[8 * mult + xt] = 0b0000000;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'A':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0011000;
    fontchar[1 * mult + xt] = 0b0111100;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b1100110;
    fontchar[5 * mult + xt] = 0b1111110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b1100110;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'B':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1111100;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b1111100;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b1111100;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'C':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0111100;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100000;
    fontchar[4 * mult + xt] = 0b1100000;
    fontchar[5 * mult + xt] = 0b1100000;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b0111100;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'D':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1111100;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b1100110;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b1111100;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'E':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1111110;
    fontchar[1 * mult + xt] = 0b1100000;
    fontchar[2 * mult + xt] = 0b1100000;
    fontchar[3 * mult + xt] = 0b1100000;
    fontchar[4 * mult + xt] = 0b1111100;
    fontchar[5 * mult + xt] = 0b1100000;
    fontchar[6 * mult + xt] = 0b1100000;
    fontchar[7 * mult + xt] = 0b1100000;
    fontchar[8 * mult + xt] = 0b1111110;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'F':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1111110;
    fontchar[1 * mult + xt] = 0b1100000;
    fontchar[2 * mult + xt] = 0b1100000;
    fontchar[3 * mult + xt] = 0b1100000;
    fontchar[4 * mult + xt] = 0b1111100;
    fontchar[5 * mult + xt] = 0b1100000;
    fontchar[6 * mult + xt] = 0b1100000;
    fontchar[7 * mult + xt] = 0b1100000;
    fontchar[8 * mult + xt] = 0b1100000;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'G':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0111100;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100000;
    fontchar[4 * mult + xt] = 0b1101110;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b0111100;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'H':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1100110;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b1111110;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b1100110;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'I':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1111110;
    fontchar[1 * mult + xt] = 0b0011000;
    fontchar[2 * mult + xt] = 0b0011000;
    fontchar[3 * mult + xt] = 0b0011000;
    fontchar[4 * mult + xt] = 0b0011000;
    fontchar[5 * mult + xt] = 0b0011000;
    fontchar[6 * mult + xt] = 0b0011000;
    fontchar[7 * mult + xt] = 0b0011000;
    fontchar[8 * mult + xt] = 0b1111110;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'J':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0000110;
    fontchar[1 * mult + xt] = 0b0000110;
    fontchar[2 * mult + xt] = 0b0000110;
    fontchar[3 * mult + xt] = 0b0000110;
    fontchar[4 * mult + xt] = 0b0000110;
    fontchar[5 * mult + xt] = 0b0000110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b0111100;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'K':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1100110;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b1111100;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b1100110;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'L':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1100000;
    fontchar[1 * mult + xt] = 0b1100000;
    fontchar[2 * mult + xt] = 0b1100000;
    fontchar[3 * mult + xt] = 0b1100000;
    fontchar[4 * mult + xt] = 0b1100000;
    fontchar[5 * mult + xt] = 0b1100000;
    fontchar[6 * mult + xt] = 0b1100000;
    fontchar[7 * mult + xt] = 0b1100000;
    fontchar[8 * mult + xt] = 0b1111110;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'M':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1100011;
    fontchar[1 * mult + xt] = 0b1110111;
    fontchar[2 * mult + xt] = 0b1111111;
    fontchar[3 * mult + xt] = 0b1101011;
    fontchar[4 * mult + xt] = 0b1100011;
    fontchar[5 * mult + xt] = 0b1100011;
    fontchar[6 * mult + xt] = 0b1100011;
    fontchar[7 * mult + xt] = 0b1100011;
    fontchar[8 * mult + xt] = 0b1100011;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'N':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1100110;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1110110;
    fontchar[3 * mult + xt] = 0b1111110;
    fontchar[4 * mult + xt] = 0b1101110;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b1100110;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'O':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0111100;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b1100110;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b0111100;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'P':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1111100;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b1111100;
    fontchar[5 * mult + xt] = 0b1100000;
    fontchar[6 * mult + xt] = 0b1100000;
    fontchar[7 * mult + xt] = 0b1100000;
    fontchar[8 * mult + xt] = 0b1100000;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'Q':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0111100;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b1100110;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1100100;
    fontchar[7 * mult + xt] = 0b1101000;
    fontchar[8 * mult + xt] = 0b0110110;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'R':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1111100;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b1111100;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b1100110;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'S':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0111100;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100000;
    fontchar[3 * mult + xt] = 0b1100000;
    fontchar[4 * mult + xt] = 0b0111100;
    fontchar[5 * mult + xt] = 0b0000110;
    fontchar[6 * mult + xt] = 0b0000110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b0111100;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'T':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1111110;
    fontchar[1 * mult + xt] = 0b0011000;
    fontchar[2 * mult + xt] = 0b0011000;
    fontchar[3 * mult + xt] = 0b0011000;
    fontchar[4 * mult + xt] = 0b0011000;
    fontchar[5 * mult + xt] = 0b0011000;
    fontchar[6 * mult + xt] = 0b0011000;
    fontchar[7 * mult + xt] = 0b0011000;
    fontchar[8 * mult + xt] = 0b0011000;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'U':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1100110;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b1100110;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b0111100;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'V':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1100110;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b1100110;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b0110100;
    fontchar[8 * mult + xt] = 0b0011000;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'W':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1100011;
    fontchar[1 * mult + xt] = 0b1100011;
    fontchar[2 * mult + xt] = 0b1100011;
    fontchar[3 * mult + xt] = 0b1100011;
    fontchar[4 * mult + xt] = 0b1100011;
    fontchar[5 * mult + xt] = 0b1101011;
    fontchar[6 * mult + xt] = 0b1111111;
    fontchar[7 * mult + xt] = 0b1110111;
    fontchar[8 * mult + xt] = 0b1100011;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'X':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1100110;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b0111100;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b1100110;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'Y':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1100110;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b0111100;
    fontchar[5 * mult + xt] = 0b0011000;
    fontchar[6 * mult + xt] = 0b0011000;
    fontchar[7 * mult + xt] = 0b0011000;
    fontchar[8 * mult + xt] = 0b0011000;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case 'Z':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1111110;
    fontchar[1 * mult + xt] = 0b0000110;
    fontchar[2 * mult + xt] = 0b0000110;
    fontchar[3 * mult + xt] = 0b0001100;
    fontchar[4 * mult + xt] = 0b0011000;
    fontchar[5 * mult + xt] = 0b0110000;
    fontchar[6 * mult + xt] = 0b1100000;
    fontchar[7 * mult + xt] = 0b1100000;
    fontchar[8 * mult + xt] = 0b1111110;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case '0':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0111100;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b1100110;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b0111100;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case '1':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0011000;
    fontchar[1 * mult + xt] = 0b0111000;
    fontchar[2 * mult + xt] = 0b1111000;
    fontchar[3 * mult + xt] = 0b0011000;
    fontchar[4 * mult + xt] = 0b0011000;
    fontchar[5 * mult + xt] = 0b0011000;
    fontchar[6 * mult + xt] = 0b0011000;
    fontchar[7 * mult + xt] = 0b0011000;
    fontchar[8 * mult + xt] = 0b1111110;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case '2':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0111100;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b0000110;
    fontchar[4 * mult + xt] = 0b0111100;
    fontchar[5 * mult + xt] = 0b1100000;
    fontchar[6 * mult + xt] = 0b1100000;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b1111110;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case '3':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0111100;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b0000110;
    fontchar[4 * mult + xt] = 0b0111100;
    fontchar[5 * mult + xt] = 0b0000110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b0111100;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case '4':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1100110;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b1100110;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1111110;
    fontchar[7 * mult + xt] = 0b0000110;
    fontchar[8 * mult + xt] = 0b0000110;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case '5':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1111110;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100000;
    fontchar[3 * mult + xt] = 0b1100000;
    fontchar[4 * mult + xt] = 0b1111100;
    fontchar[5 * mult + xt] = 0b0000110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b0111100;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case '6':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0111100;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100000;
    fontchar[4 * mult + xt] = 0b1111100;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b0111100;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case '7':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b1111110;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b0000110;
    fontchar[3 * mult + xt] = 0b0001100;
    fontchar[4 * mult + xt] = 0b0001100;
    fontchar[5 * mult + xt] = 0b0011000;
    fontchar[6 * mult + xt] = 0b0011000;
    fontchar[7 * mult + xt] = 0b0110000;
    fontchar[8 * mult + xt] = 0b0110000;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case '8':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0111100;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b0111100;
    fontchar[5 * mult + xt] = 0b1100110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b0111100;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case '9':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0111100;
    fontchar[1 * mult + xt] = 0b1100110;
    fontchar[2 * mult + xt] = 0b1100110;
    fontchar[3 * mult + xt] = 0b1100110;
    fontchar[4 * mult + xt] = 0b0111110;
    fontchar[5 * mult + xt] = 0b0000110;
    fontchar[6 * mult + xt] = 0b1100110;
    fontchar[7 * mult + xt] = 0b1100110;
    fontchar[8 * mult + xt] = 0b0111100;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case ':':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0000000;
    fontchar[1 * mult + xt] = 0b0000000;
    fontchar[2 * mult + xt] = 0b0011000;
    fontchar[3 * mult + xt] = 0b0011000;
    fontchar[4 * mult + xt] = 0b0000000;
    fontchar[5 * mult + xt] = 0b0000000;
    fontchar[6 * mult + xt] = 0b0000000;
    fontchar[7 * mult + xt] = 0b0011000;
    fontchar[8 * mult + xt] = 0b0011000;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;

    case '.':
    for(uint8_t xt = 0; xt < mult; xt++) {
    fontchar[0 * mult + xt] = 0b0000000;
    fontchar[1 * mult + xt] = 0b0000000;
    fontchar[2 * mult + xt] = 0b0000000;
    fontchar[3 * mult + xt] = 0b0000000;
    fontchar[4 * mult + xt] = 0b0000000;
    fontchar[5 * mult + xt] = 0b0000000;
    fontchar[6 * mult + xt] = 0b0000000;
    fontchar[7 * mult + xt] = 0b0011000;
    fontchar[8 * mult + xt] = 0b0011000;
    fontchar[9 * mult + xt] = 0b0000000;
    }
    break;
  }

}
