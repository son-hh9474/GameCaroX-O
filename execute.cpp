#include "function.h"

dataGame game;
res resGame;
string* ptr;

void playGame() {

	// xuất màn hình hướng dẫn 
	manHinhHuongDan();

	bool flag = false; // false: chưa chơi , true: đã chơi
	do {
		resGame.winner = -1;
		// lấy lựa chọn của màn hình sảnh: bắt đầu, kỷ lục, mô phỏng bàn cờ, .....
		game.choice = manHinhSanh(); 
		// 1: bắt đầu
		// 2: kỷ lục
		// 3: mô phỏng bàn cờ
		// 4: hướng dẫn sử dụng
		// 5: thoát
		if (game.choice == 1) {
			// khai báo mảng hai chiều chứa dữ liệu các ô 
			taoArr2DDong(game.ptr, game.n);
			// khai báo mảng string một chiều chứa nước đi 
			taoArr1DDong(ptr, game.n*game.n);
			// resGame.dem : nhận giá trị số ô đã đi trong bàn cờ
			// resGame.winner: 0 -> X thắng, 1 -> O thắng
			resGame = manHinhBatDau(game.ptr, game.n, ptr);
			if (resGame.winner == 0)
				game.X++;
			else if (resGame.winner == 1)
				game.O++;
			manHinhThongBaoWinner(resGame.winner);
			// sau khi ván cờ kết thúc ghi các nước đi vào file csv 
			ghiFile(ptr, resGame.dem);
			flag = true; // true -> đã chơi ván cờ -> đã có dữ liệu
			// sau khi chơi xong ván cờ hủy cấp phát mảng hai chiều và một chiều
			xoaArr1DDong(ptr);
			xoaArr2DDong(game.ptr, game.n);
		}
		else if (game.choice == 2) {
			manHinhKyLuc(game.X, game.O);
		}
		else if (game.choice == 3) {
			moPhongBanCo(flag);
		}
		else if (game.choice == 4) {
			manHinhHuongDan();
		}
	} while (game.choice != 5);
	system("cls");
	cout << "THANK YOU FOR YOUR PLAYING GAMES! SEE YOU NEXT TIME" << endl;
}
