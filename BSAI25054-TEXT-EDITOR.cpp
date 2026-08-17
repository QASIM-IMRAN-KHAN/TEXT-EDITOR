#include<iostream>
#include<windows.h>
#include<conio.h>
#include<math.h>
#include<vector>
#include"Document.h"
#include<fstream>
#include"MyString.h"
using namespace std;


void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
		ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState ==

			FROM_LEFT_1ST_BUTTON_PRESSED)

		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}

void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void color(int k)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}
void hideConsoleCursor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}
void printaline(int x1, int y1, int x2, int y2, char sym = -37, float alpha = 0.005)
{
	for (float i = 0; i <= 1; i += alpha)
	{
		int r = ceil((x1 * (1 - i)) + (x2 * i));
		int c = ceil((y1 * (1 - i)) + (y2 * i));

		if (x1 == x2)
		{
			r = x1;
		}

		if (y1 == y2)
		{
			c = y1;
		}

		gotoRowCol(r, c);
		cout << sym;
	}
}
bool Mystring::isEqual(const Mystring& M)
{
	if (M.size != size)
	{
		return false;
	}
	for (int i = 0; i < size; i++)
	{
		if (Cs[i] != M.Cs[i])
		{
			return false;
		}
	}
	return true;
}

Mystring::Mystring(const char* p)
{
	size = strlength(p);
	Cs = new char[size + 1];
	stringcopy(Cs, p);

}
int Mystring::strlength(const char* A)
{
	int i = 0;
	while (A[i] != '\0')
	{


		i++;
	}
	return i;



}
void Mystring::stringcopy(char* A, const char* B)
{
	int i = 0;
	while (B[i] != '\0')
	{
		A[i] = B[i];
		i++;
	}
	A[i] = '\0';




}
void toggle(Line& line,int r, int c)
{
	if (c >= 0 and c < line.linelength())
	{
		char ch = line.getchar(c);
		if (ch >= 'A' and ch <= 'Z')
		{
			ch += 32;
		}
		else if (ch >= 'a' and ch <= 'z')
		{
			ch -= 32;
		}
		line.removetext(c);
		line.inserttext(c, ch);
		gotoRowCol(r, 0);
		line.print();
		gotoRowCol(r, c);


	}
}
void deletetoend(Line& line,int r, int c)
{
	int l = line.linelength();
	for (int i = l-1; i>=c; i--)
	{
		line.removetext(i);
	}
	gotoRowCol(r, 0);
	cout << "                                                                                                           ";
	gotoRowCol(r, 0);
	line.print();
	gotoRowCol(r, c);
}
void copied(Document& p, int si, int pi, int li, vector<char>& copy, bool &iscopy)
{
	auto& line = p.getchapter(0).getsection(si).getpara(pi).getline(li);
	line.copyline(copy);
	iscopy = true;

} 
void pasted(Document& p, int &si, int &pi, int &li,int &r,int &c, vector<char>& copy, bool &iscopy, vector<char>& undo, bool &isundo)
{
	if (!iscopy)
	{
		return;
	}
	auto& line = p.getchapter(0).getsection(si).getpara(pi).getline(li);
	line.copyline(undo);
	isundo = true;
	p.getchapter(0).getsection(si).getpara(pi).addline();
	li++;
	r++;
	c = 0;
	auto& nline = p.getchapter(0).getsection(si).getpara(pi).getline(li);
	nline.settext(copy);
	gotoRowCol(r, 0);
	nline.print();
}
void undofunc(Document& p, int si, int pi, int li, int r, int& c, vector<char>& undo, bool& isundo, vector<char>& redo, bool& isredo)
{
	if (!isundo)
	{
		return;
	}
	auto& line = p.getchapter(0).getsection(si).getpara(pi).getline(li);
	line.copyline(redo);
	isredo = true;
	line.deleteline();
	line.settext(undo);
	isundo = false;
	gotoRowCol(r, 0);
	cout << "                                            ";
	gotoRowCol(r, 0);
	line.print();
	c = 0;
}
void redofunc(Document& p, int si, int pi, int li, int r, int& c, vector<char>& undo, bool& isundo, vector<char>& redo, bool& isredo)
{
	if (!isredo)
	{
		return;
	}
	auto& line = p.getchapter(0).getsection(si).getpara(pi).getline(li);
	line.copyline(undo);
	isundo = true;
	line.deleteline();
	line.settext(redo);
	isredo = false;
	gotoRowCol(r, 0);
	cout << "                                                                                                                                                                    ";
	gotoRowCol(r, 0);
	line.print();
	c = 0;
}
void savefile(Document& p,  const char* filename)
{
	ofstream fout(filename);
	if (!fout)
	{
		return;
	}
	for (int i = 0; i < p.getchapter(0).chaptersize(); i++)
	{
		for (int j = 0; j < p.getchapter(0).getsection(i).sectionsize(); j++)
		{
			for (int k = 0; k < p.getchapter(0).getsection(i).getpara(j).parasize(); k++)
			{
				auto& line = p.getchapter(0).getsection(i).getpara(j).getline(k);
				for (int a = 0; a < line.linelength(); a++)
				{
					fout << line.getchar(a);
				}
			}
		}
	}

	fout.close();

}
void printbox(int si, int pi, int li, int r, int& c, bool insert)
{
	color(10);
	gotoRowCol(0, 80);
	if (insert)
	{
		cout << "INSERT MODE";
	}
	else
	{
		cout << "NORMAL MODE";
	}
	cout << endl;
	gotoRowCol(0, 95);
	color(8);
	cout << "C :0" << " S :" << si + 1 << " P :" << pi + 1 << " L :" << li + 1 << " Col:" << c + 1;
	color(7);
	gotoRowCol(r, c);

}
void drawbox(int r, int c, int h, int w)
{
	char sym = -37;
	for (int i = 0; i < h; i++)
	{
		for (int z = 0; z < w; z++)
		{
			if (i == 0 || z == 0 || i == h - 1 || z == w - 1)
			{
				gotoRowCol(r + i, c + z);
				cout << sym;
			}
		}
	}
}
void displayCommandBox()
{
	int startR = 1;
	int startC = 100;
	int boxHeight = 22;
	int boxWidth = 40;

	color(11);
	drawbox(startR, startC, boxHeight, boxWidth);

	color(14);
	gotoRowCol(startR + 2, startC + 8);
	cout << "<<<<EDITOR KEYS>>>>";

	color(10);
	gotoRowCol(startR + 4, startC + 3);
	cout << "i : Insert Mode";

	gotoRowCol(startR + 5, startC + 3);
	cout << "Esc: Normal Mode";

	gotoRowCol(startR + 6, startC + 3);
	cout << "h,j,k,l : Navigation";

	color(15);
	gotoRowCol(startR + 8, startC + 3);
	cout << "Enter   : New Line";

	gotoRowCol(startR + 9, startC + 3);
	cout << "yy / p  : Copy / Paste Line";

	gotoRowCol(startR + 10, startC + 3);
	cout << "dd / x : Delete Line / Char";
	color(13);
	gotoRowCol(startR + 12, startC + 3);
	cout << "u /ctrl+ R : Undo / Redo";
	gotoRowCol(startR + 14, startC + 3);
	cout << "D : Delete To End";
	color(12);
	gotoRowCol(startR + 16, startC + 3);
	cout << "0 / $  Start / End Line";
	gotoRowCol(startR + 13, startC + 3);
	cout << "~ : Toggle Case";

	gotoRowCol(startR + 17, startC + 3);
	cout << "gg / G : First / Last Page";

	gotoRowCol(startR + 18, startC + 3);
	cout << ":w / :q : Save / Exit";

	color(7);
}
void SetConsoleSettings()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hWnd = GetConsoleWindow();

	if (hOut == INVALID_HANDLE_VALUE || hWnd == NULL) return;

	// 1. Set Font
	CONSOLE_FONT_INFOEX cfi = { sizeof(CONSOLE_FONT_INFOEX) };
	cfi.dwFontSize.Y = 18;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(hOut, FALSE, &cfi);

	// 2. Maximize the OS Window
	ShowWindow(hWnd, SW_MAXIMIZE);

	// 3. Get the MAXIMUM visible window size on this monitor
	COORD maxWindow = GetLargestConsoleWindowSize(hOut);

	// 4. Set Window Info first
	SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(maxWindow.X - 1), static_cast<SHORT>(maxWindow.Y - 1) };
	SetConsoleWindowInfo(hOut, TRUE, &windowSize);

	//Lock buffer EXACTLY to window size (Disables Scrollbars!)
	SetConsoleScreenBufferSize(hOut, maxWindow);

	// 6. Set Colors & Title
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	SetConsoleTitle(TEXT("Qasim's Text Editor"));
}
int Mystring::Length(const Mystring A)
{
	int i = 0;
	while (A.Cs[i] != '\0')
	{


		i++;
	}
	return i;



}
char Mystring::CharacterAt(int i)
{
	if (i > size)
	{
		return '\0';
	}
	return Cs[i];



}
bool forwardsearch(Document& p, int& si, int& pi, int& li, Mystring pattern, int& r, int& c)
{
	int l = pattern.Length(pattern);
	if (l == 0)
	{
		return false;
	}
	int ri = 0;
	for (int a = 0; a < p.getchapter(0).chaptersize(); a++)
	{
		for (int b = 0; b < p.getchapter(0).getsection(a).sectionsize(); b++)
		{
			for (int d = 0; d < p.getchapter(0).getsection(a).getpara(b).parasize();d++)
			{
				auto& line = p.getchapter(0).getsection(a).getpara(b).getline(d);
				for (int i = 0; i <= line.linelength()-l; i++)
				{
					bool match = true;
					for (int j = 0; j < l; j++)
					{
						if (line.getchar(i + j) != pattern.CharacterAt(j))
						{
							match = false;
							break;
						}
					}
					if (match)
					{
						c = i;
						r = ri;
						si = a;
						pi = b;
						li = d;
						color(5);
						gotoRowCol(ri, i);
						for (int k = 0; k < l; k++)
						{
							cout << pattern.CharacterAt(k);
						}
						color(7);
						gotoRowCol(r, c);
						return true;
					}

				}
				ri++;
			}
		}
	}


	gotoRowCol(r, c);
	return false;
}

int main()
{
	SetConsoleSettings();
 Document P;
	int c=0, r=0;
	int li = 0;
	int si = 0;
	int pi = 0;
	vector<char>copy;
	vector<char>undo;
	vector<char>redo;
	bool iscopy = false;
	bool isundo = false;
	bool isredo = false;
	bool isinsert = false;
	bool isselect = false;
	printbox( si, pi, li,r,c,  isinsert);
	displayCommandBox();
	color(12);
	printaline(0, 78, 24, 78, '|');
	printaline(24, 0, 24, 78,'|');
	while (true)
	{
		
		if (_kbhit())
		{
			int n = _getch();
			
			if (isinsert)
			{
				
				if (n == 27)
				{
					isinsert = false;
					gotoRowCol(r, c);
				}
				else if (n == 9)
				{
					for (int i = 0; i <4; i++)
					{
						P.getchapter(0).getsection(si).getpara(pi).getline(li).inserttext(c,' ');
					}
					c += 4;
					gotoRowCol(r, 0);
					P.getchapter(0).getsection(si).getpara(pi).getline(li).print();
					gotoRowCol(r, c);

				}

				 else if (n == 8)
				{
					if (c > 0)
					{
						c--;
						P.getchapter(0).getsection(si).getpara(pi).getline(li).removetext(c);
						gotoRowCol(r, 0);
						P.getchapter(0).getsection(si).getpara(pi).getline(li).print();
						cout << " ";
						gotoRowCol(r, c);
					}
				}
				else if (n == 13)
				{
					color(6);
					printaline(r + 1, 0, r + 1, 78, '-');
					r+=2;
					li++;
					if (li >= 2)
					{
						li = 0;
						pi++;
						if (pi >= 2)
						{
							P.getchapter(0).addnewChapter();
							r += 1;
							si++;
							pi = 0;
						}
						else
						{
							P.getchapter(0).getsection(si).addSection();
							r += 1;
						}

					}
					P.getchapter(0).getsection(si).getpara(pi).addline();
					c = 0;
					gotoRowCol(r, c);
				}

				
				else
				{
					char sym = n;
					P.getchapter(0).getsection(si).getpara(pi).getline(li).inserttext(c, sym);
					c++;
					gotoRowCol(r, 0);
					P.getchapter(0).getsection(si).getpara(pi).getline(li).print();
					gotoRowCol(r, c);
				}
			}
			else
			{
				if (n == 105)
				{
					isinsert = true;
					gotoRowCol(r, c);
				}
				else if (n == 58)
				{
					gotoRowCol(26, 0);
					cout << ":";
					char get[25];
					cin >> get;
					Mystring b(get);
					
					if (b.isEqual("w"))
					{
						savefile(P, "Documenttxt.txt");

					}
					else if (b.isEqual("q"))
					{
						return 0;
					}
					else if (b.isEqual("q!"))
					{
						return 0;
					}
					else if (b.isEqual("wq"))
					{

						savefile(P, "Documenttxt.txt");
						return 0;
					}
					else if (get[0] == '/')
					{
						Mystring find(get + 1);
						forwardsearch(P, si, pi, li, find, r, c);
					}
					
				}
				if (n == 104)
				{
					c--;
					gotoRowCol(r, c);
				}
				else if (n == 108)
				{
					c++;

					gotoRowCol(r, c);
				}
				else if (n == 119)
				{
					auto& line = P.getchapter(0).getsection(si).getpara(pi).getline(li);
					while (c < line.linelength() and line.getchar(c) != ' ')
					{
						c++;
					}
					while (c < line.linelength() and line.getchar(c) == ' ')
					{
						c++;
					}
					gotoRowCol(r, c);
				}
				else if (n == 98)
				{
					auto& line = P.getchapter(0).getsection(si).getpara(pi).getline(li);
					if (c > 0)
					{
						while (c > 0 and line.getchar(c) != ' ')
						{
							c--;
						}
						while (c > 0 and line.getchar(c) == ' ')
						{
							c--;
						}
					}
					gotoRowCol(r, c);
				}
				else if (n == 106)
				{
					r++;
					li++;
					int cl = P.getchapter(0).getsection(si).getpara(pi).parasize();
					if (li >= cl)
					{
						if (pi + 1 < P.getchapter(0).getsection(si).sectionsize())
						{
							pi++;
							li = 0;
						}
						else if (si + 1 < P.getchapter(0).chaptersize())
						{
							si++;
							pi = 0;
							li = 0;
						}
						else
						{
							if (cl > 0)
							{
								li = cl - 1;
							}
							else
							{
								li = 0;
							}
						}
					}

					gotoRowCol(r, c);
				}
				else if (n == 67)
				{
					copied(P, si, pi, li, copy, iscopy);
					gotoRowCol(r, c);
				}
				
				
				else if (n == 121)
				{
					int nk = _getch();
					if (nk == 121)
					{
						copied(P, si, pi, li, copy, iscopy);
						gotoRowCol(r, c);
					}
				}
				else if (n == 112)
				{
					pasted(P, si, pi, li, r, c, copy, iscopy, undo, isundo);
					gotoRowCol(r, c);
				}
				else if (n == 117)
				{
					undofunc(P, si, pi, li, r, c, undo, isundo, redo, isredo);
					gotoRowCol(r, c);
				}
				else if (n == 18)
				{
					redofunc(P, si, pi, li, r, c, undo, isundo, redo, isredo);
					gotoRowCol(r, c);
				}
				else if (n == 48)
				{
					c = 0;
					gotoRowCol(r, c);
				}
				else if (n == 36)
				{
					c = P.getchapter(0).getsection(si).getpara(pi).getline(li).linelength();
					gotoRowCol(r, c);
				}
				else if (n == 103)
				{
					int newkey = _getch();
					if (newkey == 103)
					{
						pi = 0;
						li = 0;
						si = 0;

						c = 0;
						r = 0;
						gotoRowCol(r, c);
					}
				}
				else if (n == 71)
				{

					li = P.getchapter(0).getsection(si).getpara(pi).parasize() - 1;
					pi = P.getchapter(0).getsection(si).sectionsize() - 1;
					si = P.getchapter(0).chaptersize() - 1;
					c = P.getchapter(0).getsection(si).getpara(pi).getline(li).linelength();
					r = li;
					gotoRowCol(r, c);
				}
				else if (n == 120)
				{
					auto& line = P.getchapter(0).getsection(si).getpara(pi).getline(li);
					if (c < line.linelength())
					{
						line.removetext(c);
						gotoRowCol(r, 0);
						cout << "                                                               ";
						gotoRowCol(r, 0);
						line.print();
						gotoRowCol(r, c);

					}
				}
				else if (n == 100)
				{
					int key = _getch();
					if (key == 100)
					{
						auto& line = P.getchapter(0).getsection(si).getpara(pi).getline(li);
						line.copyline(undo);
						isundo = true;
						isredo = false;
						line.deleteline();
						c = 0;
						gotoRowCol(r, 0);
						cout << "                                                                                                                                                                                        ";
						gotoRowCol(r, c);


					}
				}
				else if (n == 126)
				{
					auto& line = P.getchapter(0).getsection(si).getpara(pi).getline(li);
					toggle(line, r,c);
					}
				else if (n == 68)
				{
					auto& line = P.getchapter(0).getsection(si).getpara(pi).getline(li);
					deletetoend(line, r,c);
					}
				else if (n == 107)
				{
					if (r > 0)

					{
						r--;

						if (li > 0)
						{
							li--;

						}
						else if (pi > 0)
						{
							pi--;
							int tl = P.getchapter(0).getsection(si).getpara(pi).parasize();
							if (tl > 0)
							{
								li = tl - 1;
							}
							else
							{
								li = 0;
							}
						}
						else if (si > 0)
						{
							si--;
							pi = P.getchapter(0).getsection(si).sectionsize() - 1;
							int tl = P.getchapter(0).getsection(si).getpara(pi).parasize();
							if (tl > 0)
							{
								li = tl - 1;
							}
							else
							{
								li = 0;
							}
						}

						int l = P.getchapter(0).getsection(si).getpara(pi).parasize();
						if (c > l)
						{
							c = l;
						}
					}
					gotoRowCol(r, c);
				}
			}
		
			printbox(si, pi, li, r, c, isinsert);
		}
		
	}




	return 0;
}