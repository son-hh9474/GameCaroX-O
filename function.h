#pragma once
#include "data.h"

void resizeConsole (int);

void toMau(int, int);

int manHinhSanh();

void gotoxy(int, int);

void taoArr2DDong(dataCell**&, int);

void taoArr1DDong(string*&, int);

void xoaArr1DDong(string*&);

void xoaArr2DDong(dataCell**&, int);

void veBanCo(int);

void luaChonO(dataCell**&, int, char, string*&, int, int);

res manHinhBatDau(dataCell**&, int, string*&);

void manHinhKyLuc(int, int);

int checkResult(dataCell**&, int);

void ghiFile(string*, int);

int docFile(char arr[][8]);

void moPhongBanCo(bool);

void manHinhHuongDan();

void manHinhThongBaoWinner(int);

