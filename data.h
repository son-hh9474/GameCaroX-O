#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <ctime>



using namespace std;


struct infoConsole {
	CONSOLE_FONT_INFOEX consoleFont; // biến lưu trữ dữ về font màn hình console
	CONSOLE_SCREEN_BUFFER_INFO csbi; // biến lưu trữ thông tin màn hình console 
	infoConsole() {
		// lấy cấu trúc của kiểu dữ liệu 
		consoleFont.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		// lấy thông tin font của màn hình console hiện tại
		GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &consoleFont);
		// độ rộng của font chữ tính theo đơn vị pixel
		consoleFont.dwFontSize.X = 8;
		// độ cao của font chữ tính theo đơn vị pixel
		consoleFont.dwFontSize.Y = 16;
		// độ dày của font chữ
		consoleFont.FontWeight = 400;
		// hàm hỗ trợ nhập chuỗi
		wcscpy_s(consoleFont.FaceName, L"Consolas");
		// sau khi điền đầy đủ thông tin thay đổi font
		// hàm thay đổi font chữ
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &consoleFont);
		// hàm điều chỉnh màn hình console
		ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); // chỉnh màn hình console maximize
		// hàm lấy thông tin màn hình console
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		srand(static_cast<unsigned int>(time(0)));
	}
};

// dữ liệu vẽ bàn cờ
struct DataBanCo {

	// các kí tự ascii dùng để tạo hành bàn cờ
	char gocTraiTren = char(218);
	char gocTraiDuoi = char(192);
	char gocPhaiDuoi = char(217);
	char gocPhaiTren = char(191);
	char canhThang = char(179);
	char thanhGia = char(197);
	char canhNgang = char(196);
	char chuT = char(194);
	char chuTnguoc = char(193);
	char chuTCanhPhai = char(180);
	char chuTCanhTrai = char(195);
};

// dữ liệu ô 
struct dataCell {

	bool trangThai = false; // trạng thái ô được đánh hay chưa
	char kiTu = ' '; // kí tự được đánh vào ô
};

// các màu dùng để đổi màu thông qua hàm tô màu
struct mau {
	short black = 0;
	short blue = 1;
	short green = 2;
	short aqua = 3;
	short red = 4;
	short purple = 5;
	short yellow = 6;
	short white = 7;
	short gray = 8;
	short lightBlue = 9;
	short lightGreen = 10;
	short lightAqua = 11;
	short lightRed = 12;
	short lightPurple = 13;
	short lightYellow = 14;
	short brightWhite = 15;
};

// dữ liệu màn hình sảnh
struct dataManHinhSanh {

	const int MAXCHOICE = 5; // số lựa chọn
	int choice = 1; // biến lưu giá trị lựa chọn 
	// key lưu kí tự nhập từ bàn phím thông hàm _getch, và kí tự mũi tên
	char key, arrow = 26; 
	string batDau = "BAT DAU"; // lựa chọn 1: bắt đầu chơi
	string thoat = "THOAT"; // lựa chọn 5: thoát khỏi game
	string kyLuc = "KY LUC"; // lựa chọn 2: coi điểm của người chơi X và O
	string moPhong = "MO PHONG LAI VAN CO VUA DANH"; // lựa chọn 3: mô phỏng lại ván cờ sau khi chơi
	string huongDan = "HUONG DAN SU DUNG"; // lựa chọn 4: hướng dẫn sử dụng các nút để chơi game
};

// dữ liệu kết quả người chiến thắng và dữ liệu số nước đi trong bàn cờ
struct res {
	int winner = -1;
	int dem = 0;
};

// dữ liệu trò chơi
struct dataGame {
	dataCell** ptr; // mảng hai chiều chứa các kí tự X và O 
	int n = 15; // bàn cờ 15x15
	int choice; // choice là lựa chọn ô thứ mấy trong bàn cờ nxn
	int X = 0; // số điểm của người chơi X
	int O = 0; // số điểm của người chơi O
};
