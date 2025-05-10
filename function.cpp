#include "data.h"

infoConsole console; // thông tin màn hình console
mau colour;
DataBanCo canh;
// chiều rộng và chiều cao của màn hình console
int MAXWIDTH = console.csbi.srWindow.Right + 1, MAXHEIGHT = console.csbi.srWindow.Bottom + 1;


// hàm chỉnh kích cỡ màn hình console
void resizeConsole(int x) {
	HWND handle = GetConsoleWindow();
	ShowWindow(handle, x);
}
// hàm dịch chuyển con trỏ trong màn hình console 
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// hàm tô màu background và chữ
void toMau(int background, int text) {
	WORD colour = background * 16 + text;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}
// cấp phát động mảng hai chiều
void taoArr2DDong(dataCell**& ptr, int n) {
	ptr = new dataCell*[n];
	for (int i = 0; i < n; i++) {
		ptr[i] = new dataCell[n];
	}
}
// cấp phát động mảng một chiều
void taoArr1DDong(string*& p, int n) {
	p = new string[n];
}
// hủy cấp phát động mảng một chiều
void xoaArr1DDong(string*& p) {
	if (p == nullptr) return;
	delete[]p;
	p = nullptr;
}
// hủy cấp phát động mảng hai chiều
void xoaArr2DDong(dataCell**& ptr, int n) {
	if (ptr == nullptr) return;
	for (int i = 0; i < n; i++) {
		delete[]ptr[i];
	}
	delete[]ptr;
	ptr = nullptr;
}
// vẽ màn bàn cờ caro 15x15
void veBanCo(int n = 15) {
	// xóa màn hình khi lựa chọn bắt đầu
	system("cls"); 
	// đổi màu background thành xanh và màu chữ thành vàng
	toMau(colour.green, colour.lightYellow); 
	// xuất một dãy kí tự '-' bằng với giới hạn độ rộng màn hình console
	for (int i = 0; i < MAXWIDTH; i++)
		cout << "-";
	cout << endl;
	gotoxy(MAXWIDTH / 2, 1); // dịch chuyển con trỏ ra điểm y = 1, giữa màn hình console
	toMau(colour.black, colour.red);
	cout << "GAME CARO" << endl;
	toMau(colour.green, colour.lightYellow);
	for (int i = 0; i < MAXWIDTH; i++)
		cout << "-";
	// đổi background và màu chữ về màu mặc định
	toMau(colour.black, colour.white);
	int x = MAXWIDTH / 4, y = 5; // tọa độ bắt đầu vẽ bàn cờ
	gotoxy(x, y++); // dịch chuyển vào tọa độ vẽ bàn cờ
	toMau(colour.gray, colour.white); // màu bàn cờ
	// bắt đầu vẽ bàn cờ với cạnh đỉnh nối phần ô 
	cout << canh.gocTraiTren; // xuất góc trái đầu bàn cờ
	for (int i = 0; i < n; i++) {
		// xuất 3 kí tự cạnh ngang giống với kí tự '-'
		cout << canh.canhNgang;
		cout << canh.canhNgang;
		cout << canh.canhNgang;
		if (i < (n - 1))// chừa chỗ cho xuất phần góc 
			cout << canh.chuT; // kí tự giống T dùng để nối với kí tự |
	}
	cout << canh.gocPhaiTren; // là góc bàn cờ bên phải ở trên
	gotoxy(x, y++); // xuống dòng
	// xuất phần chính giữa của bàn cờ
	for (int i = 0; i < n; i++) { 
		cout << canh.canhThang; // xuất cạnh thẳng |
		for (int j = 0; j < n; j++) {
			cout << "   "; // xuất phần ruột bên trong ô
			cout << canh.canhThang; 
		}
		// tới đây là xong gần được dãy ô đầu tiên rồi
		gotoxy(x, y++);
		// đoạn này là vẽ phần đoạn nối giữa hai dãy ô với nhau
		if (i < (n - 1)) { // chừa chỗ cho phần vẽ đáy như phần đỉnh 
			// chữ T quay 90 độ ngược chiều kim đồng hồ 
			// dùng để nối kí tự '|' và '-'
			cout << canh.chuTCanhTrai;
			for (int j = 0; j < n; j++) {
				cout << canh.canhNgang;
				cout << canh.canhNgang;
				cout << canh.canhNgang;
				if (j < (n - 1))
					// phần nối giữa kí tự '-', '|' giữa hai dãy ô liên tiếp
					cout << canh.thanhGia; // nó giống với kí tự '+' 
			}
			cout << canh.chuTCanhPhai; // như canh.chuTcanhTrai nhưng ngược lại
			gotoxy(x, y++);
		}
	}
	// xuất phần cạnh đáy bàn cờ
	// tương tự với cạnh đỉnh nhưng ngược lại
	cout << canh.gocTraiDuoi;
	for (int i = 0; i < n; i++) {
		cout << canh.canhNgang;
		cout << canh.canhNgang;
		cout << canh.canhNgang;
		if (i < (n - 1))
			cout << canh.chuTnguoc;
	}
	cout << canh.gocPhaiDuoi;
}

// hàm lựa chọn ô để đánh X hoặc O
// ptr: mảng hai chiều chứa kết quả bàn cờ
// n: số lượng cột và hàng
// player: chứa kí tự của người chơi X hoặc O
// p: chứa nước đi của người chơi
// dem: số lượng nước đi đã đi và biến tăng cho mảng p để lưu nước đi tiếp theo
// choice: lưu lựa chọn là một số nằm từ 0 đến (n x n - 1)
int luaChonO(dataCell**& ptr, int n, char player, string*& p, int dem, int choice) {
	int choicePos = choice;
	char key;
	int x = MAXWIDTH /4, y = 5;
	gotoxy(0, y); // dịch chuyển con trỏ 
	cout << "luot choi: " << player; // xuất thông báo lượt chơi của X hoặc O
	
	// khai báo biến dòng là i và cột là j
	int i = 0, j = 0;
	do {
		do {
			i = choice / n;
			j = choice % n;
			gotoxy(x + 1 + (j * 4), y + 1 + (i * 2));
			cout << ">";
			// lấy giá trị kí tự nhập từ người dùng
			key = _getch();
			// xóa ô lựa chọn hiện tại để chuẩn bị di chuyển sang ô theo giá trị choice mới
			gotoxy(x + 1 + (j * 4), y + 1 + (i * 2));
			cout << " ";
			choicePos = choice; // lưu vị trí choice hiện tại
			// di chuyển sang trái
			if ((key == 'a' || key == 'A') && choice > ((choice / n)* n)) {
				choice--;
				while (ptr[choice / n][choice%n].trangThai) {
					choice--;
					// nếu di chuyển vượt quá số cột trả về vị trí hiện tại
					if (choice < ((choicePos / n)* n)) {
						choice = choicePos;
						break;
					}
				}
			}
			// di chuyển sang phải
			if ((key == 'd' || key == 'D') && (choice < ((choice / n)*n + n - 1))) {
				choice++;
				while (ptr[choice / n][choice%n].trangThai) {
					choice++;
					// nếu di chuyển vượt quá số cột trả về vị trí hiện tại
					if (choice > ((choicePos / n)*n + n - 1)) {
						choice = choicePos;
						break;
					}
				}
			}
			// di chuyển lên
			if ((key == 'w' || key == 'W') && choice >= n) {
				choice -= n;
				while (ptr[choice / n][choice%n].trangThai) {
					choice -= n;
					// nếu di chuyển vượt quá số hàng trả về vị trí hiện tại
					if (choice < 0) {
						choice = choicePos;
						break;
					}
				}
			}
			// di chuyển xuống
			if ((key == 's' || key == 'S') && choice < (n*n - n)) {
				choice += n;
				while (ptr[choice / n][choice%n].trangThai) {
					choice += n;
					// nếu di chuyển vượt quá số hàng trả về vị trí hiện tại
					if (choice > (n*n - 1)) {
						choice = choicePos;
						break;
					}
				}
			}
			// di chuyển sang đường chéo trái đi lên
			if ((key == 'q' || key == 'Q') && (choice != ((choice/n)*n) && choice > n)) {
				choice -= (n + 1);
				while (ptr[choice / n][choice%n].trangThai) {
					// nếu di chuyển đến cột và hàng đầu tiên không có ô trống thì trả về vị trí hiện tại
					if (choice == ((choice / n)*n) || choice < n) {
						choice = choicePos;
						break;
					}
					choice -= (n + 1);
					
				}
			}
			// di chuyển sang đường chéo trái đi xuống
			if ((key == 'z' || key == 'Z') && (choice != ((choice / n)*n) && choice < ((n*n) - n))) {
				choice += (n - 1);
				while (ptr[choice / n][choice%n].trangThai) {
					// nếu di chuyển đến cột đầu tiên và hàng cuối cùng không có ô trống thì trả về vị trí hiện tại
					if (choice == ((choice / n)*n) || choice > ((n*n) - n)) {
						choice = choicePos;
						break;
					}
					choice += (n - 1);
				}
			}
			// di chuyển sang đường chéo phải đi lên
			if ((key == 'e' || key == 'E') && (choice != (((choice / n)* n) + n - 1) && choice >= n)) {
				choice -= (n - 1);
				while (ptr[choice / n][choice%n].trangThai) {
					// nếu di chuyển đến cột cuối cùng và hàng đầu tiên không có ô trống thì trả về vị trí hiện tại
					if (choice == (((choice / n)* n) + n - 1) || choice < n) {
						choice = choicePos;
						break;
					}
					choice -= (n - 1);
				}
			}
			// di chuyển sang đường chéo phải đi xuống
			if ((key == 'x' || key == 'X') && (choice != (((choice / n)* n) + n - 1) && choice < ((n*n) - n - 1))) {
				choice += (n + 1);
				while (ptr[choice / n][choice%n].trangThai) {
					// nếu di chuyển đến cột cuối cùng và hàng cuối cùng không có ô trống thì trả về vị trí hiện tại
					if (choice == (((choice / n)* n) + n - 1) && choice > ((n*n) - n - 1)) {
						choice = choicePos;
						break;
					}
					choice += (n + 1);
				}
			}
			// nút cứu trường hợp bị kẹt không di chuyển được sẽ random đến bất kì ô chưa đánh
			if (key == 'h' || key == 'H') {
				do {
					choice = rand() % (n*n);
				} while (ptr[choice / n][choice%n].trangThai);
			}
		} while (key != 13); // nhan enter
	} while (ptr[choice / n][choice%n].trangThai == true); // kiểm tra xem ô chọn có đánh chưa
	// di chuyển đến tọa độ ô được chọn 
	gotoxy(x + 1 + (j * 4) + 1, y + 1 + (i * 2));
	// xuất kí tự X hoặc O
	cout << player;
	// lưu kí tự X hoặc O vào mảng hai chiều
	ptr[choice / n][choice%n].kiTu = player;
	// lưu ô chọn thành true: ô đã được đánh
	ptr[choice / n][choice%n].trangThai = true;
	// lưu vị trị đánh vào mảng string
	if (player == 'X') {
		p[dem] = "X-" + to_string(choice / n) + "-" + to_string(choice%n);
	}
	else
		p[dem] = "O-" + to_string(choice / n) + "-" + to_string(choice%n);
	return choice;
}

// màn hình sảnh game gồm các lựa chọn: bắt đầu, kỷ lục, mô phỏng bàn cờ, hướng dẫn sử dụng, thoát
int manHinhSanh() {

	dataManHinhSanh data;
	do {
		int x = (MAXWIDTH / 2) - 4, y = MAXHEIGHT / 2;
		system("cls");
		gotoxy(x-15, y/2);
		toMau(colour.black, colour.red);
		cout << "CHAO MUNG BAN DEN VOI TRO CHOI CARO 15x15" << endl;
		for (int i = 1; i <= data.MAXCHOICE; i++, y++) {
			gotoxy(x, y);
			if (i == data.choice) {
				toMau(colour.blue, colour.black);
				cout << data.arrow << data.arrow;
			}
			toMau(colour.lightYellow, colour.red);
			switch (i){
			case 1:
				cout << data.batDau;
				break;
			case 3:
				cout << data.moPhong;
				break;
			case 2:
				cout << data.kyLuc;
				break;
			case 4:
				cout << data.huongDan;
				break;
			case 5:
				cout << data.thoat;
				break;
			}
			toMau(colour.black, colour.white);
		}
		data.key = _getch();
		Beep(2000, 100);
		Sleep(100);
		if ((data.key == 'w' || data.key == 'W') && data.choice > 1) // mũi tên lên 
			data.choice--;
		if ((data.key == 's' || data.key == 'S') && data.choice < data.MAXCHOICE) // mũi tên xuống
			data.choice++;
	} while (data.key != 13);
	return data.choice;
}

// kiểm tra bàn cờ xem có người chiến thắng chưa
int checkResult(dataCell**& ptr, int n) {
	int res = -1; // -1: hòa, 0: người chơi X thắng, 1: người chơi O thắng
	char check;
	int point = 4; // số điểm cần tính thêm để thắng
	bool flag = false; // false: chưa chiến thắng, true: đã có người chiến thắng
	// duyệt qua từng ô trong bàn cờ
	for (int i = 0; i < n*n && flag == false; i++) {
		// tính một điểm tại vị trí kiểm trả cần thêm 4 điểm để thắng theo các đường phía dưới
		check = ptr[i / n][i%n].kiTu; 
		// kiểm tra dọc 
		for (int j = 1; j <= point && flag == false; j++) { 
			// nếu số hàng nhỏ hơn 5 thì không đủ để kiểm tra 
			if (i < n * point)
				break;
			// kiểm tra từ vị trị ô hiện tại giảm đi từng hàng 
			// xét từ điểm đó đi lên 
			if (ptr[(i - (j*n)) / n][(i - (j*n)) % n].kiTu != check || ptr[(i - (j*n)) / n][(i - (j*n)) % n].kiTu == ' ')
				break;
			// nếu j == point tức là ta được 5 ô liên tiếp 
			if (j == point)
				// flag true -> đã tìm ra người chiến thắng
				flag = true;
		}
		// kiểm tra ngang
		for (int j = 1; j <= point && flag == false; j++) {
			// nếu vượt quá số cột có trong hàng thì ngừng
			if (i > ((i / n)*n + n - point - 1))
				break;
			// kiểm tra từ trái sang phải
			if (ptr[(i + j) / n][(i + j) % n].kiTu != check || ptr[(i + j) / n][(i + j) % n].kiTu == ' ')
				break;
			if (j == point)
				flag = true;
		}
		// kiểm tra đường chéo
		// đường chéo phụ
		for (int j = 1; j <= point && flag == false; j++) { 
			// nếu số hàng nhỏ hơn 5 thì không đủ để kiểm tra 
			// và nếu cột ô hiện tại cách cột cuối bé hơn point thì ngắt vòng lặp
			if (i < n * point || i > ((i / n)*n + n - point - 1))
				break;
			// kiểm tra theo đường chéo từ trái sang phải đi lên
			if (ptr[((i - (j*n) + j) / n)][((i - (j*n) + j) % n)].kiTu != check || ptr[((i - (j*n) + j) / n)][((i - (j*n) + j) % n)].kiTu == ' ')
				break;
			if (j == point)
				flag = true;
		}

		// đường chéo chính
		for (int j = 1; j <= point && flag == false; j++) { 
			// nếu số hàng nhỏ hơn 5 thì không đủ để kiểm tra 
			// và nếu cột ô hiện tại cách cột đầu bé hơn point thì ngắt vòng lặp
			if (i < n * point || i < ((i / n)*n + point))
				break;
			// kiểm tra theo đường chéo từ phải sang trái đi lên
			if (ptr[((i - (j*n) - j) / n)][((i - (j*n) - j) % n)].kiTu != check || ptr[((i - (j*n) - j) / n)][((i - (j*n) - j) % n)].kiTu == ' ')
				break;
			if (j == point)
				flag = true;
		}
		if (flag == true) {
			if (check == 'X')
				return 0;
			else
				return 1;
		}
	}
	return res;
}

// man hinh bat dau la man hinh se bat dau tro choi 15x15 giua hai nguoi
res manHinhBatDau(dataCell**& ptr, int n, string*& p) {
	res resGame; // chứa giá trị của người chiến thắng
	int limit = n*n;// tổng số ô trong màn cờ
	const char X = 'X', O = 'O'; // kí tự X và O
	int choice = 0; // lưu vị trí vừa đánh trong bàn cờ
	veBanCo(); // vẽ bàn cờ
	do {
		// các giá trị của resGame.winner
		// -1: hòa, 0: người chơi X thắng, 1: người chơi O thắng
		resGame.winner = -1; 
		// X chơi trước, nếu đếm là số chẵn sẽ là lươt X
		if (resGame.dem % 2 == 0)
			choice = luaChonO(ptr, n, X, p, resGame.dem, choice);
		// ngược lại
		else
			choice = luaChonO(ptr, n, O, p, resGame.dem, choice);
		resGame.dem++; // sau khi đánh thì tăng số ô đã đánh
		// kiểm tra kết quả có ai thắng không
		resGame.winner = checkResult(ptr, n);
		// nếu resGame.winner là 0 hoặc 1 trả giá trị về
		if (resGame.winner != -1) {
			toMau(colour.black, colour.white);
			return resGame;
		}
	} while (resGame.dem < limit); // lặp lại cho đến khi đánh hết ô trong bàn cờ
	toMau(colour.black, colour.white);
	return resGame;
}

// màn hình của lựa chọn kỷ lục
void manHinhKyLuc(int diemX, int diemO) {
	int x = MAXWIDTH / 3, y = MAXHEIGHT / 2;
	system("cls");
	gotoxy(x, y++);
	toMau(colour.blue, colour.red);
	// điểm của người chơi X
	cout << "DIEM CUA NGUOI CHOI X: " << diemX;
	gotoxy(x, y++);
	// điểm của người chơi O
	cout << "DIEM CUA NGUOI CHOI O: " << diemO;
	gotoxy(x, y);
	// thông báo nhấn nút bất kì để thoát
	// chờ người dùng nhấn để thoát
	toMau(colour.black, colour.white);
	cout << "nhan nut bat ki de thoat";
	char key = _getch();
	Beep(2000, 100);
}

void manHinhThongBaoWinner(int res) {
	system("cls");
	int x = MAXWIDTH / 3, y = MAXHEIGHT / 2;
	toMau(colour.aqua, colour.red);
	gotoxy(x, y++);
	cout << "CHUC MUNG NGUOI CHOI ";
	if (res == 0)
		cout << "X";
	else
		cout << "O";
	cout << " DA CHIEN THANG";
	gotoxy(x, y++);
	toMau(colour.black, colour.white);
	cout << "nhan nut bat ki de thoat";
	char key = _getch();
	Beep(2000, 100);
}

// màn hình xuất ra cách sử dụng các nút để sử dụng
void manHinhHuongDan() {

	int x = MAXWIDTH / 3, y = MAXHEIGHT / 2;
	system("cls");
	gotoxy(x, y++);
	toMau(colour.aqua, colour.red);
	cout << "nut A dung de di chuyen sang trai";
	gotoxy(x, y++);
	cout << "nut D dung de di chuyen sang phai";
	gotoxy(x, y++);
	cout << "nut W dung de di chuyen len tren";
	gotoxy(x, y++);
	cout << "nut S dung de di chuyen xuong duoi";
	gotoxy(x, y++);
	cout << "nut Q dung de di chuyen cheo sang trai di len";
	gotoxy(x, y++);
	cout << "nut E dung de di chuyen cheo sang phai di len";
	gotoxy(x, y++);
	cout << "nut Z dung de di chuyen cheo sang trai di xuong";
	gotoxy(x, y++);
	cout << "nut X dung de di chuyen cheo sang phai di xuong";
	gotoxy(x, y++);
	cout << "nut H hoac mui ten len dung de dich chuyen vao truong hop bi ket";
	gotoxy(x, y++);
	cout << "nut enter dung de chon o cua ban co de danh";
	gotoxy(x, y++);
	toMau(colour.black, colour.white);
	cout << "nhan nut bat ki de thoat";
	char key = _getch();
	Beep(2000, 100);
}
// ghi lại các nước đi vào file csv
void ghiFile(string* p, int dem) {

	ofstream outputFile("dataCaro.csv", ios::out);

	if (outputFile.is_open()) {
		outputFile << "15x15" << ";";
		for (int i = 0; i < dem; i++) {
			outputFile << p[i] << ";";
		}
	}

	outputFile.close();
}

// đọc dữ liệu từ file csv lưu ván cờ vừa chơi để mô phỏng
int docFile(char arr[][8]) {
	int dem = 0;
	ifstream iff;
	char ok[100000];
	iff.open("dataCaro.csv", ios::in);
	iff >> ok;
	int i;
	for (char* ptok = strtok(ok, ";"); ptok != NULL; ptok = strtok(NULL, ";")) {
		for (i = 0; i < static_cast<int>(strlen(ptok)); i++) {
			arr[dem][i] = ptok[i];
		}
		arr[dem][i] = '\0';
		dem++;
	}
	iff.close();
	return dem;
}

// mô phỏng ván cờ vừa chơi
void moPhongBanCo(bool flag) {
	// kiểm tra xem đã chơi ván cờ chưa
	// nếu chưa thông báo chưa có dữ liệu bàn cờ
	if (flag == false) {
		system("cls");
		int x = MAXWIDTH / 2, y = MAXHEIGHT / 2;
		gotoxy(x, y);
		cout << "CHUA CO DU LIEU BAN CO!" << endl;
	}
	// nếu có rồi sẽ thực hiện mô phỏng bàn cờ
	else{
		int x = MAXWIDTH / 4, y = 5;
		// vẽ bàn cờ chuẩn bị xuất nước đi
		veBanCo();
		char res[225][8]; // mảng chứa hai chiều gồm 225 hàng chứa 8 kí tự
		int dem = docFile(res); // đọc file và trả về số lượng được đánh
		// duyệt qua các phần từ mảng hai chiều 
		for (int i = 1; i < dem; i++) {
			// lưu vị trí ô đánh
			pair<int, int> pos;
			// lưu nước đi ô đánh
			char a[8];
			// làm mới ô mảng a chuẩn bị nhập nước đi kế tiếp
			for (int j = 0; j < 8; j++)
				a[j] = ' ';
			// lấy kí tự đầu tiên là kí tự đánh của người chơi X hoặc O
			char player = res[i][0];
			gotoxy(0, y);
			// xuất lượt chơi 
			cout << "luot choi: " << player;
			// gán các kí tự vào mảng a
			for (int j = 0; res[i][j] != '\0'; j++)
				a[j] = res[i][j];
			// kí tự là 1 là số hàng 
			// kí tự là 2 là số cột
			int kiTu = 0;
			for (char* ptok = strtok(a, "-"); ptok != NULL; ptok = strtok(NULL, "-"), kiTu++) {
				if (kiTu == 1)
					pos.first = atoi(ptok); // lấy số hàng
				else if (kiTu == 2)
					pos.second = atoi(ptok); // lấy số cột
			}
			// di chuyển đến vị trị các ô trong bàn cờ 
			gotoxy(x + 1 + (pos.second * 4) + 1, y + 3 + ((pos.first - 1) * 2));
			// xuất kí tự X hoặc O
			cout << player;
			// hàm ngủ khoảng 2000 mili giây rồi tiếp tục xuất nước đi tiếp theo
			Sleep(2000);
			
		}
	}
	// sau khi kết thúc thì nhấn một nút bất kì để thoát
	gotoxy(MAXWIDTH/2, MAXHEIGHT-2);
	cout << "nhan nut bat ki de thoat";
	char key = _getch();
	Beep(2000, 100);
	toMau(colour.black, colour.white);
}

