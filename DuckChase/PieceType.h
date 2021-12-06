#ifndef __PIECETYPE_H__
#define __PIECETYPE_H__

typedef int PIECETYPE;
typedef int COLOR;

const int CYC_FILTER_COLOR = 64; //0x01000000
const int CYC_FILTER_KIND = 56;  //0x00111000
const int CYC_FILTER_TYPE = 120; //0x01111000
const int CYC_SHIFT_TYPE = 3;

const int FILTER_COLOR = 8; //0x00001000
const int SHIFT_COLOR = 3;
const int FILTER_KIND = 7; //0x00000111
const int EXCLUSIVE_OR_OPPOSITE_COLOR = 1; //0x00000001

const int COLOR_INIT = -1; //�b�U�Ĥ@�B�e���٤����D�ۤv���C��
const int COLOR_BLACK = 0; 
const int COLOR_RED = 1;

const int PIECETYPE_KING = 0;
const int PIECETYPE_ADVISER = 1;
const int PIECETYPE_ELEPHANT = 2;
const int PIECETYPE_CHARIOT = 3;
const int PIECETYPE_HORSE = 4;
const int PIECETYPE_CANNON = 5;
const int PIECETYPE_PAWN = 6; 

const int PIECETYPE_BLACK_KING = 0; //�N
const int PIECETYPE_BLACK_ADVISER = 1; //�h
const int PIECETYPE_BLACK_ELEPHANT = 2; //�H
const int PIECETYPE_BLACK_CHARIOT = 3; //��
const int PIECETYPE_BLACK_HORSE = 4; //��
const int PIECETYPE_BLACK_CANNON = 5; //�]
const int PIECETYPE_BLACK_PAWN = 6; //��

const int PIECETYPE_NONE = 7; 

const int PIECETYPE_RED_KING = 8; //��
const int PIECETYPE_RED_ADVISER = 9; //�H�K
const int PIECETYPE_RED_ELEPHANT = 10; //�H��
const int PIECETYPE_RED_CHARIOT = 11; //�H��
const int PIECETYPE_RED_HORSE = 12; //�H��
const int PIECETYPE_RED_CANNON = 13; //��
const int PIECETYPE_RED_PAWN = 14; //�L

const int PIECETYPE_COUNT = 14;

const int PIECETYPE_COVERED = 15; //�������л\�Ѥl
#endif