
// Eren ÞAHAN 172114023
// Varsayýlan kullanýcý adý ve þifer admin admin'dir.
// Ayarlarý içeren dosya silindiði taktirde kullanýcý adý ve þifre sýfýrlanmaktadýr.

// Default username and password: admin

#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;

HANDLE renk = GetStdHandle(STD_OUTPUT_HANDLE);	// Ýmleç Renk
COORD destCoord;									// ve Hareket


string getpassword(const string& prompt = "")  //http://www.cplusplus.com/forum/general/3570/
{
	string result;

	// Set the console mode to no-echo, not-line-buffered input
	DWORD mode, count;
	HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleMode(ih, &mode))
		throw runtime_error(
			"getpassword: You must be connected to a console to use this program.\n"
		);
	SetConsoleMode(ih, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

	// Get the password string
	WriteConsoleA(oh, prompt.c_str(), prompt.length(), &count, NULL);
	char c;
	while (ReadConsoleA(ih, &c, 1, &count, NULL) && (c != '\r') && (c != '\n'))
	{
		if (c == '\b')
		{
			if (result.length())
			{
				WriteConsoleA(oh, "\b \b", 3, &count, NULL);
				result.erase(result.end() - 1);
			}
		}
		else
		{
			WriteConsoleA(oh, "*", 1, &count, NULL);
			result.push_back(c);
		}
	}

	// Restore the console mode
	SetConsoleMode(ih, mode);

	return result;
}


int button();
int button2();
fstream file1, file2;
bool capscontrol();
void cursor_move(int x, int y);
void welcome();
void menu_1();
void admin_login();
void std_singup_guest();
void main_menu();
void std_singup_admin();
void confirm_std();
void std_info_change();
void new_pas();


int state; //Basýlan tuþu algýlamayla ilgili bir deðiþken
int pos, readed;

//CLASSES
class setup
{
	string username;
	string password;
	string temp_username;
	string temp_password;
public:
	int ogrid, temp_ogrid;
	string temp;
	fstream file1, file2;
	fstream tempdosya;
	setup();
	void girisyap();
}s;
setup::setup()
{
	file1.open("Ogrenci _Servis_Firmasý_Otomasyonu_Proje.bin");
	if (file1.is_open())
	{
		file1 >> username;
		file1 >> password;
		file1 >> ogrid;
		file1 >> temp_ogrid;
		file1.close();
	}
	else
	{
		cout << "setting acilmadi\nayarlar sifirlaniyor...\nProgram kapatiliyor.";
		file1.open("Ogrenci _Servis_Firmasý_Otomasyonu_Proje.bin", ios::out);
		file1 << "admin\tadmin\t100\t10";
		file1.close();
		file2.open("Ogrenci _Servis_Firmasý_Otomasyonu_Proje.bin", ios::in);
		file2 >> username;
		file2 >> password;
		file2 >> ogrid;
		file2 >> temp_ogrid;
		file2.close();
		Sleep(2000);
		exit(0);
	}
	file1.close();

	file1.open("storage.bin", ios::in);
	while (!file1.eof())
	{
		cout << 1;
		file1 >> ogrid;
		file1 >> temp;
		file1 >> temp;
		file1 >> temp;
		file1 >> temp;
		file1 >> temp;
		file1 >> temp;
	}
	file1.close();
	file1.open("waiting_storage.bin", ios::in);
	while (!file1.eof())
	{
		cout << 2;
		file1 >> temp_ogrid;
		file1 >> temp;
		file1 >> temp;
		file1 >> temp;
		file1 >> temp;
		file1 >> temp;
		file1 >> temp;
	}
	file1.close();
}
void setup::girisyap()
{
	/*
	cursor_move(0, 20);
	cout << username << endl << password << endl;   // Geçerli username ve passwordu gösterir.
	*/

	pos = 1;
label:

	while (true)
	{

		state = button();
		if (state == 4 && pos < 2)
		{
			pos++;
		}
		if (state == 3 && pos > 1)
		{
			pos--;
		}
		if (state == 7)
		{
			break;
		}
		if (pos == 1)
		{
			cursor_move(7, 14);
			SetConsoleTextAttribute(renk, 241);
			cout << "{*}> ";
			SetConsoleTextAttribute(renk, 31);
			cout << "Kullanýcý Adý: ";
		}
		else
		{
			cursor_move(7, 14);
			cout << "     Kullanýcý Adý: ";
		}

		if (pos == 2)
		{
			cursor_move(1, 19);
			SetConsoleTextAttribute(renk, 241);
			cout << "{*}> ";
			SetConsoleTextAttribute(renk, 31);
			cout << "Geri Dön";
		}
		else
		{
			cursor_move(1, 19);
			cout << "     Geri Dön";
		}
		Sleep(200);
	}
	if (pos == 1)
	{
		cursor_move(7, 14);
		SetConsoleTextAttribute(renk, 31);
		cout << "{*}> ";
		SetConsoleTextAttribute(renk, 241);
		cout << "Kullanýcý Adý:";
		SetConsoleTextAttribute(renk, 31);
		cout << " ";
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); //Daha önceden basýlan tuþlarý geçersiz kýlýyor.
		cursor_move(27, 14);
		cin >> temp_username;
		cursor_move(12, 14);
		cout << "Kullanýcý Adý: ";

		if (capscontrol())
		{
			cursor_move(46, 17);
			SetConsoleTextAttribute(renk, 111);
			cout << "Caps Lock açýk olabilir!!!";
		}
		else
		{
			cursor_move(46, 17);
			SetConsoleTextAttribute(renk, 31);
			cout << "                          ";
		}
		cursor_move(12, 16);
		SetConsoleTextAttribute(renk, 241);
		cout << "Þifre:";
		SetConsoleTextAttribute(renk, 31);
		cout << " ";
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		cursor_move(19, 16);
		temp_password = getpassword();
		cursor_move(12, 16);
		cout << "Þifre: ";

		cursor_move(46, 17);
		SetConsoleTextAttribute(renk, 31);
		cout << "                          ";
		goto label2;
	}
	else if (pos == 2)
	{
		menu_1();
	}

	else
	{
		system("cls");
		cout << " HATA " << endl;
		admin_login();
	}
	goto label;
label2:
	if (temp_username == username && temp_password == password)
	{
		cursor_move(8, 12);
		system("color 2f");
		cout << "Giris basarýlý";
		cursor_move(0, 22);
		Sleep(1500);
		main_menu();
	}
	else
	{
		cursor_move(8, 12);
		cout << "Kullanýcý adý veya þifreniz yanlýþ!!! Lütfen tekrar deneyiniz.";
		for (int i = 0; i < 7; i++)
		{
			if (i % 2 == 0)
			{
				system("color 4f");
			}
			else
			{
				system("color 1f");
			}
			Sleep(300);
		}

		admin_login();
	}
}


struct ogrenci
{
	string ad;
	string soyad;
	string adres;
	int mesafe;
	string sinif;
	string tel;

}ogr, ogr1, ogr2, ogr3, ogr4, ogr5;


///////////////////////////////////////////////////////////////////////
int main()
{
	SetConsoleTitle(TEXT("ÞAHAN Turizim")); //Konsol Baþlýðý
	setlocale(LC_ALL, "Turkish");  //Türkçe karakter tanýmlama kodu

	welcome();

	system("MODE CON: COLS=116 LINES=30");

	menu_1();

	return 0;
}
///////////////////////////////////////////////////////////////////////

int button()
{
	if (GetAsyncKeyState(VK_LEFT)) // SOL OK
	{
		return 1;
	}
	else if (GetAsyncKeyState(VK_RIGHT)) // SAÐ OK
	{
		return 2;
	}
	else if (GetAsyncKeyState(VK_UP)) // YUKARI OK
	{
		return 3;
	}
	else if (GetAsyncKeyState(VK_DOWN)) // AÞAÐI OK
	{
		return 4;
	}
	else if (GetAsyncKeyState(VK_RETURN)) // ENTER
	{
		return 5;
	}
	else if (GetAsyncKeyState(VK_SPACE)) //SPACE
	{
		return 6;
	}
	else if (GetAsyncKeyState(VK_CONTROL)) //CONTROL
	{
		return 7;
	}
	else if (GetAsyncKeyState(VK_ESCAPE)) //ESCAPE(ESC)
	{
		return 9;
	}
	return 0;
}
int button2()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // SOL OK
	{
		return 1;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) // SAÐ OK
	{
		return 2;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000) // YUKARI OK
	{
		return 3;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) // AÞAÐI OK
	{
		return 4;
	}
	else if (GetAsyncKeyState(VK_RETURN) & 0x8000) // ENTER
	{
		return 5;
	}
	else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) //ESCAPE(ESC)
	{
		return 9;
	}
	else if (GetAsyncKeyState(VK_SPACE) & 0x8000) //SPACE
	{
		return 6;
	}
	return 0;
}
bool capscontrol()
{
	if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
		return true;
	else
		return false;
}
void cursor_move(int x, int y)
{
	destCoord.X = x;
	destCoord.Y = y;
	SetConsoleCursorPosition(renk, destCoord);
}

void welcome()
{
	system("MODE CON: COLS=75 LINES=50");
	system("cls");
	SetConsoleTextAttribute(renk, 14);
	cout << "         XX                                                      XX" << endl
		<< "       XX                                                          XX" << endl
		<< "      XX                                                            XX" << endl
		<< "     XX                                                              XX" << endl
		<< "    XX                                                        X       XX" << endl
		<< "   XX                                                   XX     XX      XX" << endl
		<< "  XX                                                      XXX    XX     XX" << endl
		<< " XX      XX   XX                                             XX         XX" << endl
		<< " XX    XX   XX                                                 XX        XX" << endl
		<< "XX    X    X                  ";
	SetConsoleTextAttribute(renk, 11);
	cout << "Bir Kedi Gördüm Sanki";
	SetConsoleTextAttribute(renk, 14);
	cout << "             XX       XX" << endl
		<< "XX   X    X                                                               X" << endl
		<< "X   X    X                                                                X" << endl
		<< "X       X              8                                 8                X" << endl
		<< "X                       8                               8                 X" << endl
		<< "X                  8     8                             8   8              X" << endl
		<< "X                   8  8  8                           8  8   8            X" << endl
		<< "X                    8  8  8                         8  8  88             X" << endl
		<< "X                     8  8  8                       XXXX  8               X" << endl
		<< "X                      8 XXXX                       XXXXX8                X" << endl
		<< "XX                      XXXXXX                    XXXXXXXX               XX" << endl
		<< "XX                     XXXXXXXX                  XXXXXXXXXX              XX" << endl
		<< "XX                    XXXXXXXXXX                XXXXXXXXXXXX             XX" << endl
		<< " XX                  XXXXXXXXXXXX               XXXXXXXXXXXXX           XX" << endl
		<< "  XX                 XXXXXXXXXXXXX             XXXXXXXXXXXXXX          XX" << endl
		<< "  XX                XXXXXXXXXXXXXX            XXXXXXXXXXXXXXX          XX" << endl
		<< "  XX                XXXXXXXXXXXXXX           XXXXXXXXXXXXXXXX          XX" << endl
		<< "   XX              XXXXXXXXXXXXXXX           XXXXXXXXXXXXXXXX         XX" << endl
		<< "    XX             XXXXXXXXXXXXXXX           XXXXXXX    XXXXX        XX" << endl
		<< "     XX            XXXXXXX   XXXXX           XXXXXX      XXXX       XX" << endl
		<< "     XX            XXXXXX     XXX            XXXXX       XXXX       XX" << endl
		<< "      XX           XXXXX  88  XXXX           XXXX   88   XXX       XX" << endl
		<< "      XX           XXXX  8888  XX            XXXX  8888  XXX       XX" << endl
		<< "       XX          XXXX  8888 XXX            XXXX  8888 XXX       XX" << endl
		<< "        XX         XXXXX  88 XXX              XXXX  88 XXX       XX" << endl
		<< "          XX        XXXX    XXX               XXXX    XXX       XX" << endl
		<< "           XXX       XXXXXXXXX                 XXXXXXXXX       XXX" << endl
		<< "           XX          XXXXX      XXXXXXXXXXX    XXXXX           XX" << endl
		<< "          XXX           XX    XXXX           XXX  XX             XXX" << endl
		<< "          XX                XX XXXXX          XXXXX                XX" << endl
		<< "          XX               X  XX    XXXX  XXXX  XXXX   XXXX        XX" << endl
		<< "          XX                    XXX     XX     XX   XXX    X       XX" << endl
		<< "          XX                       XXX     XXX                    XX" << endl
		<< "           XX                         XXXXX                     XXX" << endl
		<< "             XX                                               XXX" << endl
		<< "              XXXXX                                        XXXX" << endl
		<< "                   XXXXXXXXXXX                     XXXXXXXX" << endl
		<< "                              XXXX             XXXX" << endl
		<< "                                 XX           XX" << endl
		<< "                                  XX         XX" << endl
		<< "                                  XX         XX ";
	Sleep(2500);

}
void menu_1()
{
	system("MODE CON: COLS=116 LINES=30");
	system("color a");

	cursor_move(100, 0);
	SetConsoleTextAttribute(renk, 15);
	system("echo %date%");

	SetConsoleTextAttribute(renk, 1);
	cursor_move(1, 2);
	cout << "888    888  .d88888b.   .d8888b.   .d8888b.  8888888888 888      8888888b. 8888888 888b    888 8888888 8888888888P\n";
	SetConsoleTextAttribute(renk, 9);
	cursor_move(1, 3);
	cout << "888    888 d88P\" \"Y88b d88P  Y88b d88P  Y88b 888        888      888  \"Y88b  888   8888b   888   888         d88P\n";
	SetConsoleTextAttribute(renk, 3);
	cursor_move(1, 4);
	cout << "888    888 888     888 Y88b.      888    888 888        888      888    888  888   88888b  888   888        d88P\n";
	SetConsoleTextAttribute(renk, 4);
	cursor_move(1, 5);
	cout << "8888888888 888     888  \"Y888b.   888        8888888    888      888    888  888   888Y88b 888   888       d88P\n";
	SetConsoleTextAttribute(renk, 12);
	cursor_move(1, 6);
	cout << "888    888 888     888     \"Y88b. 888  88888 888        888      888    888  888   888 Y88b888   888      d88P\n";
	SetConsoleTextAttribute(renk, 5);
	cursor_move(1, 7);
	cout << "888    888 888     888       \"888 888    888 888        888      888    888  888   888  Y88888   888     d88P\n";
	SetConsoleTextAttribute(renk, 13);
	cursor_move(1, 8);
	cout << "888    888 Y88b. .d88P Y88b  d88P Y88b  d88P 888        888      888  .d88P  888   888   Y8888   888    d88P\n";
	SetConsoleTextAttribute(renk, 6);
	cursor_move(1, 9);
	cout << "888    888  \"Y88888P\"   \"Y8888P\"   \"Y8888P88 8888888888 88888888 8888888P\" 8888888 888    Y888 8888888 d8888888888\n\n\n";
	SetConsoleTextAttribute(renk, 10);
	cout << "--------------------------------------------------------------------------------------------------------------------\n";
	cout << "=================================================|| YÖNETÝCÝ GÝRÝÞÝ ||==============================================\n";
	cout << "--------------------------------------------------------------------------------------------------------------------\n";
	cout << "=================================================|| Yeni Kayýt Ekle ||==============================================\n";
	cout << "--------------------------------------------------------------------------------------------------------------------\n";
	cout << "=================================================|| Çýkýþ Yap       ||==============================================\n";
	cout << "--------------------------------------------------------------------------------------------------------------------\n";

	int i = 9;
	int x = 103, y = 28;
	int x2 = 112;
	int pos = 1;
	cursor_move(x, y - 3);
	cout << "  __";
	cursor_move(x, y - 2);
	cout << "<(o )___";
	cursor_move(x, y - 1);
	cout << " ( ._> /";
	cursor_move(x, y);
	cout << "  `---'";
	cursor_move(x + 9, y - 2);
	cout << "  _      _      _";
	cursor_move(x + 9, y - 1);
	cout << ">(.)__ <(.)__ =(.)__";
	cursor_move(x + 9, y);
	cout << " (___/  (___/  (___/";



	SetConsoleTextAttribute(renk, 10);
	cursor_move(0, 29);
	for (int i = 0; i < 116; i++)
	{
		cout << "/";
	}
	while (true)
	{
		cursor_move(0, 25);
		for (int i = 0; i < 116; i++)
		{
			SetConsoleTextAttribute(renk, 10);
			cout << " ";
		}
		cursor_move(0, 26);
		for (int i = 0; i < 116; i++)
		{
			SetConsoleTextAttribute(renk, 10);
			cout << " ";
		}
		cursor_move(0, 27);
		for (int i = 0; i < 116; i++)
		{
			SetConsoleTextAttribute(renk, 10);
			cout << " ";
		}
		cursor_move(0, 28);
		for (int i = 0; i < 116; i++)
		{
			SetConsoleTextAttribute(renk, 10);
			cout << " ";
		}
		SetConsoleTextAttribute(renk, 4);
		cursor_move(x, y - 3);
		cout << "  __";
		cursor_move(x, y - 2);
		cout << "<(o )___";
		cursor_move(x, y - 1);
		cout << " ( ._> /";
		cursor_move(x, y);
		cout << "  `---'";
		SetConsoleTextAttribute(renk, 10);
		cursor_move(x2, y - 2);
		cout << "  _      _      _";
		cursor_move(x2, y - 1);
		cout << ">(.)__ <(.)__ =(.)__";
		cursor_move(x2, y);
		cout << " (___/  (___/  (___/";
		x--;
		x2--;
		if (x < 0)
		{
			x = 112;
		}
		if (x2 < 0)
		{
			x2 = 112;
		}

		i++;
		if (i == 15)
			i = 9;
		SetConsoleTextAttribute(renk, i);
		cursor_move(1, 2);
		cout << "888    888  .d88888b.   .d8888b.   .d8888b.  8888888888 888      8888888b. 8888888 888b    888 8888888 8888888888P\n";
		i++;
		if (i == 15)
			i = 9;
		SetConsoleTextAttribute(renk, i);
		cursor_move(1, 3);
		cout << "888    888 d88P\" \"Y88b d88P  Y88b d88P  Y88b 888        888      888  \"Y88b  888   8888b   888   888         d88P\n";
		i++;
		if (i == 15)
			i = 9;
		SetConsoleTextAttribute(renk, i);
		cursor_move(1, 4);
		cout << "888    888 888     888 Y88b.      888    888 888        888      888    888  888   88888b  888   888        d88P\n";
		i++;
		if (i == 15)
			i = 9;
		SetConsoleTextAttribute(renk, i);
		cursor_move(1, 5);
		cout << "8888888888 888     888  \"Y888b.   888        8888888    888      888    888  888   888Y88b 888   888       d88P\n";
		i++;
		if (i == 15)
			i = 9;
		SetConsoleTextAttribute(renk, i);
		cursor_move(1, 6);
		cout << "888    888 888     888     \"Y88b. 888  88888 888        888      888    888  888   888 Y88b888   888      d88P\n";
		i++;
		if (i == 15)
			i = 9;
		SetConsoleTextAttribute(renk, i);
		cursor_move(1, 7);
		cout << "888    888 888     888       \"888 888    888 888        888      888    888  888   888  Y88888   888     d88P\n";
		i++;
		if (i == 15)
			i = 9;
		SetConsoleTextAttribute(renk, i);
		cursor_move(1, 8);
		cout << "888    888 Y88b. .d88P Y88b  d88P Y88b  d88P 888        888      888  .d88P  888   888   Y8888   888    d88P\n";
		i++;
		if (i == 15)
			i = 9;
		SetConsoleTextAttribute(renk, i);
		cursor_move(1, 9);
		cout << "888    888  \"Y88888P\"   \"Y8888P\"   \"Y8888P88 8888888888 88888888 8888888P\" 8888888 888    Y888 8888888 d8888888888\n";




		state = button();
		if (state == 4 && pos < 3)
		{
			pos++;
		}
		if (state == 3 && pos > 1)
		{
			pos--;
		}
		if (state == 7)
		{
			break;
		}
		if (pos == 1)
		{
			cursor_move(49, 13);
			SetConsoleTextAttribute(renk, 240);
			cout << "|| YÖNETÝCÝ GÝRÝÞÝ ||";
			SetConsoleTextAttribute(renk, 10);
		}
		else
		{
			cursor_move(49, 13);
			SetConsoleTextAttribute(renk, 10);
			cout << "|| YÖNETÝCÝ GÝRÝÞÝ ||";
		}
		if (pos == 2)
		{
			cursor_move(49, 15);
			SetConsoleTextAttribute(renk, 240);
			cout << "|| Yeni Kayýt Ekle ||";
			SetConsoleTextAttribute(renk, 10);
		}
		else
		{
			cursor_move(49, 15);
			SetConsoleTextAttribute(renk, 10);
			cout << "|| Yeni Kayýt Ekle ||";
		}
		if (pos == 3)
		{
			cursor_move(49, 17);
			SetConsoleTextAttribute(renk, 240);
			cout << "|| Çýkýþ Yap       ||";
			SetConsoleTextAttribute(renk, 10);

		}
		else
		{
			cursor_move(49, 17);
			SetConsoleTextAttribute(renk, 10);
			cout << "|| Çýkýþ Yap       ||";
		}
		cursor_move(2, 20);
		SetConsoleTextAttribute(renk, 15);
		cout << "Yön tuþlarý ile hareketi, Ctrl ile seçimi gerçekleþtirebilirsiniz.";
		cursor_move(1, 21);
		SetConsoleTextAttribute(renk, 4);
		cout << "Þ";
		SetConsoleTextAttribute(renk, 6);
		cout << "A";
		SetConsoleTextAttribute(renk, 10);
		cout << "H";
		SetConsoleTextAttribute(renk, 1);
		cout << "A";
		SetConsoleTextAttribute(renk, 13);
		cout << "N";
		SetConsoleTextAttribute(renk, 14);
		cout << " Company";
		cursor_move(0, 0);
		Sleep(50);



	}
	if (pos == 1)
	{
		admin_login();
	}
	else if (pos == 2)
	{
		std_singup_guest();
	}
	else if (pos == 3)
	{
		exit(0);
	}
	else
	{
		system("cls");
		cout << " HATA " << endl << endl;
		Sleep(3000);
		menu_1();
	}


}
void admin_login()
{
	system("cls");
	system("MODE CON: COLS=85 LINES=23");
	system("color 1f");
	HANDLE hStdout;
	COORD destCoord;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	system("color 1f");
	{
		cursor_move(20, 2);
		cout << ".d8888b.	 d8b             d8b";
		cursor_move(20, 3);
		cout << "d88P  Y88b   Y8P             Y8P";
		cursor_move(20, 4);
		cout << "888    888";
		cursor_move(20, 5);
		cout << "888          888   888d888   888   .d8888b";
		cursor_move(20, 6);
		cout << "888  88888   888   888P\"     888   88K      ";
		cursor_move(20, 7);
		cout << "888    888   888   888       888   \"Y8888b. ";
		cursor_move(20, 8);
		cout << "Y88b  d88P   888   888       888        X88";
		cursor_move(20, 9);
		cout << " \"Y8888P88   888   888       888    88888P\'";
	}

	cursor_move(12, 14);
	cout << "Kullanýcý Adý: ";
	cursor_move(12, 16);
	cout << "Þifre: ";
	cursor_move(6, 19);
	cout << "Geri Dön";
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); //Daha önceden basýlan tuþlarý geçersiz kýlýyor.

	s.girisyap();
}
void std_singup_guest()
{
	if (s.temp_ogrid < 15)
	{
		system("cls");
		system("color 2f");
		system("MODE CON: COLS=95 LINES=25");

		ogr.ad = "empty";
		ogr.soyad = "empty";
		ogr.adres = "empty";
		ogr.mesafe = 0;
		ogr.sinif = "empty";
		ogr.tel = "empty";


		for (int i = 0; i < 95; i++)
		{
			SetConsoleTextAttribute(renk, 34);
			cout << " ";
		}
		for (int i = 0; i < 23; i++)
		{
			SetConsoleTextAttribute(renk, 34);
			cout << "  ";
			for (int j = 0; j < 91; j++)
			{
				SetConsoleTextAttribute(renk, 170);
				cout << " ";
			}
			SetConsoleTextAttribute(renk, 34);
			cout << "  ";
			cout << endl;
		}
		for (int i = 0; i < 95; i++)
		{
			SetConsoleTextAttribute(renk, 34);
			cout << " ";
		}

		SetConsoleTextAttribute(renk, 96);
		int y = 7;
		for (int j = 0; j < 12; j++)
		{
			cursor_move(6, y);
			for (int i = 0; i < 83; i++)
			{
				cout << " ";
			}
			y++;
		}
		SetConsoleTextAttribute(renk, 175);
		cursor_move(6, 4);
		cout << "Lütfen yeni öðrencinin bilgilerini giriniz. Yetkili tarafýndan kontrol edilecektir.";
		cursor_move(22, 19);
		cout << " __________";
		cursor_move(22, 20);
		cout << "|          |";
		cursor_move(22, 21);
		cout << "|   GERÝ   |";
		cursor_move(22, 22);
		cout << "|__________|";

		cursor_move(55, 19);
		cout << " ____________";
		cursor_move(55, 20);
		cout << "|            |";
		cursor_move(55, 21);
		cout << "|   Kaydet   |";
		cursor_move(55, 22);
		cout << "|____________|";

		SetConsoleTextAttribute(renk, 96);
		cursor_move(10, 8);
		cout << "Ýsim:";
		cursor_move(50, 8);
		cout << "Soyisim:";
		cursor_move(10, 12);
		cout << "Sýnýfý:";
		cursor_move(50, 12);
		cout << "Telefon Numarasý:";
		cursor_move(10, 16);
		cout << "Adresi(Semt):";
		cursor_move(50, 16);
		cout << "Mesafe(metre):";

		pos = 7;
		while (true)
		{
		label:


			state = button();
			if (state == 2 && pos < 8)
			{
				if (pos == 6)
					continue;
				pos++;
			}
			if (state == 1 && pos > 1)
			{
				if (pos == 7)
					continue;
				pos--;
			}
			if (state == 3 && pos < 9)
			{
				if (pos == 1 || pos == 2)
					continue;
				pos -= 2;
			}
			if (state == 4 && pos < 8)
			{
				if (pos == 7 || pos == 8)
					continue;
				pos += 2;
			}
			if (state == 7)
			{
				break;
			}

			if (pos == 1)
			{
				cursor_move(6, 8);
				SetConsoleTextAttribute(renk, 250);
				cout << "{*}>";
			}
			else
			{
				cursor_move(6, 8);
				SetConsoleTextAttribute(renk, 96);
				cout << "    ";
			}
			if (pos == 2)
			{
				cursor_move(46, 8);
				SetConsoleTextAttribute(renk, 250);
				cout << "{*}>";
			}
			else
			{
				cursor_move(46, 8);
				SetConsoleTextAttribute(renk, 96);
				cout << "    ";
			}
			if (pos == 3)
			{
				cursor_move(6, 12);
				SetConsoleTextAttribute(renk, 250);
				cout << "{*}>";
			}
			else
			{
				cursor_move(6, 12);
				SetConsoleTextAttribute(renk, 96);
				cout << "    ";
			}
			if (pos == 4)
			{
				cursor_move(46, 12);
				SetConsoleTextAttribute(renk, 250);
				cout << "{*}>";
			}
			else
			{
				cursor_move(46, 12);
				SetConsoleTextAttribute(renk, 96);
				cout << "    ";
			}
			if (pos == 5)
			{
				cursor_move(6, 16);
				SetConsoleTextAttribute(renk, 250);
				cout << "{*}>";
			}
			else
			{
				cursor_move(6, 16);
				SetConsoleTextAttribute(renk, 96);
				cout << "    ";
			}
			if (pos == 6)
			{
				cursor_move(46, 16);
				SetConsoleTextAttribute(renk, 250);
				cout << "{*}>";
			}
			else
			{
				cursor_move(46, 16);
				SetConsoleTextAttribute(renk, 96);
				cout << "    ";
			}
			if (pos == 7)
			{
				SetConsoleTextAttribute(renk, 250);
				cursor_move(22, 20);
				cout << "|          |";
				cursor_move(22, 21);
				cout << "|   GERÝ   |";
				cursor_move(22, 22);
				cout << "|__________|";
			}
			else
			{
				SetConsoleTextAttribute(renk, 175);
				cursor_move(22, 20);
				cout << "|          |";
				cursor_move(22, 21);
				cout << "|   GERÝ   |";
				cursor_move(22, 22);
				cout << "|__________|";
			}
			if (pos == 8)
			{
				SetConsoleTextAttribute(renk, 250);
				cursor_move(55, 20);
				cout << "|            |";
				cursor_move(55, 21);
				cout << "|   Kaydet   |";
				cursor_move(55, 22);
				cout << "|____________|";
			}
			else
			{
				SetConsoleTextAttribute(renk, 175);
				cursor_move(55, 20);
				cout << "|            |";
				cursor_move(55, 21);
				cout << "|   Kaydet   |";
				cursor_move(55, 22);
				cout << "|____________|";
			}
			Sleep(200);
		}
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		if (pos == 1)
		{
			cursor_move(16, 8);
			SetConsoleTextAttribute(renk, 224);
			cout << setw(29) << " ";
			cursor_move(16, 8);
			cin >> setw(29) >> ogr.ad;
			SetConsoleTextAttribute(renk, 96);
			cursor_move(16, 8);
			cout << left << setw(29) << ogr.ad;
			goto label;
		}
		if (pos == 2)
		{
			cursor_move(59, 8);
			SetConsoleTextAttribute(renk, 224);
			cout << setw(25) << " ";
			cursor_move(59, 8);
			cin >> setw(25) >> ogr.soyad;
			SetConsoleTextAttribute(renk, 96);
			cursor_move(59, 8);
			cout << left << setw(25) << ogr.soyad;
			goto label;
		}
		if (pos == 3)
		{
			cursor_move(18, 12);
			SetConsoleTextAttribute(renk, 224);
			cout << setw(27) << " ";
			cursor_move(18, 12);
			cin >> setw(27) >> ogr.sinif;
			SetConsoleTextAttribute(renk, 96);
			cursor_move(18, 12);
			cout << left << setw(27) << ogr.sinif;
			goto label;
		}
		if (pos == 4)
		{
			cursor_move(68, 12);
			SetConsoleTextAttribute(renk, 224);
			cout << setw(16) << " ";
			cursor_move(68, 12);
			cin >> setw(16) >> ogr.tel;
			SetConsoleTextAttribute(renk, 96);
			cursor_move(68, 12);
			cout << left << setw(16) << ogr.tel;
			goto label;
		}
		if (pos == 5)
		{
			cursor_move(24, 16);
			SetConsoleTextAttribute(renk, 224);
			cout << setw(21) << " ";
			cursor_move(24, 16);
			cin >> setw(21) >> ogr.adres;
			SetConsoleTextAttribute(renk, 96);
			cursor_move(24, 16);
			cout << left << setw(21) << ogr.adres;
			goto label;
		}
		if (pos == 6)
		{
			cursor_move(65, 16);
			SetConsoleTextAttribute(renk, 224);
			cout << setw(19) << " ";
			cursor_move(65, 16);
			cin >> setw(26) >> ogr.mesafe;
			SetConsoleTextAttribute(renk, 96);
			cursor_move(65, 16);
			cout << left << setw(19) << ogr.mesafe;
			goto label;
		}

		if (pos == 7)
		{
			menu_1();
		}
		if (pos == 8)
		{
			s.temp_ogrid++;
			file1.open("waiting_storage.bin", ios::app);
			file1 << left
				<< setw(5) << s.temp_ogrid << " "
				<< setw(20) << ogr.ad << " "
				<< setw(20) << ogr.soyad << " "
				<< setw(20) << ogr.adres << " "
				<< setw(10) << ogr.mesafe << " "
				<< setw(5) << ogr.sinif << " "
				<< setw(15) << ogr.tel << " " << endl;
		}
		file1.close();
		std_singup_guest();
	}
	else
	{
		system("MODE CON: COLS=90 LINES=20");

		SetConsoleTextAttribute(renk, 64);
		for (int i = 0; i < 90; i++)
		{
			cout << " ";
		}
		SetConsoleTextAttribute(renk, 192);
		for (int i = 0; i < 18; i++)
		{
			SetConsoleTextAttribute(renk, 64);
			cout << "  ";
			for (int j = 0; j < 86; j++)
			{
				SetConsoleTextAttribute(renk, 192);
				cout << " ";
			}
			SetConsoleTextAttribute(renk, 64);
			cout << "  " << endl;
		}
		SetConsoleTextAttribute(renk, 64);
		for (int i = 0; i < 90; i++)
		{
			cout << " ";
		}
		SetConsoleTextAttribute(renk, 207);
		cursor_move(25, 6);
		cout << "Kayýt bekleyen öðrenci limiti dolmuþtur.  ";
		cursor_move(38, 9);
		cout << " __________";
		cursor_move(38, 10);
		cout << "|          |";
		cursor_move(38, 11);
		cout << "|   GERÝ   |";
		cursor_move(38, 12);
		cout << "|__________|";

		pos = 1;
		while (true)
		{
			state = button();
			if (state == 7)
			{
				break;
			}
			if (pos == 1)
			{
				SetConsoleTextAttribute(renk, 207);
				cursor_move(38, 9);
				cout << " __________";
				SetConsoleTextAttribute(renk, 252);
				cursor_move(38, 10);
				cout << "|          |";
				cursor_move(38, 11);
				cout << "|   GERÝ   |";
				cursor_move(38, 12);
				cout << "|__________|";
				cursor_move(0, 0);
			}
			Sleep(200);
		}
		if (pos == 1)
		{
			menu_1();
		}
	}
}
void main_menu()
{
	system("cls");
	system("color 3f");
	system("MODE CON: COLS=85 LINES=30");

	for (int i = 0; i < 85; i++)
	{
		SetConsoleTextAttribute(renk, 31);
		cout << " ";
	}
	for (int i = 0; i < 28; i++)
	{
		SetConsoleTextAttribute(renk, 31);
		cout << "  ";
		for (int j = 0; j < 81; j++)
		{
			SetConsoleTextAttribute(renk, 63);
			cout << " ";
		}
		SetConsoleTextAttribute(renk, 31);
		cout << "  ";
		cout << endl;
	}
	for (int i = 0; i < 85; i++)
	{
		SetConsoleTextAttribute(renk, 31);
		cout << " ";
	}

	SetConsoleTextAttribute(renk, 63);
	cursor_move(55, 21);
	cout << "______________________";
	cursor_move(55, 22);
	cout << "|,----.,----.,----.,--.\\";
	cursor_move(55, 23);
	cout << "||    ||    ||    ||   \\\\";
	cursor_move(55, 24);
	cout << "|`----'`----'|----||----\`.";
	cursor_move(55, 25);
	cout << "[            |   -||- __|(|";
	cursor_move(55, 26);
	cout << "[  ,--.      |____||--.  ||";
	cursor_move(54, 27);
	cout << "|=-(( `))----------(( `))==|";
	cursor_move(55, 28);
	cout << "   `--'            `--'";

	cursor_move(30, 27);
	cout << "__(.)< __(.)> __(.)=";
	cursor_move(30, 28);
	cout << "\\___)  \\___)  \\___)";

	cursor_move(9, 8);
	SetConsoleTextAttribute(renk, 52);
	cout << "Yeni öðrenci kaydý";
	cursor_move(9, 10);
	SetConsoleTextAttribute(renk, 49);
	cout << "Onaylanacak öðrenciler";
	cursor_move(9, 12);
	SetConsoleTextAttribute(renk, 50);
	cout << "Kayýtlý öðrenci ara";

	cursor_move(9, 17);
	SetConsoleTextAttribute(renk, 53);
	cout << "Hesaptan çýk";
	cursor_move(9, 19);
	SetConsoleTextAttribute(renk, 60);
	cout << "Þifre deðiþtir";
	cursor_move(9, 21);
	SetConsoleTextAttribute(renk, 52);
	cout << "Çýkýþ yap";

	pos = 1;
	while (true)
	{
		state = button();
		if (state == 4)
		{
			pos++;
		}
		if (state == 3)
		{
			pos--;
		}
		if (state == 7)
		{
			break;
		}

		pos %= 6;
		if (pos == 0)
		{
			pos = 6;
		}

		if (pos == 1)
		{
			cursor_move(4, 8);
			SetConsoleTextAttribute(renk, 243);
			cout << "{*}>";
		}
		else
		{
			cursor_move(4, 8);
			SetConsoleTextAttribute(renk, 63);
			cout << "     ";
		}
		if (pos == 2)
		{
			cursor_move(4, 10);
			SetConsoleTextAttribute(renk, 243);
			cout << "{*}>";
		}
		else
		{
			cursor_move(4, 10);
			SetConsoleTextAttribute(renk, 63);
			cout << "     ";
		}
		if (pos == 3)
		{
			cursor_move(4, 12);
			SetConsoleTextAttribute(renk, 243);
			cout << "{*}>";
		}
		else
		{
			cursor_move(4, 12);
			SetConsoleTextAttribute(renk, 63);
			cout << "     ";
		}

		if (pos == 4)
		{
			cursor_move(4, 17);
			SetConsoleTextAttribute(renk, 243);
			cout << "{*}>";
		}
		else
		{
			cursor_move(4, 17);
			SetConsoleTextAttribute(renk, 63);
			cout << "     ";
		}
		if (pos == 5)
		{
			cursor_move(4, 19);
			SetConsoleTextAttribute(renk, 243);
			cout << "{*}>";
		}
		else
		{
			cursor_move(4, 19);
			SetConsoleTextAttribute(renk, 63);
			cout << "     ";
		}
		if (pos == 6)
		{
			cursor_move(4, 21);
			SetConsoleTextAttribute(renk, 243);
			cout << "{*}>";
		}
		else
		{
			cursor_move(4, 21);
			SetConsoleTextAttribute(renk, 63);
			cout << "     ";
		}
		cursor_move(0, 0);
		Sleep(250);
	}
	if (pos == 1)
	{
		std_singup_admin();
	}
	else if (pos == 2)
	{
		confirm_std();
	}
	else if (pos == 3)
	{
		std_info_change();
	}
	else if (pos == 4)
	{
		menu_1();
	}
	else if (pos == 5)
	{
		new_pas();
	}
	else if (pos == 6)
	{
		exit(0);
	}
}
void std_singup_admin()
{
	system("cls");
	system("color af");
	system("MODE CON: COLS=95 LINES=25");

	ogr.ad = "empty";
	ogr.soyad = "empty";
	ogr.adres = "empty";
	ogr.mesafe = 0;
	ogr.sinif = "empty";
	ogr.tel = "empty";


	for (int i = 0; i < 95; i++)
	{
		SetConsoleTextAttribute(renk, 34);
		cout << " ";
	}
	for (int i = 0; i < 23; i++)
	{
		SetConsoleTextAttribute(renk, 34);
		cout << "  ";
		for (int j = 0; j < 91; j++)
		{
			SetConsoleTextAttribute(renk, 170);
			cout << " ";
		}
		SetConsoleTextAttribute(renk, 34);
		cout << "  ";
		cout << endl;
	}
	for (int i = 0; i < 95; i++)
	{
		SetConsoleTextAttribute(renk, 34);
		cout << " ";
	}

	SetConsoleTextAttribute(renk, 96);
	int y = 7;
	for (int j = 0; j < 12; j++)
	{
		cursor_move(6, y);
		for (int i = 0; i < 83; i++)
		{
			cout << " ";
		}
		y++;
	}
	SetConsoleTextAttribute(renk, 175);
	cursor_move(6, 4);
	cout << "Kaydedilecek öðrencinin bilgilerini giriniz.";
	cursor_move(22, 19);
	cout << " __________";
	cursor_move(22, 20);
	cout << "|          |";
	cursor_move(22, 21);
	cout << "|   GERÝ   |";
	cursor_move(22, 22);
	cout << "|__________|";

	cursor_move(55, 19);
	cout << " ____________";
	cursor_move(55, 20);
	cout << "|            |";
	cursor_move(55, 21);
	cout << "|   Kaydet   |";
	cursor_move(55, 22);
	cout << "|____________|";

	SetConsoleTextAttribute(renk, 96);
	cursor_move(10, 8);
	cout << "Ýsim:";
	cursor_move(50, 8);
	cout << "Soyisim:";
	cursor_move(10, 12);
	cout << "Sýnýfý:";
	cursor_move(50, 12);
	cout << "Telefon Numarasý:";
	cursor_move(10, 16);
	cout << "Adresi(Semt):";
	cursor_move(50, 16);
	cout << "Mesafe(metre):";

	pos = 1;
	while (true)
	{
	label:


		state = button();
		if (state == 2 && pos < 8)
		{
			if (pos == 6)
				continue;
			pos++;
		}
		if (state == 1 && pos > 1)
		{
			if (pos == 7)
				continue;
			pos--;
		}
		if (state == 3 && pos < 9)
		{
			if (pos == 1 || pos == 2)
				continue;
			pos -= 2;
		}
		if (state == 4 && pos < 8)
		{
			if (pos == 7 || pos == 8)
				continue;
			pos += 2;
		}
		if (state == 7)
		{
			break;
		}

		if (pos == 1)
		{
			cursor_move(6, 8);
			SetConsoleTextAttribute(renk, 250);
			cout << "{*}>";
		}
		else
		{
			cursor_move(6, 8);
			SetConsoleTextAttribute(renk, 96);
			cout << "    ";
		}
		if (pos == 2)
		{
			cursor_move(46, 8);
			SetConsoleTextAttribute(renk, 250);
			cout << "{*}>";
		}
		else
		{
			cursor_move(46, 8);
			SetConsoleTextAttribute(renk, 96);
			cout << "    ";
		}
		if (pos == 3)
		{
			cursor_move(6, 12);
			SetConsoleTextAttribute(renk, 250);
			cout << "{*}>";
		}
		else
		{
			cursor_move(6, 12);
			SetConsoleTextAttribute(renk, 96);
			cout << "    ";
		}
		if (pos == 4)
		{
			cursor_move(46, 12);
			SetConsoleTextAttribute(renk, 250);
			cout << "{*}>";
		}
		else
		{
			cursor_move(46, 12);
			SetConsoleTextAttribute(renk, 96);
			cout << "    ";
		}
		if (pos == 5)
		{
			cursor_move(6, 16);
			SetConsoleTextAttribute(renk, 250);
			cout << "{*}>";
		}
		else
		{
			cursor_move(6, 16);
			SetConsoleTextAttribute(renk, 96);
			cout << "    ";
		}
		if (pos == 6)
		{
			cursor_move(46, 16);
			SetConsoleTextAttribute(renk, 250);
			cout << "{*}>";
		}
		else
		{
			cursor_move(46, 16);
			SetConsoleTextAttribute(renk, 96);
			cout << "    ";
		}
		if (pos == 7)
		{
			SetConsoleTextAttribute(renk, 250);
			cursor_move(22, 20);
			cout << "|          |";
			cursor_move(22, 21);
			cout << "|   GERÝ   |";
			cursor_move(22, 22);
			cout << "|__________|";
		}
		else
		{
			SetConsoleTextAttribute(renk, 175);
			cursor_move(22, 20);
			cout << "|          |";
			cursor_move(22, 21);
			cout << "|   GERÝ   |";
			cursor_move(22, 22);
			cout << "|__________|";
		}
		if (pos == 8)
		{
			SetConsoleTextAttribute(renk, 250);
			cursor_move(55, 20);
			cout << "|            |";
			cursor_move(55, 21);
			cout << "|   Kaydet   |";
			cursor_move(55, 22);
			cout << "|____________|";
		}
		else
		{
			SetConsoleTextAttribute(renk, 175);
			cursor_move(55, 20);
			cout << "|            |";
			cursor_move(55, 21);
			cout << "|   Kaydet   |";
			cursor_move(55, 22);
			cout << "|____________|";
		}
		Sleep(200);
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	if (pos == 1)
	{
		cursor_move(16, 8);
		SetConsoleTextAttribute(renk, 224);
		cout << setw(29) << " ";
		cursor_move(16, 8);
		cin >> setw(29) >> ogr.ad;
		SetConsoleTextAttribute(renk, 96);
		cursor_move(16, 8);
		cout << left << setw(29) << ogr.ad;
		goto label;
	}
	if (pos == 2)
	{
		cursor_move(59, 8);
		SetConsoleTextAttribute(renk, 224);
		cout << setw(25) << " ";
		cursor_move(59, 8);
		cin >> setw(25) >> ogr.soyad;
		SetConsoleTextAttribute(renk, 96);
		cursor_move(59, 8);
		cout << left << setw(25) << ogr.soyad;
		goto label;
	}
	if (pos == 3)
	{
		cursor_move(18, 12);
		SetConsoleTextAttribute(renk, 224);
		cout << setw(27) << " ";
		cursor_move(18, 12);
		cin >> setw(27) >> ogr.sinif;
		SetConsoleTextAttribute(renk, 96);
		cursor_move(18, 12);
		cout << left << setw(27) << ogr.sinif;
		goto label;
	}
	if (pos == 4)
	{
		cursor_move(68, 12);
		SetConsoleTextAttribute(renk, 224);
		cout << setw(16) << " ";
		cursor_move(68, 12);
		cin >> setw(16) >> ogr.tel;
		SetConsoleTextAttribute(renk, 96);
		cursor_move(68, 12);
		cout << left << setw(16) << ogr.tel;
		goto label;
	}
	if (pos == 5)
	{
		cursor_move(24, 16);
		SetConsoleTextAttribute(renk, 224);
		cout << setw(21) << " ";
		cursor_move(24, 16);
		cin >> setw(21) >> ogr.adres;
		SetConsoleTextAttribute(renk, 96);
		cursor_move(24, 16);
		cout << left << setw(21) << ogr.adres;
		goto label;
	}
	if (pos == 6)
	{
		cursor_move(65, 16);
		SetConsoleTextAttribute(renk, 224);
		cout << setw(19) << " ";
		cursor_move(65, 16);
		cin >> setw(26) >> ogr.mesafe;
		SetConsoleTextAttribute(renk, 96);
		cursor_move(65, 16);
		cout << left << setw(19) << ogr.mesafe;
		goto label;
	}

	if (pos == 7)
	{
		main_menu();
	}
	if (pos == 8)
	{
		s.ogrid++;
		file1.open("storage.bin", ios::app);
		file1 << left
			<< setw(5) << s.ogrid << " "
			<< setw(20) << ogr.ad << " "
			<< setw(20) << ogr.soyad << " "
			<< setw(20) << ogr.adres << " "
			<< setw(10) << ogr.mesafe << " "
			<< setw(5) << ogr.sinif << " "
			<< setw(15) << ogr.tel << " " << endl;
	}
	file1.close();
	main_menu();
}
void confirm_std()
{
	int y = 8, o = 1, _temp_ogrid = 10;;
	int s1 = 224, s2 = 224, s3 = 224, s4 = 224, s5 = 224;

	system("cls");
	if (s.temp_ogrid == 10)
	{
		system("MODE CON: COLS=90 LINES=20");

		SetConsoleTextAttribute(renk, 64);
		for (int i = 0; i < 90; i++)
		{
			cout << " ";
		}
		SetConsoleTextAttribute(renk, 192);
		for (int i = 0; i < 18; i++)
		{
			SetConsoleTextAttribute(renk, 64);
			cout << "  ";
			for (int j = 0; j < 86; j++)
			{
				SetConsoleTextAttribute(renk, 192);
				cout << " ";
			}
			SetConsoleTextAttribute(renk, 64);
			cout << "  " << endl;
		}
		SetConsoleTextAttribute(renk, 64);
		for (int i = 0; i < 90; i++)
		{
			cout << " ";
		}
		SetConsoleTextAttribute(renk, 207);
		cursor_move(25, 6);
		cout << "Kayýt bekleyen öðrenci bulunmamaktadýr.";
		cursor_move(38, 9);
		cout << " __________";
		cursor_move(38, 10);
		cout << "|          |";
		cursor_move(38, 11);
		cout << "|   GERÝ   |";
		cursor_move(38, 12);
		cout << "|__________|";

		pos = 1;
		while (true)
		{
			state = button();
			if (state == 7)
			{
				break;
			}
			if (pos == 1)
			{
				SetConsoleTextAttribute(renk, 207);
				cursor_move(38, 9);
				cout << " __________";
				SetConsoleTextAttribute(renk, 252);
				cursor_move(38, 10);
				cout << "|          |";
				cursor_move(38, 11);
				cout << "|   GERÝ   |";
				cursor_move(38, 12);
				cout << "|__________|";
				cursor_move(0, 0);
			}
			Sleep(200);
		}
		if (pos == 1)
		{
			main_menu();
		}
	}
	else
	{
		file1.open("waiting_storage.bin", ios::in);

		if (s.temp_ogrid == 11)
		{
			system("MODE CON: COLS=90 LINES=35");
			SetConsoleTextAttribute(renk, 32);
			for (int i = 0; i < 90; i++)
			{
				cout << " ";
			}
			SetConsoleTextAttribute(renk, 192);
			for (int i = 0; i < 33; i++)
			{
				SetConsoleTextAttribute(renk, 32);
				cout << "  ";
				for (int j = 0; j < 86; j++)
				{
					SetConsoleTextAttribute(renk, 160);
					cout << " ";
				}
				SetConsoleTextAttribute(renk, 32);
				cout << "  " << endl;
			}
			SetConsoleTextAttribute(renk, 32);
			for (int i = 0; i < 90; i++)
			{
				cout << " ";
			}

			cursor_move(7, 2);
			SetConsoleTextAttribute(renk, 175);
			cout << " __________";
			SetConsoleTextAttribute(renk, 175);
			cursor_move(7, 3);
			cout << "|          |";
			cursor_move(7, 4);
			cout << "|   GERÝ   |";
			cursor_move(7, 5);
			cout << "|__________|";



			SetConsoleTextAttribute(renk, 164);
			cursor_move(26, 4);
			cout << "Kayýt Edilmeyi Bekleyen Öðrenciler";
		label:
			while (!file1.eof())
			{
				file1 >> s.temp_ogrid >> ogr.ad >> ogr.soyad >> ogr.adres >> ogr.mesafe >> ogr.sinif >> ogr.tel;

				if (readed != s.temp_ogrid)
				{
					ogr1.ad = ogr.ad;
					ogr1.soyad = ogr.soyad;
					ogr1.adres = ogr.adres;
					ogr1.mesafe = ogr.mesafe;
					ogr1.sinif = ogr.sinif;
					ogr1.tel = ogr.tel;
				}
				readed = s.temp_ogrid;
			}


			SetConsoleTextAttribute(renk, 96);
			cursor_move(5, y - 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 2);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 3);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(6, y);
			cout << "Ýsim: " << ogr1.ad;
			cursor_move(6, y + 2);
			cout << "Soyisim: " << ogr1.soyad;
			cursor_move(26, y);
			cout << "Adres: " << ogr1.adres;
			cursor_move(26, y + 2);
			cout << "Mesafe: " << ogr1.mesafe;
			cursor_move(46, y);
			cout << "Sýnýfý: " << ogr1.sinif;
			cursor_move(46, y + 2);
			cout << "Telefon: " << ogr1.tel;
			cursor_move(63, y + 1);
			cout << "Ücret: " << ogr1.mesafe * 0.17 << "TL";
			SetConsoleTextAttribute(renk, 224);
			cursor_move(25, y + 4);
			cout << "Kabul Et";
			cursor_move(55, y + 4);
			cout << "Reddet";

			pos = 0;
			while (true)
			{
				state = button();
				cursor_move(32, 2);
				SetConsoleTextAttribute(renk, 175);
				cout << "1=";
				SetConsoleTextAttribute(renk, s1);
				cout << "  ";
				SetConsoleTextAttribute(renk, 175);


				if (state == 4 && pos < 1)
				{
					if (pos == 0)
					{
						pos = 1;
						continue;
					}
					pos += 2;
				}
				if (state == 1 && pos > 0)
				{
					if (pos = 1)
					{
						continue;
					}
					pos--;
				}
				if (state == 2 && pos < 2)
				{
					if (pos == 0)
					{
						continue;
					}
					pos++;
				}
				if (state == 3 && pos > 0)
				{
					if (pos == 1 || pos == 2)
					{
						pos = 0;
						continue;
					}
					pos -= 2;
				}
				if (state == 7)
				{
					break;
				}

				if (pos == 0)
				{
					SetConsoleTextAttribute(renk, 250);
					cursor_move(7, 3);
					cout << "|          |";
					cursor_move(7, 4);
					cout << "|   GERÝ   |";
					cursor_move(7, 5);
					cout << "|__________|";
				}
				else
				{
					cursor_move(7, 2);
					SetConsoleTextAttribute(renk, 175);
					cout << " __________";
					SetConsoleTextAttribute(renk, 175);
					cursor_move(7, 3);
					cout << "|          |";
					cursor_move(7, 4);
					cout << "|   GERÝ   |";
					cursor_move(7, 5);
					cout << "|__________|";

				}
				if (pos == 1)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(25, 12);
					cout << "Kabul Et";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(25, 12);
					cout << "Kabul Et";
				}
				if (pos == 2)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(55, 12);
					cout << "Reddet";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(55, 12);
					cout << "Reddet";
				}
				Sleep(300);
			}
			if (pos == 0)
			{
				goto check1;
			}
			if (pos == 1)
			{
				s1 = 16;
				goto label;
			}
			if (pos == 2)
			{
				s1 = 64;
				goto label;
			}
		}
		else if (s.temp_ogrid == 12)
		{
			system("MODE CON: COLS=90 LINES=35");
			SetConsoleTextAttribute(renk, 32);
			for (int i = 0; i < 90; i++)
			{
				cout << " ";
			}
			SetConsoleTextAttribute(renk, 192);
			for (int i = 0; i < 33; i++)
			{
				SetConsoleTextAttribute(renk, 32);
				cout << "  ";
				for (int j = 0; j < 86; j++)
				{
					SetConsoleTextAttribute(renk, 160);
					cout << " ";
				}
				SetConsoleTextAttribute(renk, 32);
				cout << "  " << endl;
			}
			SetConsoleTextAttribute(renk, 32);
			for (int i = 0; i < 90; i++)
			{
				cout << " ";
			}

			cursor_move(7, 2);
			SetConsoleTextAttribute(renk, 175);
			cout << " __________";
			SetConsoleTextAttribute(renk, 175);
			cursor_move(7, 3);
			cout << "|          |";
			cursor_move(7, 4);
			cout << "|   GERÝ   |";
			cursor_move(7, 5);
			cout << "|__________|";



			SetConsoleTextAttribute(renk, 164);
			cursor_move(26, 4);
			cout << "Kayýt Edilmeyi Bekleyen Öðrenciler";
			while (!file1.eof())
			{
				file1 >> s.temp_ogrid >> ogr.ad >> ogr.soyad >> ogr.adres >> ogr.mesafe >> ogr.sinif >> ogr.tel;

				if (readed != s.temp_ogrid)
				{
					if (o == 1)
					{
						ogr1.ad = ogr.ad;
						ogr1.soyad = ogr.soyad;
						ogr1.adres = ogr.adres;
						ogr1.mesafe = ogr.mesafe;
						ogr1.sinif = ogr.sinif;
						ogr1.tel = ogr.tel;
					}
					else if (o == 2)
					{
						ogr2.ad = ogr.ad;
						ogr2.soyad = ogr.soyad;
						ogr2.adres = ogr.adres;
						ogr2.mesafe = ogr.mesafe;
						ogr2.sinif = ogr.sinif;
						ogr2.tel = ogr.tel;
					}
					o++;
				}

				readed = s.temp_ogrid;
			}

			SetConsoleTextAttribute(renk, 96);
			cursor_move(5, y - 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 2);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 3);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}

			cursor_move(6, y);
			cout << "Ýsim: " << ogr1.ad;
			cursor_move(6, y + 2);
			cout << "Soyisim: " << ogr1.soyad;
			cursor_move(26, y);
			cout << "Adres: " << ogr1.adres;
			cursor_move(26, y + 2);
			cout << "Mesafe: " << ogr1.mesafe;
			cursor_move(46, y);
			cout << "Sýnýfý: " << ogr1.sinif;
			cursor_move(46, y + 2);
			cout << "Telefon: " << ogr1.tel;
			cursor_move(63, y + 1);
			cout << "Ücret: " << ogr1.mesafe * 0.17 << "TL";
			SetConsoleTextAttribute(renk, 224);
			cursor_move(25, y + 4);
			cout << "Kabul Et";
			cursor_move(55, y + 4);
			cout << "Reddet";

			y += 8;

			SetConsoleTextAttribute(renk, 96);
			cursor_move(5, y - 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 2);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 3);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(6, y);
			cout << "Ýsim: " << ogr2.ad;
			cursor_move(6, y + 2);
			cout << "Soyisim: " << ogr2.soyad;
			cursor_move(26, y);
			cout << "Adres: " << ogr2.adres;
			cursor_move(26, y + 2);
			cout << "Mesafe: " << ogr2.mesafe;
			cursor_move(46, y);
			cout << "Sýnýfý: " << ogr2.sinif;
			cursor_move(46, y + 2);
			cout << "Telefon: " << ogr2.tel;
			cursor_move(63, y + 1);
			cout << "Ücret: " << ogr2.mesafe * 0.17 << "TL";
			SetConsoleTextAttribute(renk, 224);
			cursor_move(25, y + 4);
			cout << "Kabul Et";
			cursor_move(55, y + 4);
			cout << "Reddet";
			pos = 0;
		label2:
			while (true)
			{
				state = button();
				cursor_move(32, 2);
				SetConsoleTextAttribute(renk, 175);
				cout << "1=";
				SetConsoleTextAttribute(renk, s1);
				cout << "  ";
				SetConsoleTextAttribute(renk, 175);
				cout << " 2=";
				SetConsoleTextAttribute(renk, s2);
				cout << "  ";
				SetConsoleTextAttribute(renk, 175);

				if (state == 4 && pos < 3)
				{
					if (pos == 0)
					{
						pos = 1;
						continue;
					}
					pos += 2;
				}
				if (state == 1 && pos > 0)
				{
					if (pos == 1)
					{
						continue;
					}
					pos--;
				}
				if (state == 2 && pos < 4)
				{
					if (pos == 0)
					{
						continue;
					}
					pos++;
				}
				if (state == 3 && pos > 0)
				{
					if (pos == 1 || pos == 2)
					{
						pos = 0;
						continue;
					}
					pos -= 2;
				}
				if (state == 7)
				{
					break;
				}

				if (pos == 0)
				{
					SetConsoleTextAttribute(renk, 250);
					cursor_move(7, 3);
					cout << "|          |";
					cursor_move(7, 4);
					cout << "|   GERÝ   |";
					cursor_move(7, 5);
					cout << "|__________|";
				}
				else
				{
					cursor_move(7, 2);
					SetConsoleTextAttribute(renk, 175);
					cout << " __________";
					SetConsoleTextAttribute(renk, 175);
					cursor_move(7, 3);
					cout << "|          |";
					cursor_move(7, 4);
					cout << "|   GERÝ   |";
					cursor_move(7, 5);
					cout << "|__________|";

				}
				if (pos == 1)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(25, 12);
					cout << "Kabul Et";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(25, 12);
					cout << "Kabul Et";
				}
				if (pos == 2)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(55, 12);
					cout << "Reddet";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(55, 12);
					cout << "Reddet";
				}
				//////////////////////////////////////
				if (pos == 3)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(25, 20);
					cout << "Kabul Et";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(25, 20);
					cout << "Kabul Et";
				}
				if (pos == 4)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(55, 20);
					cout << "Reddet";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(55, 20);
					cout << "Reddet";
				}

				Sleep(500);
			}
			if (pos == 0)
			{
				goto check2;
			}
			if (pos == 1)
			{
				s1 = 16;
				goto label2;
			}
			if (pos == 2)
			{
				s1 = 64;
				goto label2;
			}
			if (pos == 3)
			{
				s2 = 16;
				goto label2;
			}
			if (pos == 4)
			{
				s2 = 64;
				goto label2;
			}
		}
		else if (s.temp_ogrid == 13)
		{
			system("MODE CON: COLS=90 LINES=35");
			SetConsoleTextAttribute(renk, 32);
			for (int i = 0; i < 90; i++)
			{
				cout << " ";
			}
			SetConsoleTextAttribute(renk, 192);
			for (int i = 0; i < 33; i++)
			{
				SetConsoleTextAttribute(renk, 32);
				cout << "  ";
				for (int j = 0; j < 86; j++)
				{
					SetConsoleTextAttribute(renk, 160);
					cout << " ";
				}
				SetConsoleTextAttribute(renk, 32);
				cout << "  " << endl;
			}
			SetConsoleTextAttribute(renk, 32);
			for (int i = 0; i < 90; i++)
			{
				cout << " ";
			}

			cursor_move(7, 2);
			SetConsoleTextAttribute(renk, 175);
			cout << " __________";
			SetConsoleTextAttribute(renk, 175);
			cursor_move(7, 3);
			cout << "|          |";
			cursor_move(7, 4);
			cout << "|   GERÝ   |";
			cursor_move(7, 5);
			cout << "|__________|";



			SetConsoleTextAttribute(renk, 164);
			cursor_move(26, 4);
			cout << "Kayýt Edilmeyi Bekleyen Öðrenciler";
			while (!file1.eof())
			{
				file1 >> s.temp_ogrid >> ogr.ad >> ogr.soyad >> ogr.adres >> ogr.mesafe >> ogr.sinif >> ogr.tel;

				if (readed != s.temp_ogrid)
				{
					if (o == 1)
					{
						ogr1.ad = ogr.ad;
						ogr1.soyad = ogr.soyad;
						ogr1.adres = ogr.adres;
						ogr1.mesafe = ogr.mesafe;
						ogr1.sinif = ogr.sinif;
						ogr1.tel = ogr.tel;
					}
					else if (o == 2)
					{
						ogr2.ad = ogr.ad;
						ogr2.soyad = ogr.soyad;
						ogr2.adres = ogr.adres;
						ogr2.mesafe = ogr.mesafe;
						ogr2.sinif = ogr.sinif;
						ogr2.tel = ogr.tel;
					}
					else if (o == 3)
					{
						ogr3.ad = ogr.ad;
						ogr3.soyad = ogr.soyad;
						ogr3.adres = ogr.adres;
						ogr3.mesafe = ogr.mesafe;
						ogr3.sinif = ogr.sinif;
						ogr3.tel = ogr.tel;
					}
					o++;
				}

				readed = s.temp_ogrid;
			}

			SetConsoleTextAttribute(renk, 96);
			cursor_move(5, y - 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 2);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 3);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}

			cursor_move(6, y);
			cout << "Ýsim: " << ogr1.ad;
			cursor_move(6, y + 2);
			cout << "Soyisim: " << ogr1.soyad;
			cursor_move(26, y);
			cout << "Adres: " << ogr1.adres;
			cursor_move(26, y + 2);
			cout << "Mesafe: " << ogr1.mesafe;
			cursor_move(46, y);
			cout << "Sýnýfý: " << ogr1.sinif;
			cursor_move(46, y + 2);
			cout << "Telefon: " << ogr1.tel;
			cursor_move(63, y + 1);
			cout << "Ücret: " << ogr1.mesafe * 0.17 << "TL";
			SetConsoleTextAttribute(renk, 224);
			cursor_move(25, y + 4);
			cout << "Kabul Et";
			cursor_move(55, y + 4);
			cout << "Reddet";

			y += 8;

			SetConsoleTextAttribute(renk, 96);
			cursor_move(5, y - 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 2);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 3);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(6, y);
			cout << "Ýsim: " << ogr2.ad;
			cursor_move(6, y + 2);
			cout << "Soyisim: " << ogr2.soyad;
			cursor_move(26, y);
			cout << "Adres: " << ogr2.adres;
			cursor_move(26, y + 2);
			cout << "Mesafe: " << ogr2.mesafe;
			cursor_move(46, y);
			cout << "Sýnýfý: " << ogr2.sinif;
			cursor_move(46, y + 2);
			cout << "Telefon: " << ogr2.tel;
			cursor_move(63, y + 1);
			cout << "Ücret: " << ogr2.mesafe * 0.17 << "TL";
			SetConsoleTextAttribute(renk, 224);
			cursor_move(25, y + 4);
			cout << "Kabul Et";
			cursor_move(55, y + 4);
			cout << "Reddet";

			y += 8;

			SetConsoleTextAttribute(renk, 96);
			cursor_move(5, y - 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 2);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 3);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}

			cursor_move(6, y);
			cout << "Ýsim: " << ogr3.ad;
			cursor_move(6, y + 2);
			cout << "Soyisim: " << ogr3.soyad;
			cursor_move(26, y);
			cout << "Adres: " << ogr3.adres;
			cursor_move(26, y + 2);
			cout << "Mesafe: " << ogr3.mesafe;
			cursor_move(46, y);
			cout << "Sýnýfý: " << ogr3.sinif;
			cursor_move(46, y + 2);
			cout << "Telefon: " << ogr3.tel;
			cursor_move(63, y + 1);
			cout << "Ücret: " << ogr3.mesafe * 0.17 << "TL";
			SetConsoleTextAttribute(renk, 224);
			cursor_move(25, y + 4);
			cout << "Kabul Et";
			cursor_move(55, y + 4);
			cout << "Reddet";
			pos = 0;
		label3:
			while (true)
			{
				state = button();
				cursor_move(32, 2);
				SetConsoleTextAttribute(renk, 175);
				cout << "1=";
				SetConsoleTextAttribute(renk, s1);
				cout << "  ";
				SetConsoleTextAttribute(renk, 175);
				cout << " 2=";
				SetConsoleTextAttribute(renk, s2);
				cout << "  ";
				SetConsoleTextAttribute(renk, 175);
				cout << " 3=";
				SetConsoleTextAttribute(renk, s3);
				cout << "  ";
				SetConsoleTextAttribute(renk, 175);

				if (state == 4 && pos < 5)
				{
					if (pos == 0)
					{
						pos = 1;
						continue;
					}
					pos += 2;
				}
				if (state == 1 && pos > 0)
				{
					if (pos == 1)
					{
						continue;
					}
					pos--;
				}
				if (state == 2 && pos < 6)
				{
					if (pos == 0)
					{
						continue;
					}
					pos++;
				}
				if (state == 3 && pos > 0)
				{
					if (pos == 1 || pos == 2)
					{
						pos = 0;
						continue;
					}
					pos -= 2;
				}
				if (state == 7)
				{
					break;
				}

				if (pos == 0)
				{
					SetConsoleTextAttribute(renk, 250);
					cursor_move(7, 3);
					cout << "|          |";
					cursor_move(7, 4);
					cout << "|   GERÝ   |";
					cursor_move(7, 5);
					cout << "|__________|";
				}
				else
				{
					cursor_move(7, 2);
					SetConsoleTextAttribute(renk, 175);
					cout << " __________";
					SetConsoleTextAttribute(renk, 175);
					cursor_move(7, 3);
					cout << "|          |";
					cursor_move(7, 4);
					cout << "|   GERÝ   |";
					cursor_move(7, 5);
					cout << "|__________|";

				}
				if (pos == 1)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(25, 12);
					cout << "Kabul Et";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(25, 12);
					cout << "Kabul Et";
				}
				if (pos == 2)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(55, 12);
					cout << "Reddet";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(55, 12);
					cout << "Reddet";
				}
				//////////////////////////////////////
				if (pos == 3)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(25, 20);
					cout << "Kabul Et";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(25, 20);
					cout << "Kabul Et";
				}
				if (pos == 4)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(55, 20);
					cout << "Reddet";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(55, 20);
					cout << "Reddet";
				}
				//////////////////////////////////////
				if (pos == 5)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(25, 28);
					cout << "Kabul Et";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(25, 28);
					cout << "Kabul Et";
				}
				if (pos == 6)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(55, 28);
					cout << "Reddet";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(55, 28);
					cout << "Reddet";
				}

				Sleep(500);
			}
			if (pos == 0)
			{
				goto check3;
			}
			if (pos == 1)
			{
				s1 = 16;
				goto label3;
			}
			if (pos == 2)
			{
				s1 = 64;
				goto label3;
			}
			if (pos == 3)
			{
				s2 = 16;
				goto label3;
			}
			if (pos == 4)
			{
				s2 = 64;
				goto label3;
			}
			if (pos == 5)
			{
				s3 = 16;
				goto label3;
			}
			if (pos == 6)
			{
				s3 = 64;
				goto label3;
			}
		}
		else if (s.temp_ogrid == 14)
		{
			system("MODE CON: COLS=90 LINES=40");
			SetConsoleTextAttribute(renk, 32);
			for (int i = 0; i < 90; i++)
			{
				cout << " ";
			}
			SetConsoleTextAttribute(renk, 192);
			for (int i = 0; i < 38; i++)
			{
				SetConsoleTextAttribute(renk, 32);
				cout << "  ";
				for (int j = 0; j < 86; j++)
				{
					SetConsoleTextAttribute(renk, 160);
					cout << " ";
				}
				SetConsoleTextAttribute(renk, 32);
				cout << "  " << endl;
			}
			SetConsoleTextAttribute(renk, 32);
			for (int i = 0; i < 90; i++)
			{
				cout << " ";
			}

			cursor_move(7, 2);
			SetConsoleTextAttribute(renk, 175);
			cout << " __________";
			SetConsoleTextAttribute(renk, 175);
			cursor_move(7, 3);
			cout << "|          |";
			cursor_move(7, 4);
			cout << "|   GERÝ   |";
			cursor_move(7, 5);
			cout << "|__________|";

			cursor_move(26, 4);
			SetConsoleTextAttribute(renk, 164);
			cout << "Kayýt Edilmeyi Bekleyen Öðrenciler";


			while (!file1.eof())
			{
				file1 >> s.temp_ogrid >> ogr.ad >> ogr.soyad >> ogr.adres >> ogr.mesafe >> ogr.sinif >> ogr.tel;

				if (readed != s.temp_ogrid)
				{
					if (o == 1)
					{
						ogr1.ad = ogr.ad;
						ogr1.soyad = ogr.soyad;
						ogr1.adres = ogr.adres;
						ogr1.mesafe = ogr.mesafe;
						ogr1.sinif = ogr.sinif;
						ogr1.tel = ogr.tel;
					}
					else if (o == 2)
					{
						ogr2.ad = ogr.ad;
						ogr2.soyad = ogr.soyad;
						ogr2.adres = ogr.adres;
						ogr2.mesafe = ogr.mesafe;
						ogr2.sinif = ogr.sinif;
						ogr2.tel = ogr.tel;
					}
					else if (o == 3)
					{
						ogr3.ad = ogr.ad;
						ogr3.soyad = ogr.soyad;
						ogr3.adres = ogr.adres;
						ogr3.mesafe = ogr.mesafe;
						ogr3.sinif = ogr.sinif;
						ogr3.tel = ogr.tel;
					}
					else if (o == 4)
					{
						ogr4.ad = ogr.ad;
						ogr4.soyad = ogr.soyad;
						ogr4.adres = ogr.adres;
						ogr4.mesafe = ogr.mesafe;
						ogr4.sinif = ogr.sinif;
						ogr4.tel = ogr.tel;
					}
					o++;
				}

				readed = s.temp_ogrid;
			}

			//////////////////////////////////////////////////
			SetConsoleTextAttribute(renk, 96);
			cursor_move(5, y - 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 2);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 3);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}

			cursor_move(6, y);
			cout << "Ýsim: " << ogr1.ad;
			cursor_move(6, y + 2);
			cout << "Soyisim: " << ogr1.soyad;
			cursor_move(26, y);
			cout << "Adres: " << ogr1.adres;
			cursor_move(26, y + 2);
			cout << "Mesafe: " << ogr1.mesafe;
			cursor_move(46, y);
			cout << "Sýnýfý: " << ogr1.sinif;
			cursor_move(46, y + 2);
			cout << "Telefon: " << ogr1.tel;
			cursor_move(63, y + 1);
			cout << "Ücret: " << ogr1.mesafe * 0.17 << "TL";
			SetConsoleTextAttribute(renk, 224);
			cursor_move(25, y + 4);
			cout << "Kabul Et";
			cursor_move(55, y + 4);
			cout << "Reddet";
			//////////////////////////////////////////////////
			y += 8;
			//////////////////////////////////////////////////
			SetConsoleTextAttribute(renk, 96);
			cursor_move(5, y - 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 2);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 3);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(6, y);
			cout << "Ýsim: " << ogr2.ad;
			cursor_move(6, y + 2);
			cout << "Soyisim: " << ogr2.soyad;
			cursor_move(26, y);
			cout << "Adres: " << ogr2.adres;
			cursor_move(26, y + 2);
			cout << "Mesafe: " << ogr2.mesafe;
			cursor_move(46, y);
			cout << "Sýnýfý: " << ogr2.sinif;
			cursor_move(46, y + 2);
			cout << "Telefon: " << ogr2.tel;
			cursor_move(63, y + 1);
			cout << "Ücret: " << ogr2.mesafe * 0.17 << "TL";
			SetConsoleTextAttribute(renk, 224);
			cursor_move(25, y + 4);
			cout << "Kabul Et";
			cursor_move(55, y + 4);
			cout << "Reddet";
			//////////////////////////////////////////////////
			y += 8;
			//////////////////////////////////////////////////
			SetConsoleTextAttribute(renk, 96);
			cursor_move(5, y - 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 2);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 3);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}

			cursor_move(6, y);
			cout << "Ýsim: " << ogr3.ad;
			cursor_move(6, y + 2);
			cout << "Soyisim: " << ogr3.soyad;
			cursor_move(26, y);
			cout << "Adres: " << ogr3.adres;
			cursor_move(26, y + 2);
			cout << "Mesafe: " << ogr3.mesafe;
			cursor_move(46, y);
			cout << "Sýnýfý: " << ogr3.sinif;
			cursor_move(46, y + 2);
			cout << "Telefon: " << ogr3.tel;
			cursor_move(63, y + 1);
			cout << "Ücret: " << ogr3.mesafe * 0.17 << "TL";
			SetConsoleTextAttribute(renk, 224);
			cursor_move(25, y + 4);
			cout << "Kabul Et";
			cursor_move(55, y + 4);
			cout << "Reddet";
			//////////////////////////////////////////////////
			y += 8;
			//////////////////////////////////////////////////
			SetConsoleTextAttribute(renk, 96);
			cursor_move(5, y - 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 2);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 3);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(6, y);
			cout << "Ýsim: " << ogr4.ad;
			cursor_move(6, y + 2);
			cout << "Soyisim: " << ogr4.soyad;
			cursor_move(26, y);
			cout << "Adres: " << ogr4.adres;
			cursor_move(26, y + 2);
			cout << "Mesafe: " << ogr4.mesafe;
			cursor_move(46, y);
			cout << "Sýnýfý: " << ogr4.sinif;
			cursor_move(46, y + 2);
			cout << "Telefon: " << ogr4.tel;
			cursor_move(63, y + 1);
			cout << "Ücret: " << ogr4.mesafe * 0.17 << "TL";
			SetConsoleTextAttribute(renk, 224);
			cursor_move(25, y + 4);
			cout << "Kabul Et";
			cursor_move(55, y + 4);
			cout << "Reddet";
			pos = 0;
		label4:
			while (true)
			{
				state = button();
				cursor_move(32, 2);
				SetConsoleTextAttribute(renk, 175);
				cout << "1=";
				SetConsoleTextAttribute(renk, s1);
				cout << "  ";
				SetConsoleTextAttribute(renk, 175);
				cout << " 2=";
				SetConsoleTextAttribute(renk, s2);
				cout << "  ";
				SetConsoleTextAttribute(renk, 175);
				cout << " 3=";
				SetConsoleTextAttribute(renk, s3);
				cout << "  ";
				SetConsoleTextAttribute(renk, 175);
				cout << " 4=";
				SetConsoleTextAttribute(renk, s4);
				cout << "  ";
				SetConsoleTextAttribute(renk, 175);

				if (state == 4 && pos < 7)
				{
					if (pos == 0)
					{
						pos = 1;
						continue;
					}
					pos += 2;
				}
				if (state == 1 && pos > 0)
				{
					if (pos == 1)
					{
						continue;
					}
					pos--;
				}
				if (state == 2 && pos < 8)
				{
					if (pos == 0)
					{
						continue;
					}
					pos++;
				}
				if (state == 3 && pos > 0)
				{
					if (pos == 1 || pos == 2)
					{
						pos = 0;
						continue;
					}
					pos -= 2;
				}
				if (state == 7)
				{
					break;
				}

				if (pos == 0)
				{
					SetConsoleTextAttribute(renk, 250);
					cursor_move(7, 3);
					cout << "|          |";
					cursor_move(7, 4);
					cout << "|   GERÝ   |";
					cursor_move(7, 5);
					cout << "|__________|";
				}
				else
				{
					cursor_move(7, 2);
					SetConsoleTextAttribute(renk, 175);
					cout << " __________";
					SetConsoleTextAttribute(renk, 175);
					cursor_move(7, 3);
					cout << "|          |";
					cursor_move(7, 4);
					cout << "|   GERÝ   |";
					cursor_move(7, 5);
					cout << "|__________|";

				}
				if (pos == 1)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(25, 12);
					cout << "Kabul Et";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(25, 12);
					cout << "Kabul Et";
				}
				if (pos == 2)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(55, 12);
					cout << "Reddet";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(55, 12);
					cout << "Reddet";
				}
				//////////////////////////////////////
				if (pos == 3)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(25, 20);
					cout << "Kabul Et";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(25, 20);
					cout << "Kabul Et";
				}
				if (pos == 4)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(55, 20);
					cout << "Reddet";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(55, 20);
					cout << "Reddet";
				}
				//////////////////////////////////////
				if (pos == 5)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(25, 28);
					cout << "Kabul Et";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(25, 28);
					cout << "Kabul Et";
				}
				if (pos == 6)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(55, 28);
					cout << "Reddet";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(55, 28);
					cout << "Reddet";
				}
				//////////////////////////////////////
				if (pos == 7)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(25, 36);
					cout << "Kabul Et";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(25, 36);
					cout << "Kabul Et";
				}
				if (pos == 8)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(55, 36);
					cout << "Reddet";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(55, 36);
					cout << "Reddet";
				}
				Sleep(500);
			}
			if (pos == 0)
			{
				goto check4;
			}
			if (pos == 1)
			{
				s1 = 16;
				goto label4;
			}
			if (pos == 2)
			{
				s1 = 64;
				goto label4;
			}
			if (pos == 3)
			{
				s2 = 16;
				goto label4;
			}
			if (pos == 4)
			{
				s2 = 64;
				goto label4;
			}
			if (pos == 5)
			{
				s3 = 16;
				goto label4;
			}
			if (pos == 6)
			{
				s3 = 64;
				goto label4;
			}
			if (pos == 7)
			{
				s4 = 16;
				goto label4;
			}
			if (pos == 8)
			{
				s4 = 64;
				goto label4;
			}
		}
		else if (s.temp_ogrid == 15)
		{
			system("MODE CON: COLS=90 LINES=47");
			SetConsoleTextAttribute(renk, 32);
			for (int i = 0; i < 90; i++)
			{
				cout << " ";
			}
			SetConsoleTextAttribute(renk, 192);
			for (int i = 0; i < 45; i++)
			{
				SetConsoleTextAttribute(renk, 32);
				cout << "  ";
				for (int j = 0; j < 86; j++)
				{
					SetConsoleTextAttribute(renk, 160);
					cout << " ";
				}
				SetConsoleTextAttribute(renk, 32);
				cout << "  " << endl;
			}
			SetConsoleTextAttribute(renk, 32);
			for (int i = 0; i < 90; i++)
			{
				cout << " ";
			}

			cursor_move(7, 2);
			SetConsoleTextAttribute(renk, 175);
			cout << " __________";
			SetConsoleTextAttribute(renk, 175);
			cursor_move(7, 3);
			cout << "|          |";
			cursor_move(7, 4);
			cout << "|   GERÝ   |";
			cursor_move(7, 5);
			cout << "|__________|";

			cursor_move(26, 4);
			SetConsoleTextAttribute(renk, 164);
			cout << "Kayýt Edilmeyi Bekleyen Öðrenciler";


			while (!file1.eof())
			{
				file1 >> s.temp_ogrid >> ogr.ad >> ogr.soyad >> ogr.adres >> ogr.mesafe >> ogr.sinif >> ogr.tel;

				if (readed != s.temp_ogrid)
				{
					if (o == 1)
					{
						ogr1.ad = ogr.ad;
						ogr1.soyad = ogr.soyad;
						ogr1.adres = ogr.adres;
						ogr1.mesafe = ogr.mesafe;
						ogr1.sinif = ogr.sinif;
						ogr1.tel = ogr.tel;
					}
					else if (o == 2)
					{
						ogr2.ad = ogr.ad;
						ogr2.soyad = ogr.soyad;
						ogr2.adres = ogr.adres;
						ogr2.mesafe = ogr.mesafe;
						ogr2.sinif = ogr.sinif;
						ogr2.tel = ogr.tel;
					}
					else if (o == 3)
					{
						ogr3.ad = ogr.ad;
						ogr3.soyad = ogr.soyad;
						ogr3.adres = ogr.adres;
						ogr3.mesafe = ogr.mesafe;
						ogr3.sinif = ogr.sinif;
						ogr3.tel = ogr.tel;
					}
					else if (o == 4)
					{
						ogr4.ad = ogr.ad;
						ogr4.soyad = ogr.soyad;
						ogr4.adres = ogr.adres;
						ogr4.mesafe = ogr.mesafe;
						ogr4.sinif = ogr.sinif;
						ogr4.tel = ogr.tel;
					}
					else if (o == 5)
					{
						ogr5.ad = ogr.ad;
						ogr5.soyad = ogr.soyad;
						ogr5.adres = ogr.adres;
						ogr5.mesafe = ogr.mesafe;
						ogr5.sinif = ogr.sinif;
						ogr5.tel = ogr.tel;
					}
					o++;
				}

				readed = s.temp_ogrid;
			}

			//////////////////////////////////////////////////
			SetConsoleTextAttribute(renk, 96);
			cursor_move(5, y - 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 2);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 3);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}

			cursor_move(6, y);
			cout << "Ýsim: " << ogr1.ad;
			cursor_move(6, y + 2);
			cout << "Soyisim: " << ogr1.soyad;
			cursor_move(26, y);
			cout << "Adres: " << ogr1.adres;
			cursor_move(26, y + 2);
			cout << "Mesafe: " << ogr1.mesafe;
			cursor_move(46, y);
			cout << "Sýnýfý: " << ogr1.sinif;
			cursor_move(46, y + 2);
			cout << "Telefon: " << ogr1.tel;
			cursor_move(63, y + 1);
			cout << "Ücret: " << ogr1.mesafe * 0.17 << "TL";
			SetConsoleTextAttribute(renk, 224);
			cursor_move(25, y + 4);
			cout << "Kabul Et";
			cursor_move(55, y + 4);
			cout << "Reddet";
			//////////////////////////////////////////////////
			y += 8;
			//////////////////////////////////////////////////
			SetConsoleTextAttribute(renk, 96);
			cursor_move(5, y - 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 2);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 3);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(6, y);
			cout << "Ýsim: " << ogr2.ad;
			cursor_move(6, y + 2);
			cout << "Soyisim: " << ogr2.soyad;
			cursor_move(26, y);
			cout << "Adres: " << ogr2.adres;
			cursor_move(26, y + 2);
			cout << "Mesafe: " << ogr2.mesafe;
			cursor_move(46, y);
			cout << "Sýnýfý: " << ogr2.sinif;
			cursor_move(46, y + 2);
			cout << "Telefon: " << ogr2.tel;
			cursor_move(63, y + 1);
			cout << "Ücret: " << ogr2.mesafe * 0.17 << "TL";
			SetConsoleTextAttribute(renk, 224);
			cursor_move(25, y + 4);
			cout << "Kabul Et";
			cursor_move(55, y + 4);
			cout << "Reddet";
			//////////////////////////////////////////////////
			y += 8;
			//////////////////////////////////////////////////
			SetConsoleTextAttribute(renk, 96);
			cursor_move(5, y - 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 2);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 3);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}

			cursor_move(6, y);
			cout << "Ýsim: " << ogr3.ad;
			cursor_move(6, y + 2);
			cout << "Soyisim: " << ogr3.soyad;
			cursor_move(26, y);
			cout << "Adres: " << ogr3.adres;
			cursor_move(26, y + 2);
			cout << "Mesafe: " << ogr3.mesafe;
			cursor_move(46, y);
			cout << "Sýnýfý: " << ogr3.sinif;
			cursor_move(46, y + 2);
			cout << "Telefon: " << ogr3.tel;
			cursor_move(63, y + 1);
			cout << "Ücret: " << ogr3.mesafe * 0.17 << "TL";
			SetConsoleTextAttribute(renk, 224);
			cursor_move(25, y + 4);
			cout << "Kabul Et";
			cursor_move(55, y + 4);
			cout << "Reddet";
			//////////////////////////////////////////////////
			y += 8;
			//////////////////////////////////////////////////
			SetConsoleTextAttribute(renk, 96);
			cursor_move(5, y - 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 2);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 3);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(6, y);
			cout << "Ýsim: " << ogr4.ad;
			cursor_move(6, y + 2);
			cout << "Soyisim: " << ogr4.soyad;
			cursor_move(26, y);
			cout << "Adres: " << ogr4.adres;
			cursor_move(26, y + 2);
			cout << "Mesafe: " << ogr4.mesafe;
			cursor_move(46, y);
			cout << "Sýnýfý: " << ogr4.sinif;
			cursor_move(46, y + 2);
			cout << "Telefon: " << ogr4.tel;
			cursor_move(63, y + 1);
			cout << "Ücret: " << ogr4.mesafe * 0.17 << "TL";
			SetConsoleTextAttribute(renk, 224);
			cursor_move(25, y + 4);
			cout << "Kabul Et";
			cursor_move(55, y + 4);
			cout << "Reddet";
			//////////////////////////////////////////////////
			y += 8;
			//////////////////////////////////////////////////
			SetConsoleTextAttribute(renk, 96);
			cursor_move(5, y - 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 1);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 2);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(5, y + 3);
			for (int i = 0; i < 80; i++)
			{
				cout << " ";
			}
			cursor_move(6, y);
			cout << "Ýsim: " << ogr5.ad;
			cursor_move(6, y + 2);
			cout << "Soyisim: " << ogr5.soyad;
			cursor_move(26, y);
			cout << "Adres: " << ogr5.adres;
			cursor_move(26, y + 2);
			cout << "Mesafe: " << ogr5.mesafe;
			cursor_move(46, y);
			cout << "Sýnýfý: " << ogr5.sinif;
			cursor_move(46, y + 2);
			cout << "Telefon: " << ogr5.tel;
			cursor_move(63, y + 1);
			cout << "Ücret: " << ogr5.mesafe * 0.17 << "TL";
			SetConsoleTextAttribute(renk, 224);
			cursor_move(25, y + 4);
			cout << "Kabul Et";
			cursor_move(55, y + 4);
			cout << "Reddet";


			pos = 0;
		label5:
			while (true)
			{
				state = button();
				cursor_move(32, 2);
				SetConsoleTextAttribute(renk, 175);
				cout << "1=";
				SetConsoleTextAttribute(renk, s1);
				cout << "  ";
				SetConsoleTextAttribute(renk, 175);
				cout << " 2=";
				SetConsoleTextAttribute(renk, s2);
				cout << "  ";
				SetConsoleTextAttribute(renk, 175);
				cout << " 3=";
				SetConsoleTextAttribute(renk, s3);
				cout << "  ";
				SetConsoleTextAttribute(renk, 175);
				cout << " 4=";
				SetConsoleTextAttribute(renk, s4);
				cout << "  ";
				SetConsoleTextAttribute(renk, 175);
				cout << " 5=";
				SetConsoleTextAttribute(renk, s5);
				cout << "  ";
				SetConsoleTextAttribute(renk, 175);

				if (state == 4 && pos < 9)
				{
					if (pos == 0)
					{
						pos = 1;
						continue;
					}
					pos += 2;
				}
				if (state == 1 && pos > 0)
				{
					if (pos == 1)
					{
						continue;
					}
					pos--;
				}
				if (state == 2 && pos < 10)
				{
					if (pos == 0)
					{
						continue;
					}
					pos++;
				}
				if (state == 3 && pos > 0)
				{
					if (pos == 1 || pos == 2)
					{
						pos = 0;
						continue;
					}
					pos -= 2;
				}
				if (state == 7)
				{
					break;
				}

				if (pos == 0)
				{
					SetConsoleTextAttribute(renk, 250);
					cursor_move(7, 3);
					cout << "|          |";
					cursor_move(7, 4);
					cout << "|   GERÝ   |";
					cursor_move(7, 5);
					cout << "|__________|";
				}
				else
				{
					cursor_move(7, 2);
					SetConsoleTextAttribute(renk, 175);
					cout << " __________";
					SetConsoleTextAttribute(renk, 175);
					cursor_move(7, 3);
					cout << "|          |";
					cursor_move(7, 4);
					cout << "|   GERÝ   |";
					cursor_move(7, 5);
					cout << "|__________|";

				}
				if (pos == 1)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(25, 12);
					cout << "Kabul Et";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(25, 12);
					cout << "Kabul Et";
				}
				if (pos == 2)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(55, 12);
					cout << "Reddet";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(55, 12);
					cout << "Reddet";
				}
				//////////////////////////////////////
				if (pos == 3)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(25, 20);
					cout << "Kabul Et";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(25, 20);
					cout << "Kabul Et";
				}
				if (pos == 4)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(55, 20);
					cout << "Reddet";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(55, 20);
					cout << "Reddet";
				}
				//////////////////////////////////////
				if (pos == 5)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(25, 28);
					cout << "Kabul Et";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(25, 28);
					cout << "Kabul Et";
				}
				if (pos == 6)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(55, 28);
					cout << "Reddet";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(55, 28);
					cout << "Reddet";
				}
				//////////////////////////////////////
				if (pos == 7)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(25, 36);
					cout << "Kabul Et";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(25, 36);
					cout << "Kabul Et";
				}
				if (pos == 8)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(55, 36);
					cout << "Reddet";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(55, 36);
					cout << "Reddet";
				}
				//////////////////////////////////////
				if (pos == 9)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(25, 44);
					cout << "Kabul Et";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(25, 44);
					cout << "Kabul Et";
				}
				if (pos == 10)
				{
					SetConsoleTextAttribute(renk, 31);
					cursor_move(55, 44);
					cout << "Reddet";
				}
				else
				{
					SetConsoleTextAttribute(renk, 224);
					cursor_move(55, 44);
					cout << "Reddet";
				}
				Sleep(500);
			}
			if (pos == 0)
			{
				goto check5;
			}
			if (pos == 1)
			{
				s1 = 16;
				goto label5;
			}
			if (pos == 2)
			{
				s1 = 64;
				goto label5;
			}
			if (pos == 3)
			{
				s2 = 16;
				goto label5;
			}
			if (pos == 4)
			{
				s2 = 64;
				goto label5;
			}
			if (pos == 5)
			{
				s3 = 16;
				goto label5;
			}
			if (pos == 6)
			{
				s3 = 64;
				goto label5;
			}
			if (pos == 7)
			{
				s4 = 16;
				goto label5;
			}
			if (pos == 8)
			{
				s4 = 64;
				goto label5;
			}
			if (pos == 9)
			{
				s5 = 16;
				goto label5;
			}
			if (pos == 10)
			{
				s5 = 64;
				goto label5;
			}
		}

		file1.close();



	check1:
		{
			file2.open("temp.bin", ios::out | ios::app);
			ofstream file3("storage.bin", ios::out | ios::app);


			if (s1 == 224)
			{


				_temp_ogrid++;
				file2 << left
					<< setw(5) << _temp_ogrid << " "
					<< setw(20) << ogr1.ad << " "
					<< setw(20) << ogr1.soyad << " "
					<< setw(20) << ogr1.adres << " "
					<< setw(10) << ogr1.mesafe << " "
					<< setw(5) << ogr1.sinif << " "
					<< setw(15) << ogr1.tel << " " << endl;
			}
			else if (s1 == 16)
			{
				s.ogrid++;
				file3 << left
					<< setw(5) << s.ogrid << " "
					<< setw(20) << ogr1.ad << " "
					<< setw(20) << ogr1.soyad << " "
					<< setw(20) << ogr1.adres << " "
					<< setw(10) << ogr1.mesafe << " "
					<< setw(5) << ogr1.sinif << " "
					<< setw(15) << ogr1.tel << " " << endl;
			}
			else if (s1 == 64)
			{

			}

			file1.close();
			file2.close();
			file3.close();

			remove("waiting_storage.bin");
			rename("temp.bin", "waiting_storage.bin");

			main_menu();
		}
	check2:
		{
			file2.open("temp.bin", ios::out | ios::app);
			ofstream file3("storage.bin", ios::out | ios::app);

			if (s1 == 224)
			{
				_temp_ogrid++;
				file2 << left
					<< setw(5) << _temp_ogrid << " "
					<< setw(20) << ogr1.ad << " "
					<< setw(20) << ogr1.soyad << " "
					<< setw(20) << ogr1.adres << " "
					<< setw(10) << ogr1.mesafe << " "
					<< setw(5) << ogr1.sinif << " "
					<< setw(15) << ogr1.tel << " " << endl;
			}
			else if (s1 == 16)
			{
				s.ogrid++;
				file3 << left
					<< setw(5) << s.ogrid << " "
					<< setw(20) << ogr1.ad << " "
					<< setw(20) << ogr1.soyad << " "
					<< setw(20) << ogr1.adres << " "
					<< setw(10) << ogr1.mesafe << " "
					<< setw(5) << ogr1.sinif << " "
					<< setw(15) << ogr1.tel << " " << endl;
			}
			else if (s1 == 64)
			{

			}

			if (s2 == 224)
			{
				_temp_ogrid++;
				file2 << left
					<< setw(5) << _temp_ogrid << " "
					<< setw(20) << ogr2.ad << " "
					<< setw(20) << ogr2.soyad << " "
					<< setw(20) << ogr2.adres << " "
					<< setw(10) << ogr2.mesafe << " "
					<< setw(5) << ogr2.sinif << " "
					<< setw(15) << ogr2.tel << " " << endl;
			}
			else if (s2 == 16)
			{
				s.ogrid++;
				file2 << left
					<< setw(5) << s.ogrid << " "
					<< setw(20) << ogr2.ad << " "
					<< setw(20) << ogr2.soyad << " "
					<< setw(20) << ogr2.adres << " "
					<< setw(10) << ogr2.mesafe << " "
					<< setw(5) << ogr2.sinif << " "
					<< setw(15) << ogr2.tel << " " << endl;
			}
			else if (s2 == 64)
			{

			}

			file1.close();
			file2.close();
			file3.close();

			remove("waiting_storage.bin");
			rename("temp.bin", "waiting_storage.bin");

			main_menu();
		}
	check3:
		{
			file2.open("temp.bin", ios::out | ios::app);
			ofstream file3("storage.bin", ios::out | ios::app);

			if (s1 == 224)
			{
				_temp_ogrid++;
				file2 << left
					<< setw(5) << _temp_ogrid << " "
					<< setw(20) << ogr1.ad << " "
					<< setw(20) << ogr1.soyad << " "
					<< setw(20) << ogr1.adres << " "
					<< setw(10) << ogr1.mesafe << " "
					<< setw(5) << ogr1.sinif << " "
					<< setw(15) << ogr1.tel << " " << endl;
			}
			else if (s1 == 16)
			{
				s.ogrid++;
				file3 << left
					<< setw(5) << s.ogrid << " "
					<< setw(20) << ogr1.ad << " "
					<< setw(20) << ogr1.soyad << " "
					<< setw(20) << ogr1.adres << " "
					<< setw(10) << ogr1.mesafe << " "
					<< setw(5) << ogr1.sinif << " "
					<< setw(15) << ogr1.tel << " " << endl;
			}
			else if (s1 == 64)
			{

			}

			if (s2 == 224)
			{
				_temp_ogrid++;
				file2 << left
					<< setw(5) << _temp_ogrid << " "
					<< setw(20) << ogr2.ad << " "
					<< setw(20) << ogr2.soyad << " "
					<< setw(20) << ogr2.adres << " "
					<< setw(10) << ogr2.mesafe << " "
					<< setw(5) << ogr2.sinif << " "
					<< setw(15) << ogr2.tel << " " << endl;
			}
			else if (s2 == 16)
			{
				s.ogrid++;
				file3 << left
					<< setw(5) << s.ogrid << " "
					<< setw(20) << ogr2.ad << " "
					<< setw(20) << ogr2.soyad << " "
					<< setw(20) << ogr2.adres << " "
					<< setw(10) << ogr2.mesafe << " "
					<< setw(5) << ogr2.sinif << " "
					<< setw(15) << ogr2.tel << " " << endl;
			}
			else if (s2 == 64)
			{

			}

			if (s3 == 224)
			{
				_temp_ogrid++;
				file2 << left
					<< setw(5) << _temp_ogrid << " "
					<< setw(20) << ogr3.ad << " "
					<< setw(20) << ogr3.soyad << " "
					<< setw(20) << ogr3.adres << " "
					<< setw(10) << ogr3.mesafe << " "
					<< setw(5) << ogr3.sinif << " "
					<< setw(15) << ogr3.tel << " " << endl;
			}
			else if (s3 == 16)
			{
				s.ogrid++;
				file3 << left
					<< setw(5) << s.ogrid << " "
					<< setw(20) << ogr3.ad << " "
					<< setw(20) << ogr3.soyad << " "
					<< setw(20) << ogr3.adres << " "
					<< setw(10) << ogr3.mesafe << " "
					<< setw(5) << ogr3.sinif << " "
					<< setw(15) << ogr3.tel << " " << endl;
			}
			else if (s3 == 64)
			{

			}

			file1.close();
			file2.close();
			file3.close();

			remove("waiting_storage.bin");
			rename("temp.bin", "waiting_storage.bin");

			main_menu();
		}
	check4:
		{
			file2.open("temp.bin", ios::out | ios::app);
			ofstream file3("storage.bin", ios::out | ios::app);

			if (s1 == 224)
			{
				_temp_ogrid++;
				file2 << left
					<< setw(5) << _temp_ogrid << " "
					<< setw(20) << ogr1.ad << " "
					<< setw(20) << ogr1.soyad << " "
					<< setw(20) << ogr1.adres << " "
					<< setw(10) << ogr1.mesafe << " "
					<< setw(5) << ogr1.sinif << " "
					<< setw(15) << ogr1.tel << " " << endl;
			}
			else if (s1 == 16)
			{
				s.ogrid++;
				file3 << left
					<< setw(5) << s.ogrid << " "
					<< setw(20) << ogr1.ad << " "
					<< setw(20) << ogr1.soyad << " "
					<< setw(20) << ogr1.adres << " "
					<< setw(10) << ogr1.mesafe << " "
					<< setw(5) << ogr1.sinif << " "
					<< setw(15) << ogr1.tel << " " << endl;
			}
			else if (s1 == 64)
			{

			}

			if (s2 == 224)
			{
				_temp_ogrid++;
				file2 << left
					<< setw(5) << _temp_ogrid << " "
					<< setw(20) << ogr2.ad << " "
					<< setw(20) << ogr2.soyad << " "
					<< setw(20) << ogr2.adres << " "
					<< setw(10) << ogr2.mesafe << " "
					<< setw(5) << ogr2.sinif << " "
					<< setw(15) << ogr.tel << " " << endl;
			}
			else if (s2 == 16)
			{
				s.ogrid++;
				file3 << left
					<< setw(5) << s.ogrid << " "
					<< setw(20) << ogr2.ad << " "
					<< setw(20) << ogr2.soyad << " "
					<< setw(20) << ogr2.adres << " "
					<< setw(10) << ogr2.mesafe << " "
					<< setw(5) << ogr2.sinif << " "
					<< setw(15) << ogr2.tel << " " << endl;
			}
			else if (s2 == 64)
			{

			}

			if (s3 == 224)
			{
				_temp_ogrid++;
				file2 << left
					<< setw(5) << _temp_ogrid << " "
					<< setw(20) << ogr3.ad << " "
					<< setw(20) << ogr3.soyad << " "
					<< setw(20) << ogr3.adres << " "
					<< setw(10) << ogr3.mesafe << " "
					<< setw(5) << ogr3.sinif << " "
					<< setw(15) << ogr3.tel << " " << endl;
			}
			else if (s3 == 16)
			{
				s.ogrid++;
				file3 << left
					<< setw(5) << s.ogrid << " "
					<< setw(20) << ogr3.ad << " "
					<< setw(20) << ogr3.soyad << " "
					<< setw(20) << ogr3.adres << " "
					<< setw(10) << ogr3.mesafe << " "
					<< setw(5) << ogr3.sinif << " "
					<< setw(15) << ogr3.tel << " " << endl;
			}
			else if (s3 == 64)
			{

			}


			if (s4 == 224)
			{
				_temp_ogrid++;
				file2 << left
					<< setw(5) << _temp_ogrid << " "
					<< setw(20) << ogr4.ad << " "
					<< setw(20) << ogr4.soyad << " "
					<< setw(20) << ogr4.adres << " "
					<< setw(10) << ogr4.mesafe << " "
					<< setw(5) << ogr4.sinif << " "
					<< setw(15) << ogr4.tel << " " << endl;
			}
			else if (s4 == 16)
			{
				s.ogrid++;
				file3 << left
					<< setw(5) << s.ogrid << " "
					<< setw(20) << ogr4.ad << " "
					<< setw(20) << ogr4.soyad << " "
					<< setw(20) << ogr4.adres << " "
					<< setw(10) << ogr4.mesafe << " "
					<< setw(5) << ogr4.sinif << " "
					<< setw(15) << ogr4.tel << " " << endl;
			}
			else if (s4 == 64)
			{

			}

			file1.close();
			file2.close();
			file3.close();

			remove("waiting_storage.bin");
			rename("temp.bin", "waiting_storage.bin");

			main_menu();
		}
	check5:
		{
			file2.open("temp.bin", ios::out | ios::app);
			ofstream file3("storage.bin", ios::out | ios::app);


			if (s1 == 224)
			{
				_temp_ogrid++;
				file2 << left
					<< setw(5) << _temp_ogrid << " "
					<< setw(20) << ogr1.ad << " "
					<< setw(20) << ogr1.soyad << " "
					<< setw(20) << ogr1.adres << " "
					<< setw(10) << ogr1.mesafe << " "
					<< setw(5) << ogr1.sinif << " "
					<< setw(15) << ogr1.tel << " " << endl;
			}
			else if (s1 == 16)
			{
				s.ogrid++;
				file3 << left
					<< setw(5) << s.ogrid << " "
					<< setw(20) << ogr1.ad << " "
					<< setw(20) << ogr1.soyad << " "
					<< setw(20) << ogr1.adres << " "
					<< setw(10) << ogr1.mesafe << " "
					<< setw(5) << ogr1.sinif << " "
					<< setw(15) << ogr1.tel << " " << endl;
			}
			else if (s1 == 64)
			{

			}


			if (s2 == 224)
			{
				_temp_ogrid++;
				file2 << left
					<< setw(5) << _temp_ogrid << " "
					<< setw(20) << ogr2.ad << " "
					<< setw(20) << ogr2.soyad << " "
					<< setw(20) << ogr2.adres << " "
					<< setw(10) << ogr2.mesafe << " "
					<< setw(5) << ogr2.sinif << " "
					<< setw(15) << ogr2.tel << " " << endl;
			}
			else if (s2 == 16)
			{
				s.ogrid++;
				file3 << left
					<< setw(5) << s.ogrid << " "
					<< setw(20) << ogr2.ad << " "
					<< setw(20) << ogr2.soyad << " "
					<< setw(20) << ogr2.adres << " "
					<< setw(10) << ogr2.mesafe << " "
					<< setw(5) << ogr2.sinif << " "
					<< setw(15) << ogr.tel << " " << endl;
			}
			else if (s2 == 64)
			{

			}


			if (s3 == 224)
			{
				_temp_ogrid++;
				file2 << left
					<< setw(5) << _temp_ogrid << " "
					<< setw(20) << ogr3.ad << " "
					<< setw(20) << ogr3.soyad << " "
					<< setw(20) << ogr3.adres << " "
					<< setw(10) << ogr3.mesafe << " "
					<< setw(5) << ogr3.sinif << " "
					<< setw(15) << ogr3.tel << " " << endl;
			}
			else if (s3 == 16)
			{
				s.ogrid++;
				file3 << left
					<< setw(5) << s.ogrid << " "
					<< setw(20) << ogr3.ad << " "
					<< setw(20) << ogr3.soyad << " "
					<< setw(20) << ogr3.adres << " "
					<< setw(10) << ogr3.mesafe << " "
					<< setw(5) << ogr3.sinif << " "
					<< setw(15) << ogr3.tel << " " << endl;
			}
			else if (s3 == 64)
			{

			}




			if (s4 == 224)
			{
				_temp_ogrid++;
				file2 << left
					<< setw(5) << _temp_ogrid << " "
					<< setw(20) << ogr4.ad << " "
					<< setw(20) << ogr4.soyad << " "
					<< setw(20) << ogr4.adres << " "
					<< setw(10) << ogr4.mesafe << " "
					<< setw(5) << ogr4.sinif << " "
					<< setw(15) << ogr4.tel << " " << endl;
			}
			else if (s4 == 16)
			{
				s.ogrid++;
				file3 << left
					<< setw(5) << s.ogrid << " "
					<< setw(20) << ogr4.ad << " "
					<< setw(20) << ogr4.soyad << " "
					<< setw(20) << ogr4.adres << " "
					<< setw(10) << ogr4.mesafe << " "
					<< setw(5) << ogr4.sinif << " "
					<< setw(15) << ogr4.tel << " " << endl;
			}
			else if (s4 == 64)
			{

			}



			if (s5 == 224)
			{
				_temp_ogrid++;
				file2 << left
					<< setw(5) << _temp_ogrid << " "
					<< setw(20) << ogr5.ad << " "
					<< setw(20) << ogr5.soyad << " "
					<< setw(20) << ogr5.adres << " "
					<< setw(10) << ogr5.mesafe << " "
					<< setw(5) << ogr5.sinif << " "
					<< setw(15) << ogr5.tel << " " << endl;
			}
			else if (s5 == 16)
			{
				s.ogrid++;
				file3 << left
					<< setw(5) << s.ogrid << " "
					<< setw(20) << ogr5.ad << " "
					<< setw(20) << ogr5.soyad << " "
					<< setw(20) << ogr5.adres << " "
					<< setw(10) << ogr5.mesafe << " "
					<< setw(5) << ogr5.sinif << " "
					<< setw(15) << ogr5.tel << " " << endl;
			}
			else if (s5 == 64)
			{

			}

			file1.close();
			file2.close();
			file3.close();

			remove("waiting_storage.bin");
			rename("temp.bin", "waiting_storage.bin");

			main_menu();
		}


		system("cls");
		cout << "404 NOT FOUND";
		Sleep(3000);
		exit(0);

	}
}
void std_info_change()
{
	system("MODE CON: COLS=90 LINES=20");

	int pos2 = 4;
	int intsearch;
	bool checkbox1 = false, checkbox2 = true, find = false;
	string strsearch1, strsearch2, name, temp_name;

	SetConsoleTextAttribute(renk, 128);
	for (int i = 0; i < 90; i++)
	{
		cout << " ";
	}
	for (int i = 0; i < 18; i++)
	{
		SetConsoleTextAttribute(renk, 128);
		cout << "  ";
		for (int j = 0; j < 86; j++)
		{
			SetConsoleTextAttribute(renk, 112);
			cout << " ";
		}
		SetConsoleTextAttribute(renk, 128);
		cout << "  " << endl;
	}
	SetConsoleTextAttribute(renk, 128);
	for (int i = 0; i < 90; i++)
	{
		cout << " ";
	}
	SetConsoleTextAttribute(renk, 112);
	cursor_move(21, 3);
	cout << "Ad ve Soyada göre";
	cursor_move(28, 5);
	SetConsoleTextAttribute(renk, 224);
	cout << "  ";
	cursor_move(45, 3);
	SetConsoleTextAttribute(renk, 112);
	cout << "Öðrenci numarasýna göre";
	cursor_move(55, 5);
	SetConsoleTextAttribute(renk, 224);
	cout << "  ";

	SetConsoleTextAttribute(renk, 224);
	cursor_move(19, 8);
	cout << "                                              ";

	SetConsoleTextAttribute(renk, 112);
	cursor_move(20, 10);
	cout << " __________";
	cursor_move(20, 11);
	cout << "|          |";
	cursor_move(20, 12);
	cout << "|   GERÝ   |";
	cursor_move(20, 13);
	cout << "|__________|";

	cursor_move(50, 10);
	cout << " __________";
	cursor_move(50, 11);
	cout << "|          |";
	cursor_move(50, 12);
	cout << "|   ARA    |";
	cursor_move(50, 13);
	cout << "|__________|";

	while (true)
	{
	loop:
		state = button();
		if (state == 2 && pos2 < 5)
		{
			if (pos2 == 2 || pos2 == 3)
			{
				continue;
			}
			pos2++;
		}
		if (state == 1 && pos2 > 1)
		{
			if (pos2 == 3)
			{
				continue;
			}
			pos2--;
		}
		if (state == 3 && pos2 > 2)
		{
			if (pos2 == 2)
			{
				continue;
			}
			else if (pos2 == 4)
			{
				pos2 = 3;
				continue;
			}
			pos2 -= 2;
		}
		if (state == 4 && pos2 < 4)
		{
			if (pos2 == 2)
			{
				pos2 = 3;
				continue;
			}
			pos2 += 2;
		}
		if (state == 7)
		{
			break;
		}

		if (pos2 == 1)
		{
			if (!checkbox1)
			{
				cursor_move(28, 5);
				SetConsoleTextAttribute(renk, 240);
				cout << "  ";
			}
			else if (checkbox1)
			{
				cursor_move(28, 5);
				SetConsoleTextAttribute(renk, 240);
				cout << "\\/";
			}
		}
		else
		{
			if (!checkbox1)
			{
				cursor_move(28, 5);
				SetConsoleTextAttribute(renk, 224);
				cout << "  ";
			}
			else if (checkbox1)
			{
				cursor_move(28, 5);
				SetConsoleTextAttribute(renk, 224);
				cout << "\\/";
			}
		}
		if (pos2 == 2)
		{
			if (!checkbox2)
			{
				cursor_move(55, 5);
				SetConsoleTextAttribute(renk, 240);
				cout << "  ";
			}
			else if (checkbox2)
			{
				cursor_move(55, 5);
				SetConsoleTextAttribute(renk, 240);
				cout << "\\/";
			}
		}
		else
		{
			if (!checkbox2)
			{
				cursor_move(55, 5);
				SetConsoleTextAttribute(renk, 224);
				cout << "  ";
			}
			else if (checkbox2)
			{
				cursor_move(55, 5);
				SetConsoleTextAttribute(renk, 224);
				cout << "\\/";
			}
		}

		if (pos2 == 3)
		{
			SetConsoleTextAttribute(renk, 240);
			cursor_move(13, 8);
			cout << "{*}>";
		}
		else
		{
			SetConsoleTextAttribute(renk, 112);
			cursor_move(13, 8);
			cout << "    ";
		}

		if (pos2 == 4)
		{
			SetConsoleTextAttribute(renk, 120);
			cursor_move(20, 10);
			cout << " __________";
			SetConsoleTextAttribute(renk, 248);
			cursor_move(20, 11);
			cout << "|          |";
			cursor_move(20, 12);
			cout << "|   GERÝ   |";
			cursor_move(20, 13);
			cout << "|__________|";
		}
		else
		{
			SetConsoleTextAttribute(renk, 112);
			cursor_move(20, 10);
			cout << " __________";
			cursor_move(20, 11);
			cout << "|          |";
			cursor_move(20, 12);
			cout << "|   GERÝ   |";
			cursor_move(20, 13);
			cout << "|__________|";
		}
		if (pos2 == 5)
		{
			SetConsoleTextAttribute(renk, 120);
			cursor_move(50, 10);
			cout << " __________";
			SetConsoleTextAttribute(renk, 248);
			cursor_move(50, 11);
			cout << "|          |";
			cursor_move(50, 12);
			cout << "|   ARA    |";
			cursor_move(50, 13);
			cout << "|__________|";
		}
		else
		{
			SetConsoleTextAttribute(renk, 112);
			cursor_move(50, 10);
			cout << " __________";
			cursor_move(50, 11);
			cout << "|          |";
			cursor_move(50, 12);
			cout << "|   ARA    |";
			cursor_move(50, 13);
			cout << "|__________|";
		}

		Sleep(700);
	}
	if (pos2 == 1)
	{
		checkbox1 = !checkbox1;
		if (checkbox2)
		{
			checkbox2 = !checkbox2;
		}
		goto loop;
	}
	if (pos2 == 2)
	{
		checkbox2 = !checkbox2;
		if (checkbox1)
		{
			checkbox1 = !checkbox1;
		}
		goto loop;
	}
	if (pos2 == 3)
	{
		SetConsoleTextAttribute(renk, 96);
		cursor_move(19, 8);
		cout << "                                              ";
		cursor_move(19, 8);
		if (checkbox1)
		{
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			cin >> strsearch1;
			cin >> strsearch2;
			temp_name = strsearch1 + " " + strsearch2;
			cursor_move(19, 8);
			SetConsoleTextAttribute(renk, 224);
			cout << "                                              ";
			cursor_move(19, 8);

			cout << temp_name;
			goto loop;
		}
		else if (checkbox2)
		{
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			cin >> intsearch;
			cursor_move(19, 8);
			SetConsoleTextAttribute(renk, 224);
			cout << "                                              ";
			cursor_move(19, 8);
			cout << intsearch;
			goto loop;
		}
	}
	if (pos2 == 4)
	{
		main_menu();
	}
	if (pos2 = 5)
	{
		if (checkbox1)  //birinci checkbox iþaretli ise string yani ada ve soyada göre arama yapar.
		{
			system("MODE CON: COLS=80 LINES=25");
			file1.open("storage.bin", ios::in);
			file2.open("temp_storage.bin", ios::out);

			while (!file1.eof())
			{
				file1 >> s.ogrid >> ogr.ad >> ogr.soyad >> ogr.adres >> ogr.mesafe >> ogr.sinif >> ogr.tel;

				name = ogr.ad + " " + ogr.soyad;

				if (readed != s.ogrid)
				{
					if (temp_name == name)//öðrenci eþleþirse
					{
						find = true;

					loop2:

						cursor_move(0, 0);
						SetConsoleTextAttribute(renk, 32);
						for (int i = 0; i < 80; i++)
						{
							cout << " ";
						}
						for (int i = 0; i < 23; i++)
						{
							SetConsoleTextAttribute(renk, 32);
							cout << "  ";
							for (int j = 0; j < 76; j++)
							{
								SetConsoleTextAttribute(renk, 160);
								cout << " ";
							}
							SetConsoleTextAttribute(renk, 32);
							cout << "  " << endl;
						}
						SetConsoleTextAttribute(renk, 32);
						for (int i = 0; i < 80; i++)
						{
							cout << " ";
						}

						cursor_move(10, 6);
						SetConsoleTextAttribute(renk, 164);
						cout << "Ad Soyad: ";
						SetConsoleTextAttribute(renk, 160);
						cout << name;
						cursor_move(10, 8);
						SetConsoleTextAttribute(renk, 164);
						cout << "Sýnýf: ";
						SetConsoleTextAttribute(renk, 160);
						cout << ogr.sinif;
						cursor_move(10, 10);
						SetConsoleTextAttribute(renk, 164);
						cout << "Adresi(Semt): ";
						SetConsoleTextAttribute(renk, 160);
						cout << ogr.adres;
						cursor_move(10, 12);
						SetConsoleTextAttribute(renk, 164);
						cout << "Mesafe(metre): ";
						SetConsoleTextAttribute(renk, 160);
						cout << ogr.mesafe;
						cursor_move(10, 14);
						SetConsoleTextAttribute(renk, 164);
						cout << "Telefon Numarasý: ";
						SetConsoleTextAttribute(renk, 160);
						cout << ogr.tel;

						SetConsoleTextAttribute(renk, 175);
						cursor_move(7, 17);
						cout << " __________";
						cursor_move(7, 18);
						cout << "|          |";
						cursor_move(7, 19);
						cout << "|   GERÝ   |";
						cursor_move(7, 20);
						cout << "|__________|";

						SetConsoleTextAttribute(renk, 175);
						cursor_move(34, 17);
						cout << " __________";
						cursor_move(34, 18);
						cout << "|          |";
						cursor_move(34, 19);
						cout << "|   SÝL    |";
						cursor_move(34, 20);
						cout << "|__________|";

						SetConsoleTextAttribute(renk, 175);
						cursor_move(61, 17);
						cout << " __________";
						cursor_move(61, 18);
						cout << "|          |";
						cursor_move(61, 19);
						cout << "| Güncelle |";
						cursor_move(61, 20);
						cout << "|__________|";


						pos2 = 1;

						while (true)
						{
							state = button();
							if (state == 1 && pos2 > 1)
							{
								pos2--;
							}
							if (state == 2 && pos2 < 3)
							{
								pos2++;
							}
							if (state == 7)
							{
								break;
							}

							if (pos2 == 1)
							{
								SetConsoleTextAttribute(renk, 250);
								cursor_move(7, 18);
								cout << "|          |";
								cursor_move(7, 19);
								cout << "|   GERÝ   |";
								cursor_move(7, 20);
								cout << "|__________|";
							}
							else
							{
								SetConsoleTextAttribute(renk, 175);
								cursor_move(7, 18);
								cout << "|          |";
								cursor_move(7, 19);
								cout << "|   GERÝ   |";
								cursor_move(7, 20);
								cout << "|__________|";
							}
							if (pos2 == 2)
							{
								SetConsoleTextAttribute(renk, 250);
								cursor_move(34, 18);
								cout << "|          |";
								cursor_move(34, 19);
								cout << "|   SÝL    |";
								cursor_move(34, 20);
								cout << "|__________|";
							}
							else
							{
								SetConsoleTextAttribute(renk, 175);
								cursor_move(34, 18);
								cout << "|          |";
								cursor_move(34, 19);
								cout << "|   SÝL    |";
								cursor_move(34, 20);
								cout << "|__________|";
							}
							if (pos2 == 3)
							{
								SetConsoleTextAttribute(renk, 250);
								cursor_move(61, 18);
								cout << "|          |";
								cursor_move(61, 19);
								cout << "| Güncelle |";
								cursor_move(61, 20);
								cout << "|__________|";
							}
							else
							{
								SetConsoleTextAttribute(renk, 175);
								cursor_move(61, 18);
								cout << "|          |";
								cursor_move(61, 19);
								cout << "| Güncelle |";
								cursor_move(61, 20);
								cout << "|__________|";
							}
							Sleep(300);
						}
						if (pos2 == 1)
						{
							file2 << left
								<< setw(5) << s.ogrid << " "
								<< setw(20) << ogr.ad << " "
								<< setw(20) << ogr.soyad << " "
								<< setw(20) << ogr.adres << " "
								<< setw(10) << ogr.mesafe << " "
								<< setw(5) << ogr.sinif << " "
								<< setw(15) << ogr.tel << " " << endl;
						}
						if (pos2 == 2)
						{
							{
								cursor_move(17, 8);
								SetConsoleTextAttribute(renk, 244);
								cout << "///////////////////////////////////////////////";
								cursor_move(17, 9);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 10);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "     Silmek Ýstediðinize emin misiniz?     ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 11);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 12);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 13);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "          ";
								SetConsoleTextAttribute(renk, 244);
								cout << "Evet";
								SetConsoleTextAttribute(renk, 64);
								cout << "              ";
								SetConsoleTextAttribute(renk, 244);
								cout << "Hayýr";
								SetConsoleTextAttribute(renk, 64);
								cout << "          ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 14);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 15);
								SetConsoleTextAttribute(renk, 244);
								cout << "///////////////////////////////////////////////";
							}

							Sleep(500);
							pos2 = 2;
							while (true)
							{
								state = button();
								if (state == 1 && pos2 > 1)
								{
									pos2--;
								}
								if (state == 2 && pos2 < 2)
								{
									pos2++;
								}
								if (state == 7)
								{
									break;
								}

								if (pos2 == 1)
								{
									cursor_move(29, 13);
									SetConsoleTextAttribute(renk, 31);
									cout << "Evet";
								}
								else
								{
									cursor_move(29, 13);
									SetConsoleTextAttribute(renk, 244);
									cout << "Evet";
								}
								if (pos2 == 2)
								{
									cursor_move(47, 13);
									SetConsoleTextAttribute(renk, 31);
									cout << "Hayýr";
								}
								else
								{
									cursor_move(47, 13);
									SetConsoleTextAttribute(renk, 244);
									cout << "Hayýr";
								}

								cursor_move(0, 0);
								Sleep(300);
							}
							if (pos2 == 1)
							{
								cursor_move(17, 8);
								SetConsoleTextAttribute(renk, 244);
								cout << "///////////////////////////////////////////////";
								cursor_move(17, 9);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 10);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 11);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "              Öðrenci Silindi              ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 12);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 13);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 14);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 15);
								SetConsoleTextAttribute(renk, 244);
								cout << "///////////////////////////////////////////////";
								Sleep(2500);
								goto label;
							}
							if (pos2 == 2)
							{
								goto loop2;
							}

						}
						if (pos2 == 3)
						{
							ogr1.ad = ogr.ad;
							ogr1.soyad = ogr.soyad;
							ogr1.sinif = ogr.sinif;
							ogr1.adres = ogr.adres;
							ogr1.mesafe = ogr.mesafe;
							ogr1.tel = ogr.tel;

							Sleep(200);
							cursor_move(5, 17);
							SetConsoleTextAttribute(renk, 160);
							cout << "                                                                     ";
							cursor_move(5, 18);
							cout << "                                                                     ";
							cursor_move(5, 19);
							cout << "                                                                     ";
							cursor_move(5, 20);
							cout << "                                                                     ";


							pos = 1;
							while (true)
							{
							label2:
								state = button();
								if (state == 1 && pos == 7)
								{
									pos--;
								}
								if (state == 2 && pos == 6)
								{
									pos++;
								}
								if (state == 3 && pos > 1)
								{
									if (pos > 5)
									{
										pos = 5;
										continue;
									}
									pos--;
								}
								if (state == 4 && pos < 7)
								{
									if (pos > 5)
									{
										continue;
									}
									pos++;
								}
								if (state == 7)
								{
									break;
								}
								if (pos == 1)
								{
									cursor_move(4, 6);
									SetConsoleTextAttribute(renk, 250);
									cout << "{*}>";
								}
								else
								{
									cursor_move(4, 6);
									SetConsoleTextAttribute(renk, 160);
									cout << "     ";
								}
								if (pos == 2)
								{
									cursor_move(4, 8);
									SetConsoleTextAttribute(renk, 250);
									cout << "{*}>";
								}
								else
								{
									cursor_move(4, 8);
									SetConsoleTextAttribute(renk, 160);
									cout << "     ";
								}
								if (pos == 3)
								{
									cursor_move(4, 10);
									SetConsoleTextAttribute(renk, 250);
									cout << "{*}>";
								}
								else
								{
									cursor_move(4, 10);
									SetConsoleTextAttribute(renk, 160);
									cout << "     ";
								}
								if (pos == 4)
								{
									cursor_move(4, 12);
									SetConsoleTextAttribute(renk, 250);
									cout << "{*}>";
								}
								else
								{
									cursor_move(4, 12);
									SetConsoleTextAttribute(renk, 160);
									cout << "     ";
								}
								if (pos == 5)
								{
									cursor_move(4, 14);
									SetConsoleTextAttribute(renk, 250);
									cout << "{*}>";
								}
								else
								{
									cursor_move(4, 14);
									SetConsoleTextAttribute(renk, 160);
									cout << "     ";
								}
								if (pos == 6)
								{
									SetConsoleTextAttribute(renk, 250);
									cursor_move(7, 18);
									cout << "|           |";
									cursor_move(7, 19);
									cout << "|   ÝPTAL   |";
									cursor_move(7, 20);
									cout << "|___________|";
								}
								else
								{
									SetConsoleTextAttribute(renk, 175);
									cursor_move(7, 17);
									cout << " ___________";
									cursor_move(7, 18);
									cout << "|           |";
									cursor_move(7, 19);
									cout << "|   ÝPTAL   |";
									cursor_move(7, 20);
									cout << "|___________|";
								}
								if (pos == 7)
								{
									SetConsoleTextAttribute(renk, 250);
									cursor_move(34, 18);
									cout << "|          |";
									cursor_move(34, 19);
									cout << "|  KAYDET  |";
									cursor_move(34, 20);
									cout << "|__________|";
								}
								else
								{
									SetConsoleTextAttribute(renk, 175);
									cursor_move(34, 17);
									cout << " __________";
									cursor_move(34, 18);
									cout << "|          |";
									cursor_move(34, 19);
									cout << "|  KAYDET  |";
									cursor_move(34, 20);
									cout << "|__________|";
								}

								Sleep(200);
							}
							if (pos == 1)
							{
								cursor_move(20, 6);
								SetConsoleTextAttribute(renk, 160);
								cout << "                              ";
								cursor_move(20, 6);
								FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
								cin >> ogr.ad;
								FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
								cin >> ogr.soyad;
								name = ogr.ad + " " + ogr.soyad;
								SetConsoleTextAttribute(renk, 160);
								cursor_move(20, 6);
								cout << "                              ";
								cursor_move(20, 6);
								cout << name;
								goto label2;
							}
							if (pos == 2)
							{
								cursor_move(17, 8);
								SetConsoleTextAttribute(renk, 160);
								cout << "                              ";
								cursor_move(17, 8);
								FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
								cin >> ogr.sinif;
								SetConsoleTextAttribute(renk, 160);
								cursor_move(17, 8);
								cout << "                              ";
								cursor_move(17, 8);
								cout << ogr.sinif;
								goto label2;
							}
							if (pos == 3)
							{
								cursor_move(24, 10);
								SetConsoleTextAttribute(renk, 160);
								cout << "                              ";
								cursor_move(24, 10);
								FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
								cin >> ogr.adres;
								SetConsoleTextAttribute(renk, 160);
								cursor_move(24, 10);
								cout << "                              ";
								cursor_move(24, 10);
								cout << ogr.adres;
								goto label2;
							}
							if (pos == 4)
							{
								cursor_move(25, 12);
								SetConsoleTextAttribute(renk, 160);
								cout << "                              ";
								cursor_move(25, 12);
								FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
								cin >> ogr.mesafe;
								SetConsoleTextAttribute(renk, 160);
								cursor_move(25, 12);
								cout << "                              ";
								cursor_move(25, 12);
								cout << ogr.mesafe;
								goto label2;
							}
							if (pos == 5)
							{
								cursor_move(28, 14);
								SetConsoleTextAttribute(renk, 160);
								cout << "                              ";
								cursor_move(28, 14);
								FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
								cin >> ogr.tel;
								SetConsoleTextAttribute(renk, 160);
								cursor_move(28, 14);
								cout << "                              ";
								cursor_move(28, 14);
								cout << ogr.tel;
								goto label2;
							}
							if (pos == 6)
							{
								ogr.ad = ogr1.ad;
								ogr.soyad = ogr1.soyad;
								ogr.sinif = ogr1.sinif;
								ogr.adres = ogr1.adres;
								ogr.mesafe = ogr1.mesafe;
								ogr.tel = ogr1.tel;
								goto loop2;
							}
							if (pos == 7)
							{
								file2 << left
									<< setw(5) << s.ogrid << " "
									<< setw(20) << ogr.ad << " "
									<< setw(20) << ogr.soyad << " "
									<< setw(20) << ogr.adres << " "
									<< setw(10) << ogr.mesafe << " "
									<< setw(5) << ogr.sinif << " "
									<< setw(15) << ogr.tel << " " << endl;
							}

						}

					}
					else//öðrenci eþleþmezse
					{
						file2 << left
							<< setw(5) << s.ogrid << " "
							<< setw(20) << ogr.ad << " "
							<< setw(20) << ogr.soyad << " "
							<< setw(20) << ogr.adres << " "
							<< setw(10) << ogr.mesafe << " "
							<< setw(5) << ogr.sinif << " "
							<< setw(15) << ogr.tel << " " << endl;
					}
				}
			label:
				readed = s.ogrid;
			}
			if (!find)
			{
				system("MODE CON: COLS=90 LINES=20");

				SetConsoleTextAttribute(renk, 64);
				for (int i = 0; i < 90; i++)
				{
					cout << " ";
				}
				SetConsoleTextAttribute(renk, 192);
				for (int i = 0; i < 18; i++)
				{
					SetConsoleTextAttribute(renk, 64);
					cout << "  ";
					for (int j = 0; j < 86; j++)
					{
						SetConsoleTextAttribute(renk, 192);
						cout << " ";
					}
					SetConsoleTextAttribute(renk, 64);
					cout << "  " << endl;
				}
				SetConsoleTextAttribute(renk, 64);
				for (int i = 0; i < 90; i++)
				{
					cout << " ";
				}
				SetConsoleTextAttribute(renk, 207);
				cursor_move(25, 6);
				cout << "Kayýtta böyle bir öðrenci bulunmamaktadýr.";
				cursor_move(38, 9);
				cout << " __________";
				cursor_move(38, 10);
				cout << "|          |";
				cursor_move(38, 11);
				cout << "|   GERÝ   |";
				cursor_move(38, 12);
				cout << "|__________|";

				pos = 1;
				while (true)
				{
					state = button();
					if (state == 7)
					{
						break;
					}
					if (pos == 1)
					{
						SetConsoleTextAttribute(renk, 207);
						cursor_move(38, 9);
						cout << " __________";
						SetConsoleTextAttribute(renk, 252);
						cursor_move(38, 10);
						cout << "|          |";
						cursor_move(38, 11);
						cout << "|   GERÝ   |";
						cursor_move(38, 12);
						cout << "|__________|";
						cursor_move(0, 0);
					}
					Sleep(200);
				}
				if (pos == 1)
				{
					std_info_change();
				}

			}

			file1.close();
			file2.close();
			remove("storage.bin");
			rename("temp_storage.bin", "storage.bin");
			std_info_change();
		}
		else if (checkbox2)  //birinci checkbox iþaretli ise sayisal yani numaraya göre arama yapar.
		{
			system("MODE CON: COLS=80 LINES=25");
			file1.open("storage.bin", ios::in);
			file2.open("temp_storage.bin", ios::out);

			while (!file1.eof())
			{
				file1 >> s.ogrid >> ogr.ad >> ogr.soyad >> ogr.adres >> ogr.mesafe >> ogr.sinif >> ogr.tel;

				name = ogr.ad + " " + ogr.soyad;

				if (readed != s.ogrid)
				{
					if (intsearch == s.ogrid)//öðrenci eþleþirse
					{
						find = true;

					loop3:

						cursor_move(0, 0);
						SetConsoleTextAttribute(renk, 32);
						for (int i = 0; i < 80; i++)
						{
							cout << " ";
						}
						for (int i = 0; i < 23; i++)
						{
							SetConsoleTextAttribute(renk, 32);
							cout << "  ";
							for (int j = 0; j < 76; j++)
							{
								SetConsoleTextAttribute(renk, 160);
								cout << " ";
							}
							SetConsoleTextAttribute(renk, 32);
							cout << "  " << endl;
						}
						SetConsoleTextAttribute(renk, 32);
						for (int i = 0; i < 80; i++)
						{
							cout << " ";
						}

						cursor_move(10, 6);
						SetConsoleTextAttribute(renk, 164);
						cout << "Ad Soyad: ";
						SetConsoleTextAttribute(renk, 160);
						cout << name;
						cursor_move(10, 8);
						SetConsoleTextAttribute(renk, 164);
						cout << "Sýnýf: ";
						SetConsoleTextAttribute(renk, 160);
						cout << ogr.sinif;
						cursor_move(10, 10);
						SetConsoleTextAttribute(renk, 164);
						cout << "Adresi(Semt): ";
						SetConsoleTextAttribute(renk, 160);
						cout << ogr.adres;
						cursor_move(10, 12);
						SetConsoleTextAttribute(renk, 164);
						cout << "Mesafe(metre): ";
						SetConsoleTextAttribute(renk, 160);
						cout << ogr.mesafe;
						cursor_move(10, 14);
						SetConsoleTextAttribute(renk, 164);
						cout << "Telefon Numarasý: ";
						SetConsoleTextAttribute(renk, 160);
						cout << ogr.tel;

						SetConsoleTextAttribute(renk, 175);
						cursor_move(7, 17);
						cout << " __________";
						cursor_move(7, 18);
						cout << "|          |";
						cursor_move(7, 19);
						cout << "|   GERÝ   |";
						cursor_move(7, 20);
						cout << "|__________|";

						SetConsoleTextAttribute(renk, 175);
						cursor_move(34, 17);
						cout << " __________";
						cursor_move(34, 18);
						cout << "|          |";
						cursor_move(34, 19);
						cout << "|   SÝL    |";
						cursor_move(34, 20);
						cout << "|__________|";

						SetConsoleTextAttribute(renk, 175);
						cursor_move(61, 17);
						cout << " __________";
						cursor_move(61, 18);
						cout << "|          |";
						cursor_move(61, 19);
						cout << "| Güncelle |";
						cursor_move(61, 20);
						cout << "|__________|";


						pos2 = 1;

						while (true)
						{
							state = button();
							if (state == 1 && pos2 > 1)
							{
								pos2--;
							}
							if (state == 2 && pos2 < 3)
							{
								pos2++;
							}
							if (state == 7)
							{
								break;
							}

							if (pos2 == 1)
							{
								SetConsoleTextAttribute(renk, 250);
								cursor_move(7, 18);
								cout << "|          |";
								cursor_move(7, 19);
								cout << "|   GERÝ   |";
								cursor_move(7, 20);
								cout << "|__________|";
							}
							else
							{
								SetConsoleTextAttribute(renk, 175);
								cursor_move(7, 18);
								cout << "|          |";
								cursor_move(7, 19);
								cout << "|   GERÝ   |";
								cursor_move(7, 20);
								cout << "|__________|";
							}
							if (pos2 == 2)
							{
								SetConsoleTextAttribute(renk, 250);
								cursor_move(34, 18);
								cout << "|          |";
								cursor_move(34, 19);
								cout << "|   SÝL    |";
								cursor_move(34, 20);
								cout << "|__________|";
							}
							else
							{
								SetConsoleTextAttribute(renk, 175);
								cursor_move(34, 18);
								cout << "|          |";
								cursor_move(34, 19);
								cout << "|   SÝL    |";
								cursor_move(34, 20);
								cout << "|__________|";
							}
							if (pos2 == 3)
							{
								SetConsoleTextAttribute(renk, 250);
								cursor_move(61, 18);
								cout << "|          |";
								cursor_move(61, 19);
								cout << "| Güncelle |";
								cursor_move(61, 20);
								cout << "|__________|";
							}
							else
							{
								SetConsoleTextAttribute(renk, 175);
								cursor_move(61, 18);
								cout << "|          |";
								cursor_move(61, 19);
								cout << "| Güncelle |";
								cursor_move(61, 20);
								cout << "|__________|";
							}
							Sleep(300);
						}
						if (pos2 == 1)
						{
							file2 << left
								<< setw(5) << s.ogrid << " "
								<< setw(20) << ogr.ad << " "
								<< setw(20) << ogr.soyad << " "
								<< setw(20) << ogr.adres << " "
								<< setw(10) << ogr.mesafe << " "
								<< setw(5) << ogr.sinif << " "
								<< setw(15) << ogr.tel << " " << endl;
						}
						if (pos2 == 2)
						{
							{
								cursor_move(17, 8);
								SetConsoleTextAttribute(renk, 244);
								cout << "///////////////////////////////////////////////";
								cursor_move(17, 9);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 10);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "     Silmek Ýstediðinize emin misiniz?     ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 11);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 12);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 13);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "          ";
								SetConsoleTextAttribute(renk, 244);
								cout << "Evet";
								SetConsoleTextAttribute(renk, 64);
								cout << "              ";
								SetConsoleTextAttribute(renk, 244);
								cout << "Hayýr";
								SetConsoleTextAttribute(renk, 64);
								cout << "          ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 14);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 15);
								SetConsoleTextAttribute(renk, 244);
								cout << "///////////////////////////////////////////////";
							}

							Sleep(500);
							pos2 = 2;
							while (true)
							{
								state = button();
								if (state == 1 && pos2 > 1)
								{
									pos2--;
								}
								if (state == 2 && pos2 < 2)
								{
									pos2++;
								}
								if (state == 7)
								{
									break;
								}

								if (pos2 == 1)
								{
									cursor_move(29, 13);
									SetConsoleTextAttribute(renk, 31);
									cout << "Evet";
								}
								else
								{
									cursor_move(29, 13);
									SetConsoleTextAttribute(renk, 244);
									cout << "Evet";
								}
								if (pos2 == 2)
								{
									cursor_move(47, 13);
									SetConsoleTextAttribute(renk, 31);
									cout << "Hayýr";
								}
								else
								{
									cursor_move(47, 13);
									SetConsoleTextAttribute(renk, 244);
									cout << "Hayýr";
								}

								cursor_move(0, 0);
								Sleep(300);
							}
							if (pos2 == 1)
							{
								cursor_move(17, 8);
								SetConsoleTextAttribute(renk, 244);
								cout << "///////////////////////////////////////////////";
								cursor_move(17, 9);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 10);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 11);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "              Öðrenci Silindi              ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 12);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 13);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 14);
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								SetConsoleTextAttribute(renk, 64);
								cout << "                                           ";
								SetConsoleTextAttribute(renk, 244);
								cout << "//";
								cursor_move(17, 15);
								SetConsoleTextAttribute(renk, 244);
								cout << "///////////////////////////////////////////////";
								Sleep(2500);
								goto label3;
							}
							if (pos2 == 2)
							{
								goto loop3;
							}

						}
						if (pos2 == 3)
						{
							ogr1.ad = ogr.ad;
							ogr1.soyad = ogr.soyad;
							ogr1.sinif = ogr.sinif;
							ogr1.adres = ogr.adres;
							ogr1.mesafe = ogr.mesafe;
							ogr1.tel = ogr.tel;

							Sleep(200);
							cursor_move(5, 17);
							SetConsoleTextAttribute(renk, 160);
							cout << "                                                                     ";
							cursor_move(5, 18);
							cout << "                                                                     ";
							cursor_move(5, 19);
							cout << "                                                                     ";
							cursor_move(5, 20);
							cout << "                                                                     ";


							pos = 1;
							while (true)
							{
							label4:
								state = button();
								if (state == 1 && pos == 7)
								{
									pos--;
								}
								if (state == 2 && pos == 6)
								{
									pos++;
								}
								if (state == 3 && pos > 1)
								{
									if (pos > 5)
									{
										pos = 5;
										continue;
									}
									pos--;
								}
								if (state == 4 && pos < 7)
								{
									if (pos > 5)
									{
										continue;
									}
									pos++;
								}
								if (state == 7)
								{
									break;
								}
								if (pos == 1)
								{
									cursor_move(4, 6);
									SetConsoleTextAttribute(renk, 250);
									cout << "{*}>";
								}
								else
								{
									cursor_move(4, 6);
									SetConsoleTextAttribute(renk, 160);
									cout << "     ";
								}
								if (pos == 2)
								{
									cursor_move(4, 8);
									SetConsoleTextAttribute(renk, 250);
									cout << "{*}>";
								}
								else
								{
									cursor_move(4, 8);
									SetConsoleTextAttribute(renk, 160);
									cout << "     ";
								}
								if (pos == 3)
								{
									cursor_move(4, 10);
									SetConsoleTextAttribute(renk, 250);
									cout << "{*}>";
								}
								else
								{
									cursor_move(4, 10);
									SetConsoleTextAttribute(renk, 160);
									cout << "     ";
								}
								if (pos == 4)
								{
									cursor_move(4, 12);
									SetConsoleTextAttribute(renk, 250);
									cout << "{*}>";
								}
								else
								{
									cursor_move(4, 12);
									SetConsoleTextAttribute(renk, 160);
									cout << "     ";
								}
								if (pos == 5)
								{
									cursor_move(4, 14);
									SetConsoleTextAttribute(renk, 250);
									cout << "{*}>";
								}
								else
								{
									cursor_move(4, 14);
									SetConsoleTextAttribute(renk, 160);
									cout << "     ";
								}
								if (pos == 6)
								{
									SetConsoleTextAttribute(renk, 250);
									cursor_move(7, 18);
									cout << "|           |";
									cursor_move(7, 19);
									cout << "|   ÝPTAL   |";
									cursor_move(7, 20);
									cout << "|___________|";
								}
								else
								{
									SetConsoleTextAttribute(renk, 175);
									cursor_move(7, 17);
									cout << " ___________";
									cursor_move(7, 18);
									cout << "|           |";
									cursor_move(7, 19);
									cout << "|   ÝPTAL   |";
									cursor_move(7, 20);
									cout << "|___________|";
								}
								if (pos == 7)
								{
									SetConsoleTextAttribute(renk, 250);
									cursor_move(34, 18);
									cout << "|          |";
									cursor_move(34, 19);
									cout << "|  KAYDET  |";
									cursor_move(34, 20);
									cout << "|__________|";
								}
								else
								{
									SetConsoleTextAttribute(renk, 175);
									cursor_move(34, 17);
									cout << " __________";
									cursor_move(34, 18);
									cout << "|          |";
									cursor_move(34, 19);
									cout << "|  KAYDET  |";
									cursor_move(34, 20);
									cout << "|__________|";
								}

								Sleep(200);
							}
							if (pos == 1)
							{
								cursor_move(20, 6);
								SetConsoleTextAttribute(renk, 160);
								cout << "                              ";
								cursor_move(20, 6);
								FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
								cin >> ogr.ad;
								FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
								cin >> ogr.soyad;
								name = ogr.ad + " " + ogr.soyad;
								SetConsoleTextAttribute(renk, 160);
								cursor_move(20, 6);
								cout << "                              ";
								cursor_move(20, 6);
								cout << name;
								goto label4;
							}
							if (pos == 2)
							{
								cursor_move(17, 8);
								SetConsoleTextAttribute(renk, 160);
								cout << "                              ";
								cursor_move(17, 8);
								FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
								cin >> ogr.sinif;
								SetConsoleTextAttribute(renk, 160);
								cursor_move(17, 8);
								cout << "                              ";
								cursor_move(17, 8);
								cout << ogr.sinif;
								goto label4;
							}
							if (pos == 3)
							{
								cursor_move(24, 10);
								SetConsoleTextAttribute(renk, 160);
								cout << "                              ";
								cursor_move(24, 10);
								FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
								cin >> ogr.adres;
								SetConsoleTextAttribute(renk, 160);
								cursor_move(24, 10);
								cout << "                              ";
								cursor_move(24, 10);
								cout << ogr.adres;
								goto label4;
							}
							if (pos == 4)
							{
								cursor_move(25, 12);
								SetConsoleTextAttribute(renk, 160);
								cout << "                              ";
								cursor_move(25, 12);
								FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
								cin >> ogr.mesafe;
								SetConsoleTextAttribute(renk, 160);
								cursor_move(25, 12);
								cout << "                              ";
								cursor_move(25, 12);
								cout << ogr.mesafe;
								goto label4;
							}
							if (pos == 5)
							{
								cursor_move(28, 14);
								SetConsoleTextAttribute(renk, 160);
								cout << "                              ";
								cursor_move(28, 14);
								FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
								cin >> ogr.tel;
								SetConsoleTextAttribute(renk, 160);
								cursor_move(28, 14);
								cout << "                              ";
								cursor_move(28, 14);
								cout << ogr.tel;
								goto label4;
							}
							if (pos == 6)
							{
								ogr.ad = ogr1.ad;
								ogr.soyad = ogr1.soyad;
								ogr.sinif = ogr1.sinif;
								ogr.adres = ogr1.adres;
								ogr.mesafe = ogr1.mesafe;
								ogr.tel = ogr1.tel;
								goto loop3;
							}
							if (pos == 7)
							{
								file2 << left
									<< setw(5) << s.ogrid << " "
									<< setw(20) << ogr.ad << " "
									<< setw(20) << ogr.soyad << " "
									<< setw(20) << ogr.adres << " "
									<< setw(10) << ogr.mesafe << " "
									<< setw(5) << ogr.sinif << " "
									<< setw(15) << ogr.tel << " " << endl;
							}

						}

					}
					else//öðrenci eþleþmezse
					{
						file2 << left
							<< setw(5) << s.ogrid << " "
							<< setw(20) << ogr.ad << " "
							<< setw(20) << ogr.soyad << " "
							<< setw(20) << ogr.adres << " "
							<< setw(10) << ogr.mesafe << " "
							<< setw(5) << ogr.sinif << " "
							<< setw(15) << ogr.tel << " " << endl;
					}
				}
			label3:
				readed = s.ogrid;
			}
			if (!find)
			{
				system("MODE CON: COLS=90 LINES=20");

				SetConsoleTextAttribute(renk, 64);
				for (int i = 0; i < 90; i++)
				{
					cout << " ";
				}
				SetConsoleTextAttribute(renk, 192);
				for (int i = 0; i < 18; i++)
				{
					SetConsoleTextAttribute(renk, 64);
					cout << "  ";
					for (int j = 0; j < 86; j++)
					{
						SetConsoleTextAttribute(renk, 192);
						cout << " ";
					}
					SetConsoleTextAttribute(renk, 64);
					cout << "  " << endl;
				}
				SetConsoleTextAttribute(renk, 64);
				for (int i = 0; i < 90; i++)
				{
					cout << " ";
				}
				SetConsoleTextAttribute(renk, 207);
				cursor_move(25, 6);
				cout << "Kayýtta böyle bir öðrenci bulunmamaktadýr.";
				cursor_move(38, 9);
				cout << " __________";
				cursor_move(38, 10);
				cout << "|          |";
				cursor_move(38, 11);
				cout << "|   GERÝ   |";
				cursor_move(38, 12);
				cout << "|__________|";

				pos = 1;
				while (true)
				{
					state = button();
					if (state == 7)
					{
						break;
					}
					if (pos == 1)
					{
						SetConsoleTextAttribute(renk, 207);
						cursor_move(38, 9);
						cout << " __________";
						SetConsoleTextAttribute(renk, 252);
						cursor_move(38, 10);
						cout << "|          |";
						cursor_move(38, 11);
						cout << "|   GERÝ   |";
						cursor_move(38, 12);
						cout << "|__________|";
						cursor_move(0, 0);
					}
					Sleep(200);
				}
				if (pos == 1)
				{
					std_info_change();
				}

			}

			file1.close();
			file2.close();
			remove("storage.bin");
			rename("temp_storage.bin", "storage.bin");
			std_info_change();
		}
		else    //eðer checkboxlarýn hiçbiri iþaretli deðilse arama yapmaz, sonsuz döngü devam eder.
		{
			goto loop;
		}
	}
}
void new_pas()
{

	int counter = 0, temp1, temp2;

	string username, password, temp_username, temp_password;

	file1.open("Ogrenci _Servis_Firmasý_Otomasyonu_Proje.bin", ios::in);

	file1 >> username >> password >> temp1 >> temp2;

	file1.close();

	system("MODE CON: COLS=85 LINES=23");
loop:
	cursor_move(0, 0);
	SetConsoleTextAttribute(renk, 64);
	for (int i = 0; i < 85; i++)
	{
		cout << " ";
	}
	for (int i = 0; i < 21; i++)
	{
		SetConsoleTextAttribute(renk, 64);
		cout << "  ";
		for (int j = 0; j < 81; j++)
		{
			SetConsoleTextAttribute(renk, 0);
			cout << " ";
		}
		SetConsoleTextAttribute(renk, 64);
		cout << "  ";
	}
	SetConsoleTextAttribute(renk, 64);
	for (int i = 0; i < 85; i++)
	{
		cout << " ";
	}
	SetConsoleTextAttribute(renk, 6);
	cursor_move(17, 6);
	cout << "Geçerli þifreyi giriniz";
	cursor_move(12, 11);
	cout << "Kullanýcý adý:";
	cursor_move(12, 13);
	cout << "Þifre:";
	cursor_move(8, 16);
	cout << "Geri Dön";

	pos = 2;
	while (true)
	{
		state = button();
		if (state == 4 && pos < 2)
		{
			pos++;
		}
		if (state == 3 && pos > 1)
		{
			pos--;
		}
		if (state == 7)
		{
			break;
		}

		if (pos == 1)
		{
			cursor_move(6, 11);
			SetConsoleTextAttribute(renk, 12);
			cout << "{*}>";

		}
		else
		{
			cursor_move(6, 11);
			cout << "     ";
		}
		if (pos == 2)
		{
			cursor_move(3, 16);
			SetConsoleTextAttribute(renk, 12);
			cout << "{*}>";
		}
		else
		{
			cursor_move(3, 16);
			cout << "     ";
		}

		Sleep(300);
	}
	if (pos == 1)
	{
		cursor_move(27, 11);
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		SetConsoleTextAttribute(renk, 15);
		cin >> temp_username;
		cursor_move(19, 13);
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		temp_password = getpassword();
		SetConsoleTextAttribute(renk, 6);

		counter++;

		if (temp_username == username && temp_password == password)
		{
			cursor_move(0, 0);
			SetConsoleTextAttribute(renk, 144);
			for (int i = 0; i < 85; i++)
			{
				cout << " ";
			}
			for (int i = 0; i < 21; i++)
			{
				SetConsoleTextAttribute(renk, 144);
				cout << "  ";
				for (int j = 0; j < 81; j++)
				{
					SetConsoleTextAttribute(renk, 48);
					cout << " ";
				}
				SetConsoleTextAttribute(renk, 144);
				cout << "  ";
			}
			SetConsoleTextAttribute(renk, 144);
			for (int i = 0; i < 85; i++)
			{
				cout << " ";
			}
			SetConsoleTextAttribute(renk, 63);
			cursor_move(17, 6);
			cout << "Yeni kullanýcý adý ve þifreyi giriniz";
			cursor_move(12, 11);
			cout << "Yeni Kullanýcý adý:";
			cursor_move(12, 13);
			cout << "Yeni Þifre:";

			cursor_move(33, 11);
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			cin >> username;
			cursor_move(25, 13);
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			cin >> password;

			file1.open("Ogrenci _Servis_Firmasý_Otomasyonu_Proje.bin", ios::out);

			file1 << username << "\t" << password << "\t" << temp1 << "\t" << temp2;

			file1.close();

			Sleep(1000);
			system("cls");
			system("color 2f");
			cursor_move(17, 6);
			cout << "Ýþlem baþarýyla gerçekleþti";
			Sleep(2000);
			main_menu();

		}
		else
		{

			if (counter == 3)
			{
				cursor_move(0, 0);
				system("MODE CON: COLS=90 LINES=20");

				SetConsoleTextAttribute(renk, 64);
				for (int i = 0; i < 90; i++)
				{
					cout << " ";
				}
				SetConsoleTextAttribute(renk, 192);
				for (int i = 0; i < 18; i++)
				{
					SetConsoleTextAttribute(renk, 64);
					cout << "  ";
					for (int j = 0; j < 86; j++)
					{
						SetConsoleTextAttribute(renk, 192);
						cout << " ";
					}
					SetConsoleTextAttribute(renk, 64);
					cout << "  " << endl;
				}
				SetConsoleTextAttribute(renk, 64);
				for (int i = 0; i < 90; i++)
				{
					cout << " ";
				}
				SetConsoleTextAttribute(renk, 207);
				cursor_move(25, 6);
				cout << "!!!Çok fazla deneme yaptýnýz!!!";
				cursor_move(38, 9);
				cout << " __________";
				cursor_move(38, 10);
				cout << "|          |";
				cursor_move(38, 11);
				cout << "|   GERÝ   |";
				cursor_move(38, 12);
				cout << "|__________|";

				pos = 1;
				while (true)
				{
					state = button();
					if (state == 7)
					{
						break;
					}
					if (pos == 1)
					{
						SetConsoleTextAttribute(renk, 207);
						cursor_move(38, 9);
						cout << " __________";
						SetConsoleTextAttribute(renk, 252);
						cursor_move(38, 10);
						cout << "|          |";
						cursor_move(38, 11);
						cout << "|   GERÝ   |";
						cursor_move(38, 12);
						cout << "|__________|";
						cursor_move(0, 0);
					}
					Sleep(200);
				}
				if (pos == 1)
				{
					main_menu();
				}
			}
			SetConsoleTextAttribute(renk, 6);
			cursor_move(17, 6);
			SetConsoleTextAttribute(renk, 79);
			cout << "Kullanýcý adý veya þifreniz uyuþmuyor";
			SetConsoleTextAttribute(renk, 15);
			Sleep(2000);
			cursor_move(17, 6);
			SetConsoleTextAttribute(renk, 15);
			cout << "                                     ";
			SetConsoleTextAttribute(renk, 15);
			cursor_move(17, 6);
			SetConsoleTextAttribute(renk, 15);
			cout << "Geçerli þifreyi giriniz";
			cursor_move(27, 11);
			cout << "                                   ";
			cursor_move(29, 13);
			cout << "                                   ";
			goto loop;
		}


	}
	if (pos == 2)
	{
		main_menu();
	}

	cursor_move(0, 0);
	system("pause");


}
