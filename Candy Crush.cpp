#include<iostream>
#include"SFML/Graphics.hpp"
#include<iomanip>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<fstream>

using namespace std;
using namespace sf;

void Resume(int arr[][9], int size, int& GainedPoints, int& TargetPoints, int& Moves)
{
	ifstream fin;
	fin.open("CandyCrush.txt");
	if (fin.is_open())
	{
		fin >> Moves;
		fin >> GainedPoints;
		fin >> TargetPoints;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				fin >> arr[i][j];
			}
		}
		fin.close();
	}
	else
	{
		cout << "[Error] Game not loaded\n";
		exit(1);
	}
}
void Save(int arr[][9], int size, int GainedPoints, int TargetPoints, int Moves)
{
	cout << "**********Game Saved*************\n";
	ofstream fout;
	fout.open("CandyCrush.txt", ios::out);
	if (fout.is_open())
	{
		fout << Moves << endl;
		fout << GainedPoints << endl;
		fout << TargetPoints << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (j < size - 1)
					fout << arr[i][j] << " ";
				else
					fout << arr[i][j];
			}
			if (i < size - 1)
				fout << endl;
		}
		fout.close();
	}
	else
	{
		cout << "Game not Saved\n";
		exit(1);
	}
}
void New(int arr[][9], int size, int& GainedPoints, int& TargetPoints, int& Moves)
{
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
		up: arr[i][j] = rand() % 5 + 1;
			for (int n = j - 2; n < j; n++)
			{
				if (arr[i][j] == arr[i][n])
				{
					arr[i][j] = 0;
					goto up;
				}

			}
			if (arr[i][j] == arr[i - 1][j])
			{
				arr[i][j] = 0;
				goto up;
			}
		}
	}

	GainedPoints = 0;
	TargetPoints = 1000;
	Moves = 20;
}
void Print(int arr[][9], int size, int GainedPoints, int TargetPoints, int Moves)
{
	cout << "  **************** Candy Crush ****************\n\n";
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << setw(5) << arr[i][j];
		}
		cout << endl << endl;
	}
	cout << "Remaining Moves : " << Moves << endl;
	cout << "Gained Point : " << GainedPoints << endl;
	cout << "Targeted Point : " << TargetPoints << endl;
}
void Menu(int arr[][9], int size, int& GainedPoints, int& TargetPoints, int& Moves)
{
	cout << "******** MENU ********\n";
	cout << "1. RESUME\n";
	cout << "2. NEW\n";
	cout << "3. Exit\n";
	int input = 0;
	cin >> input;
	system("CLS");
	if (input == 1)
	{
		Resume(arr, size, GainedPoints, TargetPoints, Moves);
	}
	else if (input == 2)
	{
		New(arr, size, GainedPoints, TargetPoints, Moves);
	}
	else if (input == 3)
	{
		exit(1);
	}
}
void ZeroCover(int arr[][9], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (arr[i][j] == 0)
			{
				if (i > 0)
				{
					for (int k = i - 1, l = i; k >= 0; k--, l--)
					{
						arr[l][j] = arr[k][j];
					}
					arr[0][j] = rand() % (6 - 1) + 1;
				}
				else if (i == 0)
				{
					arr[0][j] = rand() % (6 - 1) + 1;
				}
			}
		}
	}
}
void PrintGraphics(RenderWindow& window, int arr[][9], int size, int GainedPoints, int TargetPoints, int Moves)
{
	// Text 
	Font font;
	if (!font.loadFromFile("Additional Files/bold.ttf"))
	{
		cout << "[Error] Font File Not Loaded\n";
		exit(1);
	}
	Text G_points, T_points, Move;
	G_points.setFont(font); T_points.setFont(font); Move.setFont(font);
	G_points.setCharacterSize(18); T_points.setCharacterSize(18); Move.setCharacterSize(18);
	G_points.setFillColor(Color::Blue); T_points.setFillColor(Color::Red); Move.setFillColor(Color::Green);
	G_points.setPosition({ 20.0f,455.0f }); T_points.setPosition({ 220.0f,455.0f }); Move.setPosition({ 170.0f,480.0f });
	G_points.setString("Gained Points : " + to_string(GainedPoints));
	T_points.setString("Targeted Points : " + to_string(TargetPoints));
	Move.setString("Moves : " + to_string(Moves));

	// Buttons Save & Main Menu

	Font font2;
	//SAVE
	RectangleShape Save;
	Save.setFillColor(Color::White);
	Save.setOutlineColor(Color::Cyan);
	Save.setOutlineThickness(2);
	Save.setSize({ 40.0f,30.0f });
	Save.setPosition({ 20.0f,510.0f });
	// Text 
	Text b_Save, t_Save;
	b_Save.setString("S"); t_Save.setString("- SAVE");
	b_Save.setCharacterSize(20); t_Save.setCharacterSize(20);
	b_Save.setFillColor(Color::Black); t_Save.setFillColor(Color::White);
	if (!font2.loadFromFile("Additional Files/Calibri.ttf"))
	{
		cout << "[Error] Font File Not Loaded\n";
		exit(1);
	}
	b_Save.setFont(font2); t_Save.setFont(font2);
	//b_Save.setStyle(Text::Bold); t_Save.setStyle(Text::Bold);

	// Center text on button:
	float xPos = float((20.0f + 40.0f / 2.0f) - (b_Save.getLocalBounds().width / 2));
	float yPos = float((510.0f + 30.0f / 3.0f) - (b_Save.getLocalBounds().height / 2));
	b_Save.setPosition(xPos, yPos); t_Save.setPosition(xPos + 30, yPos);

	// MAIN MENU
	RectangleShape Esc;
	Esc.setFillColor(Color::White);
	Esc.setOutlineColor(Color::Cyan);
	Esc.setOutlineThickness(2);
	Esc.setSize({ 40.0f,30.0f });
	Esc.setPosition({ 150.0f,510.0f });
	// Text 
	Text b_Esc, t_Esc;
	b_Esc.setString("Esc"); t_Esc.setString("- BACK");
	b_Esc.setCharacterSize(20); t_Esc.setCharacterSize(20);
	b_Esc.setFillColor(Color::Black); t_Esc.setFillColor(Color::White);
	b_Esc.setFont(font2); t_Esc.setFont(font2);
	//b_Esc.setStyle(Text::Bold); t_Esc.setStyle(Text::Bold);

	// Center text on button:
	xPos = float((150.0f + 40.0f / 2.0f) - (b_Esc.getLocalBounds().width / 2));
	yPos = float((510.0f + 30.0f / 3.0f) - (b_Esc.getLocalBounds().height / 2));
	b_Esc.setPosition(xPos, yPos); t_Esc.setPosition(xPos + 40, yPos);


	// Candies
	float x_axis = 0.0f, y_axis = 0.0f;
	Sprite sp_arr[9][9];
	Texture txt_arr[9][9];

	for (int i = 0; i < size; i++, x_axis = 0.0f, y_axis += 50.0f)
	{
		for (int j = 0; j < size; j++, x_axis += 50.0f)
		{
			if (arr[i][j] == 0)
			{
				txt_arr[i][j].loadFromFile("Additional Files/Blast.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);
			}
			if (arr[i][j] == 1)
			{
				txt_arr[i][j].loadFromFile("Additional Files/Red.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);
			}
			else if (arr[i][j] == 2)
			{
				txt_arr[i][j].loadFromFile("Additional Files/Green.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);

			}
			else if (arr[i][j] == 3)
			{

				txt_arr[i][j].loadFromFile("Additional Files/Blue.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);
			}
			else if (arr[i][j] == 4)
			{
				txt_arr[i][j].loadFromFile("Additional Files/Yellow.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);

			}
			else if (arr[i][j] == 5)
			{
				txt_arr[i][j].loadFromFile("Additional Files/Orange.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);

			}
			else if (arr[i][j] == 6)
			{
				txt_arr[i][j].loadFromFile("Additional Files/RedStripe.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);

			}
			else if (arr[i][j] == 7)
			{
				txt_arr[i][j].loadFromFile("Additional Files/GreenStripe.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);

			}
			else if (arr[i][j] == 8)
			{
				txt_arr[i][j].loadFromFile("Additional Files/BlueStripe.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);

			}
			else if (arr[i][j] == 9)
			{
				txt_arr[i][j].loadFromFile("Additional Files/YellowStripe.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);

			}
			else if (arr[i][j] == 10)
			{
				txt_arr[i][j].loadFromFile("Additional Files/OrangeStripe.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);

			}
			else if (arr[i][j] == 11)
			{
				txt_arr[i][j].loadFromFile("Additional Files/RedWrap.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);

			}
			else if (arr[i][j] == 12)
			{

				txt_arr[i][j].loadFromFile("Additional Files/GreenWrap.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);
			}
			else if (arr[i][j] == 13)
			{
				txt_arr[i][j].loadFromFile("Additional Files/BlueWrap.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);

			}
			else if (arr[i][j] == 14)
			{
				txt_arr[i][j].loadFromFile("Additional Files/YellowWrap.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);

			}
			else if (arr[i][j] == 15)
			{
				txt_arr[i][j].loadFromFile("Additional Files/OrangeWrap.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);

			}
			else if (arr[i][j] == 16)
			{

				txt_arr[i][j].loadFromFile("Additional Files/ColorBomb.png");
				sp_arr[i][j].setTexture(txt_arr[i][j]);
			}

			sp_arr[i][j].setPosition({ x_axis,y_axis });
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			window.draw(sp_arr[i][j]);
		}
	}

	window.draw(G_points);
	window.draw(T_points);
	window.draw(Move);
	window.draw(Save);
	window.draw(b_Save);
	window.draw(t_Save);
	window.draw(Esc);
	window.draw(b_Esc);
	window.draw(t_Esc);
}

//*********************************** FUNCTIONS ********************************************//
void funStripe(int arr[][9], int size, int i, int j, string direction)
{
	if (direction == "vertical")
	{
		for (int row = 0; row < size; row++)
		{
			arr[row++][j] = 0;
		}
	}	
	else if (direction == "horizontal")
	{
		for (int col = 0; col < size; col++)
		{
			arr[i][col++] = 0;
		}
	}
}

bool funA(int arr[][9], int size, Vector2i IndexArr[], int Isize, int Itype, int t1, int t2, int t3, int t4, int t5)
{
	// For CB & TL _Crusher
	if (Itype == 5)
	{
		if ((t1 == 1) || (t1 == 6) || (t1 == 11))
		{
			if ((t2 == 1) || (t2 == 6) || (t2 == 11))
			{
				if ((t3 == 1) || (t3 == 6) || (t3 == 11))
				{
					if ((t4 == 1) || (t4 == 6) || (t4 == 11))
					{
						if ((t5 == 1) || (t5 == 6) || (t5 == 11))
						{
							return true;
						}
					}
				}
			}
		}
		else if ((t1 == 2) || (t1 == 7) || (t1 == 12))
		{
			if ((t2 == 2) || (t2 == 7) || (t2 == 12))
			{
				if ((t3 == 2) || (t3 == 7) || (t3 == 12))
				{
					if ((t4 == 2) || (t4 == 7) || (t4 == 12))
					{
						if ((t5 == 2) || (t5 == 7) || (t5 == 12))
						{
							return true;
						}
					}
				}
			}
		}
		else if ((t1 == 3) || (t1 == 8) || (t1 == 13))
		{
			if ((t2 == 3) || (t2 == 8) || (t2 == 13))
			{
				if ((t3 == 3) || (t3 == 8) || (t3 == 13))
				{
					if ((t4 == 3) || (t4 == 8) || (t4 == 13))
					{
						if ((t5 == 3) || (t5 == 8) || (t5 == 13))
						{
							return true;
						}
					}
				}
			}
		}
		else if ((t1 == 4) || (t1 == 9) || (t1 == 14))
		{
			if ((t2 == 4) || (t2 == 9) || (t2 == 14))
			{
				if ((t3 == 4) || (t3 == 9) || (t3 == 14))
				{
					if ((t4 == 4) || (t4 == 9) || (t4 == 14))
					{
						if ((t5 == 4) || (t5 == 9) || (t5 == 14))
						{
							return true;
						}
					}
				}
			}
		}
		else if ((t1 == 5) || (t1 == 10) || (t1 == 15))
		{
			if ((t2 == 5) || (t2 == 10) || (t2 == 15))
			{
				if ((t3 == 5) || (t3 == 10) || (t3 == 15))
				{
					if ((t4 == 5) || (t4 == 10) || (t4 == 15))
					{
						if ((t5 == 5) || (t5 == 10) || (t5 == 15))
						{
							return true;
						}
					}
				}
			}
		}
	}
	// For Stripes _Crusher
	else if (Itype == 4)
	{
		if ((t1 == 1) || (t1 == 6) || (t1 == 11))
		{
			if ((t2 == 1) || (t2 == 6) || (t2 == 11))
			{
				if ((t3 == 1) || (t3 == 6) || (t3 == 11))
				{
					if ((t4 == 1) || (t4 == 6) || (t4 == 11))
					{
						return true;
					}
				}
			}
		}
		else if ((t1 == 2) || (t1 == 7) || (t1 == 12))
		{
			if ((t2 == 2) || (t2 == 7) || (t2 == 12))
			{
				if ((t3 == 2) || (t3 == 7) || (t3 == 12))
				{
					if ((t4 == 2) || (t4 == 7) || (t4 == 12))
					{
						return true;
					}
				}
			}
		}
		else if ((t1 == 3) || (t1 == 8) || (t1 == 13))
		{
			if ((t2 == 3) || (t2 == 8) || (t2 == 13))
			{
				if ((t3 == 3) || (t3 == 8) || (t3 == 13))
				{
					if ((t4 == 3) || (t4 == 8) || (t4 == 13))
					{
						return true;
					}
				}
			}
		}
		else if ((t1 == 4) || (t1 == 9) || (t1 == 14))
		{
			if ((t2 == 4) || (t2 == 9) || (t2 == 14))
			{
				if ((t3 == 4) || (t3 == 9) || (t3 == 14))
				{
					if ((t4 == 4) || (t4 == 9) || (t4 == 14))
					{
						return true;
					}
				}
			}
		}
		else if ((t1 == 5) || (t1 == 10) || (t1 == 15))
		{
			if ((t2 == 5) || (t2 == 10) || (t2 == 15))
			{
				if ((t3 == 5) || (t3 == 10) || (t3 == 15))
				{
					if ((t4 == 5) || (t4 == 10) || (t4 == 15))
					{
						return true;
					}
				}
			}
		}
	}
	// For 3_Crusher
	else if (Itype == 3)
	{
	if ((t1 == 1) || (t1 == 6) || (t1 == 11))
	{
		if ((t2 == 1) || (t2 == 6) || (t2 == 11))
		{
			if ((t3 == 1) || (t3 == 6) || (t3 == 11))
			{
				if (t1 == 6)
				{
					funStripe(arr, size, IndexArr[0].x, IndexArr[0].y, "vertical");
				}
				else if (t2 == 6)
				{
					funStripe(arr, size, IndexArr[1].x, IndexArr[1].y, "vertical");
				}
				else if (t3 == 6)
				{
					funStripe(arr, size, IndexArr[2].x, IndexArr[2].y, "vertical");
				}
				return true;
			}
		}
	}
	else if ((t1 == 2) || (t1 == 7) || (t1 == 12))
	{
		if ((t2 == 2) || (t2 == 7) || (t2 == 12))
		{
			if ((t3 == 2) || (t3 == 7) || (t3 == 12))
			{
				if (t1 == 7)
				{
					funStripe(arr, size, IndexArr[0].x, IndexArr[0].y, "vertical");
				}
				else if (t2 == 7)
				{
					funStripe(arr, size, IndexArr[1].x, IndexArr[1].y, "vertical");
				}
				else if (t3 == 7)
				{
					funStripe(arr, size, IndexArr[2].x, IndexArr[2].y, "vertical");
				}
				return true;
			}
		}
	}
	else if ((t1 == 3) || (t1 == 8) || (t1 == 13))
	{
		if ((t2 == 3) || (t2 == 8) || (t2 == 13))
		{
			if ((t3 == 3) || (t3 == 8) || (t3 == 13))
			{
				if (t1 == 8)
				{
					funStripe(arr, size, IndexArr[0].x, IndexArr[0].y, "horizontal");
				}
				else if (t2 == 8)
				{
					funStripe(arr, size, IndexArr[1].x, IndexArr[1].y, "horizontal");
				}
				else if (t3 == 8)
				{
					funStripe(arr, size, IndexArr[2].x, IndexArr[2].y, "horizontal");
				}
				return true;
			}
		}
	}
	else if ((t1 == 4) || (t1 == 9) || (t1 == 14))
	{
		if ((t2 == 4) || (t2 == 9) || (t2 == 14))
		{
			if ((t3 == 4) || (t3 == 9) || (t3 == 14))
			{
				if (t1 == 9)
				{
					funStripe(arr, size, IndexArr[0].x, IndexArr[0].y, "horizontal");
				}
				else if (t2 == 9)
				{
					funStripe(arr, size, IndexArr[1].x, IndexArr[1].y, "horizontal");
				}
				else if (t3 == 9)
				{
					funStripe(arr, size, IndexArr[2].x, IndexArr[2].y, "horizontal");
				}
				return true;
			}
		}
	}
	else if ((t1 == 5) || (t1 == 10) || (t1 == 15))
	{
		if ((t2 == 5) || (t2 == 10) || (t2 == 15))
		{
			if ((t3 == 5) || (t3 == 10) || (t3 == 15))
			{
				if (t1 == 10)
				{
					funStripe(arr, size, IndexArr[0].x, IndexArr[0].y, "horizontal");
				}
				else if (t2 == 10)
				{
					funStripe(arr, size, IndexArr[1].x, IndexArr[1].y, "horizontal");
				}
				else if (t3 == 10)
				{
					funStripe(arr, size, IndexArr[2].x, IndexArr[2].y, "horizontal");
				}
				return true;
			}
		}
	}
	}

	return false;
}


bool CB_Crusher(int arr[][9], int size, int i, int j, Vector2i current_Index)
{
	cout << "i >> " << i << endl;
	cout << "j >> " << j << endl;
	int Itype = 5;
	const int Isize = 5;
	Vector2i IndexArr[Isize];
	if (j < size - 4)
	{
		int t1, t2, t3, t4, t5;
		t1 = arr[i][j];
		t2 = arr[i][j + 1];
		t3 = arr[i][j + 2];
		t4 = arr[i][j + 3];
		t5 = arr[i][j + 4];

		IndexArr[0] = { i,j };
		IndexArr[1] = { i,j + 1 };
		IndexArr[2] = { i,j + 2 };
		IndexArr[3] = { i,j + 3 };
		IndexArr[4] = { i,j+4 };
		
		if ((t1 == t2) && (t1 == t3) && (t1 == t4) && (t1 == t5))
		{
			cout << "CB_Crusher called ( ------ )\n";
			arr[i][j] = 0;
			arr[i][j + 1] = 0;
			arr[i][j + 2] = 0;
			arr[i][j + 3] = 0;
			arr[i][j + 4] = 0;
			arr[i][j + 2] = 16;
			return true;
		}
	}
	if (i < size - 4)
	{
		int t1, t2, t3, t4, t5;
		t1 = arr[i][j];
		t2 = arr[i + 1][j];
		t3 = arr[i + 2][j];
		t4 = arr[i + 3][j];
		t5 = arr[i + 4][j];

		IndexArr[0] = { i,j };
		IndexArr[1] = { i + 1,j };
		IndexArr[2] = { i + 2,j };
		IndexArr[3] = { i + 3,j };
		IndexArr[4] = { i + 4,j };

		if ((t1 == t2) && (t1 == t3) && (t1 == t4) && (t1 == t5))
		{
			cout << "CB_Crusher called  ( | )\n";
			arr[i][j] = 0;
			arr[i + 1][j] = 0;
			arr[i + 2][j] = 0;
			arr[i + 3][j] = 0;
			arr[i + 4][j] = 0;
			arr[i][j] = 16;
			return true;
		}
	}
	return false;
}
bool ST_Crusher(int arr[][9], int size, int i, int j, Vector2i current_Index)
{
	cout << "i >> " << i << endl;
	cout << "j >> " << j << endl;
	if (j < size - 3)
	{
		int t1, t2, t3, t4;
		t1 = arr[i][j];
		t2 = arr[i][j + 1];
		t3 = arr[i][j + 2];
		t4 = arr[i][j + 3];

		if ((t1 == t2) && (t1 == t3) && (t1 == t4))
		{
			cout << "ST_Crusher called  ( ---- )\n";
			arr[i][j] = 0;
			arr[i][j + 1] = 0;
			arr[i][j + 2] = 0;
			arr[i][j + 3] = 0;
			switch (t1)
			{
			case 1:// Red
				arr[i][j] = 6;
				break;
			case 2:// Green
				arr[i][j] = 7;
				break;
			case 3:// Blue
				arr[i][j] = 8;
				break;
			case 4:// Yellow
				arr[i][j] = 9;
				break;
			case 5:// Orange
				arr[i][j] = 10;
				break;
			default:
				break;
			}
			return true;
		}
	}
	if (i < size - 3)
	{
		int t1, t2, t3, t4;
		t1 = arr[i][j];
		t2 = arr[i + 1][j];
		t3 = arr[i + 2][j];
		t4 = arr[i + 3][j];
		if ((t1 == t2) && (t1 == t3) && (t1 == t4))
		{
			cout << "ST_Crusher called  ( | ) \n";
			arr[i][j] = 0;
			arr[i + 1][j] = 0;
			arr[i + 2][j] = 0;
			arr[i + 3][j] = 0;
			switch (t1)
			{
			case 1:// Red
				arr[i][j] = 6;
				break;
			case 2:// Green
				arr[i][j] = 7;
				break;
			case 3:// Blue
				arr[i][j] = 8;
				break;
			case 4:// Yellow
				arr[i][j] = 9;
				break;
			case 5:// Orange
				arr[i][j] = 10;
				break;
			default:
				break;
			}
			return true;
		}
	}

	return false;
}
bool TL_Crusher(int arr[][9], int size, int i, int j, Vector2i current_Index)
{
	cout << "i >> " << i << endl;
	cout << "j >> " << j << endl;
	cout << "TL_Crusher called\n";

	bool flag = false;

	int t1 = arr[i][j];
	int t2 = arr[i][j + 1];
	int t3 = arr[i][j + 2];
	int t4 = arr[i + 1][j];
	int t5 = arr[i + 2][j];

	int Upa1 = 0, Upa2 = 0;
	int Da1 = 0, Da2 = 0;

	int Upb1 = 0, Upb2 = 0;
	int Db1 = 0, Db2 = 0;

	int Upc1 = 0, Upc2 = 0;
	int Dc1 = 0, Dc2 = 0;

	int Ra1 = 0, Ra2 = 0;
	int La1 = 0, La2 = 0;

	int Rb1 = 0, Rb2 = 0;
	int Lb1 = 0, Lb2 = 0;

	int Rc1 = 0, Rc2 = 0;
	int Lc1 = 0, Lc2 = 0;

	// To be Continued
	if (i + 2 < size)
	{
		// Down
		cout << "up\n";
		Da1 = arr[i + 1][j], Da2 = arr[i + 2][j];
		Db1 = arr[i + 1][j + 1], Db2 = arr[i + 2][j + 1];
		Dc1 = arr[i + 1][j + 2], Dc2 = arr[i + 2][j + 2];
	}
	if (i - 2 >= 0)
	{
		// Up
		cout << "down\n";
		Upa1 = arr[i - 1][j], Upa2 = arr[i - 2][j];
		Upb1 = arr[i - 1][j + 1], Upb2 = arr[i - 2][j + 1];
		Upc1 = arr[i - 1][j + 2], Upc2 = arr[i - 2][j + 2];
	}
	if (j + 2 < size)
	{
		// Right
		cout << "right\n";
		Ra1 = arr[i][j + 1], Ra2 = arr[i][j + 2];
		Rb1 = arr[i + 1][j + 1], Rb2 = arr[i + 1][j + 2];
		Rc1 = arr[i + 2][j + 1], Rc2 = arr[i + 2][j + 2];
	}
	if (j - 2 >= 0)
	{
		// Left
		cout << "left\n";
		La1 = arr[i][j - 1], La2 = arr[i][j - 2];
		Lb1 = arr[i + 1][j - 1], Lb2 = arr[i + 1][j - 2];
		Lc1 = arr[i + 2][j - 1], Lc2 = arr[i + 2][j - 2];
	}


	if ((t1 == Upa1) && (t1 == Upa2) && (t1 == t2) && (t1 == t3))// L up
	{
		cout << "L up called\n";
		arr[i][j] = 0;
		arr[i][j + 1] = 0;
		arr[i][j + 2] = 0;
		arr[i - 1][j] = 0;
		arr[i - 2][j] = 0;

		flag = true;
	}
	else if ((t1 == Da1) && (t1 == Da2) && (t1 == t2) && (t1 == t3))// L Down
	{
		cout << "L Down called\n";
		arr[i][j] = 0;
		arr[i][j + 1] = 0;
		arr[i][j + 2] = 0;
		arr[i + 1][j] = 0;
		arr[i + 2][j] = 0;

		flag = true;
	}
	else if ((t1 == Upb1) && (t1 == Upb2) && (t1 == t2) && (t1 == t3))// T Up
	{
		cout << "T up called\n";
		arr[i][j] = 0;
		arr[i][j + 1] = 0;
		arr[i][j + 2] = 0;
		arr[i - 1][j + 1] = 0;
		arr[i - 2][j + 1] = 0;

		flag = true;
	}
	else if ((t1 == Db1) && (t1 == Db2) && (t1 == t2) && (t1 == t3))// T Down
	{
		cout << "T up called\n";
		arr[i][j] = 0;
		arr[i][j + 1] = 0;
		arr[i][j + 2] = 0;
		arr[i + 1][j + 1] = 0;
		arr[i + 2][j + 1] = 0;

		flag = true;
	}
	else if ((t1 == Upc1) && (t1 == Upc2) && (t1 == t2) && (t1 == t3))// L Up R
	{
		cout << "L up called R\n";
		arr[i][j] = 0;
		arr[i][j + 1] = 0;
		arr[i][j + 2] = 0;
		arr[i - 1][j + 2] = 0;
		arr[i - 2][j + 2] = 0;

		flag = true;
	}
	else if ((t1 == Dc1) && (t1 == Dc2) && (t1 == t2) && (t1 == t3))// L Down R
	{
		cout << "L Down called R\n";
		arr[i][j] = 0;
		arr[i][j + 1] = 0;
		arr[i][j + 2] = 0;
		arr[i + 1][j + 2] = 0;
		arr[i + 2][j + 2] = 0;

		flag = true;
	}
	else if ((t1 == Ra1) && (t1 == Ra2) && (t1 == t4) && (t1 == t5))
	{
		cout << "L called Right\n";
		arr[i][j] = 0;
		arr[i][j + 1] = 0;
		arr[i][j + 2] = 0;
		arr[i + 1][j] = 0;
		arr[i + 2][j] = 0;
		flag = true;
	}
	else if ((t1 == La1) && (t1 == La2) && (t1 == t4) && (t1 == t5))
	{
		cout << "L called left\n";
		arr[i][j] = 0;
		arr[i][j - 1] = 0;
		arr[i][j - 2] = 0;
		arr[i + 1][j] = 0;
		arr[i + 2][j] = 0;
		flag = true;
	}
	else if ((t1 == Rb1) && (t1 == Rb2) && (t1 == t4) && (t1 == t5))
	{
		cout << "T called Right\n";
		arr[i][j] = 0;
		arr[i + 1][j + 1] = 0;
		arr[i + 1][j + 2] = 0;
		arr[i + 1][j] = 0;
		arr[i + 2][j] = 0;
		flag = true;
	}
	else if ((t1 == Lb1) && (t1 == Lb2) && (t1 == t4) && (t1 == t5))
	{
		cout << "T called left\n";
		arr[i][j] = 0;
		arr[i + 1][j - 1] = 0;
		arr[i + 1][j - 2] = 0;
		arr[i + 1][j] = 0;
		arr[i + 2][j] = 0;
		flag = true;
	}
	else if ((t1 == Rc1) && (t1 == Rc2) && (t1 == t4) && (t1 == t5))
	{
		cout << "L called bottom Right\n";
		arr[i][j] = 0;
		arr[i + 2][j + 1] = 0;
		arr[i + 2][j + 2] = 0;
		arr[i + 1][j] = 0;
		arr[i + 2][j] = 0;
		flag = true;
	}
	else if ((t1 == Lc1) && (t1 == Lc2) && (t1 == t4) && (t1 == t5))
	{
		cout << "T called bottom left\n";
		arr[i][j] = 0;
		arr[i + 2][j - 1] = 0;
		arr[i + 2][j - 2] = 0;
		arr[i + 1][j] = 0;
		arr[i + 2][j] = 0;
		flag = true;
	}




	if (flag == true)
	{
		switch (t1)
		{
		case 1:// Red
			arr[i][j] = 11;
			break;
		case 2:// Green
			arr[i][j] = 12;
			break;
		case 3:// Blue
			arr[i][j] = 13;
			break;
		case 4:// Yellow
			arr[i][j] = 14;
			break;
		case 5:// Orange
			arr[i][j] = 15;
			break;
		default:
			break;
		}

	}
	else
	{
		return false;
	}
}

void Checker(RenderWindow& window, int arr[][9], int size, Vector2i& previous_Index, Vector2i& current_Index, int& GainedPoints, int& TargetPoints, int& Moves)
{

	bool flag = false; int point = 0;
back:
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int t1 = -1, t2 = -1, t3 = -1;
			int t4 = -1, t5 = -1;
			t1 = arr[i][j];
			if (t1 == 1)//red
			{
				point = 30;
			}
			else if (t1 == 2)//green
			{
				point = 40;
			}
			else if (t1 == 3)//blue
			{
				point = 50;
			}
			else if (t1 == 4)//yellow
			{
				point = 30;
			}
			else if (t1 == 5)//orange
			{
				point = 60;
			}
			if (t1 == 16)
			{
				t1 = 2;
			}
			if (j < size - 2)
			{
				cout << "j **** in\n";
				t2 = arr[i][j + 1];
				t3 = arr[i][j + 2];
			}
			if (i < size - 2)
			{
				cout << "i *** in \n";
				t4 = arr[i + 1][j];
				t5 = arr[i + 2][j];
			}
			bool horizontal = false, vertical = false;
			if ((t1 == 1) || (t1 == 6) || (t1 == 11))
			{
				if ((t2 == 1) || (t2 == 6) || (t2 == 11))
				{
					if ((t3 == 1) || (t3 == 6) || (t3 == 11))
					{
						horizontal = true;
					}
				}
			}
			else if ((t1 == 2) || (t1 == 7) || (t1 == 12))
			{
				if ((t2 == 2) || (t2 == 7) || (t2 == 12))
				{
					if ((t3 == 2) || (t3 == 7) || (t3 == 12))
					{
						horizontal = true;
					}
				}
			}
			else if ((t1 == 3) || (t1 == 8) || (t1 == 13))
			{
				if ((t2 == 3) || (t2 == 8) || (t2 == 13))
				{
					if ((t3 == 3) || (t3 == 8) || (t3 == 13))
					{
						horizontal = true;
					}
				}
			}
			else if ((t1 == 4) || (t1 == 9) || (t1 == 14))
			{
				if ((t2 == 4) || (t2 == 9) || (t2 == 14))
				{
					if ((t3 == 4) || (t3 == 9) || (t3 == 14))
					{
						horizontal = true;
					}
				}
			}
			else if ((t1 == 5) || (t1 == 10) || (t1 == 15))
			{
				if ((t2 == 5) || (t2 == 10) || (t2 == 15))
				{
					if ((t3 == 5) || (t3 == 10) || (t3 == 15))
					{
						horizontal = true;
					}
				}
			}

			if ((t1 == 1) || (t1 == 6) || (t1 == 11))
			{
				if ((t4 == 1) || (t4 == 6) || (t4 == 11))
				{
					if ((t5 == 1) || (t5 == 6) || (t5 == 11))
					{
						vertical = true;
					}
				}
			}
			else if ((t1 == 2) || (t1 == 7) || (t1 == 12))
			{
				if ((t4 == 2) || (t4 == 7) || (t4 == 12))
				{
					if ((t5 == 2) || (t5 == 7) || (t5 == 12))
					{
						vertical = true;
					}
				}
			}
			else if ((t1 == 3) || (t1 == 8) || (t1 == 13))
			{
				if ((t4 == 3) || (t4 == 8) || (t4 == 13))
				{
					if ((t5 == 3) || (t5 == 8) || (t5 == 13))
					{
						vertical = true;
					}
				}
			}
			else if ((t1 == 4) || (t1 == 9) || (t1 == 14))
			{
				if ((t4 == 4) || (t4 == 9) || (t4 == 14))
				{
					if ((t5 == 4) || (t5 == 9) || (t5 == 14))
					{
						vertical = true;
					}
				}
			}
			else if ((t1 == 5) || (t1 == 10) || (t1 == 15))
			{
				if ((t4 == 5) || (t4 == 10) || (t4 == 15))
				{
					if ((t5 == 5) || (t5 == 10) || (t5 == 15))
					{
						vertical = true;
					}
				}
			}

			if (horizontal || vertical)
			{
				flag = true;
				if (!CB_Crusher(arr, size, i, j, current_Index))
				{
					if (!ST_Crusher(arr, size, i, j, current_Index))
					{
						if (!TL_Crusher(arr, size, i, j, current_Index))
						{
							cout << "Not Found Anything\n";
							if (horizontal)
							{
								cout << "Horizontal called\n";
								arr[i][j] = 0;
								arr[i][j + 1] = 0;
								arr[i][j + 2] = 0;
							}
							if (vertical)
							{
								cout << "Vertical called\n";
								arr[i][j] = 0;
								arr[i + 1][j] = 0;
								arr[i + 2][j] = 0;
							}
							window.clear();
							Print(arr, size, GainedPoints, TargetPoints, Moves);
							PrintGraphics(window, arr, size, GainedPoints, TargetPoints, Moves);
							window.display();
							Sleep(300);
							GainedPoints += (point * 3);
							ZeroCover(arr, size);
							Print(arr, size, GainedPoints, TargetPoints, Moves);
							window.clear();
							PrintGraphics(window, arr, size, GainedPoints, TargetPoints, Moves);
							window.display();
							Sleep(300);
							goto back;
						}
						else
						{
							window.clear();
							Print(arr, size, GainedPoints, TargetPoints, Moves);
							PrintGraphics(window, arr, size, GainedPoints, TargetPoints, Moves);
							window.display();
							Sleep(300);
							GainedPoints += (point * 5);
							ZeroCover(arr, size);
							Print(arr, size, GainedPoints, TargetPoints, Moves);
							window.clear();
							PrintGraphics(window, arr, size, GainedPoints, TargetPoints, Moves);
							window.display();
							Sleep(300);
							goto back;
						}
					}
					else
					{
						window.clear();
						Print(arr, size, GainedPoints, TargetPoints, Moves);
						PrintGraphics(window, arr, size, GainedPoints, TargetPoints, Moves);
						window.display();
						Sleep(300);
						GainedPoints += (point * 4);
						ZeroCover(arr, size);
						Print(arr, size, GainedPoints, TargetPoints, Moves);
						window.clear();
						PrintGraphics(window, arr, size, GainedPoints, TargetPoints, Moves);
						window.display();
						Sleep(300);
						goto back;
					}
				}
				else
				{
					window.clear();
					Print(arr, size, GainedPoints, TargetPoints, Moves);
					PrintGraphics(window, arr, size, GainedPoints, TargetPoints, Moves);
					window.display();
					Sleep(300);
					GainedPoints += (point * 5);
					ZeroCover(arr, size);
					Print(arr, size, GainedPoints, TargetPoints, Moves);
					window.clear();
					PrintGraphics(window, arr, size, GainedPoints, TargetPoints, Moves);
					window.display();
					Sleep(300);
					goto back;
				}
			}

		}
	}
	if (flag == false)
	{
		swap(arr[current_Index.x][current_Index.y], arr[previous_Index.x][previous_Index.y]);
		current_Index = previous_Index;
		Moves++;
	}
}
void Move(RenderWindow& window, int arr[][9], int size, Vector2i& previous_index, Vector2i& current_index, int& GainedPoints, int& TargetPoints, int& Moves)
{
	// Rect Moving Box
	RectangleShape rect;
	rect.setFillColor(Color::White);
	rect.setPosition({ (float)current_index.x * 50.0f,(float)current_index.y * 50.0f });
	rect.setSize({ 50.0f,50.0f });


	bool win_open = true;
	while (win_open)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				previous_index = current_index;
				if (event.key.code == sf::Keyboard::Up)
				{
					//cout << "up";
					if (current_index.x > 0)
					{
						current_index.x--;
					}
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					//cout << "down";
					if (current_index.x < size - 1)
					{
						current_index.x++;
					}
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					//cout << "right";
					if (current_index.y < size - 1)
					{
						current_index.y++;
					}
				}
				else if (event.key.code == sf::Keyboard::Left)
				{
					//cout << "left";
					if (current_index.y > 0)
					{
						current_index.y--;
					}
				}
				else if (event.key.code == sf::Keyboard::S)
				{
					Save(arr, size, GainedPoints, TargetPoints, Moves);
				}
				else if (event.key.code == sf::Keyboard::Escape)
				{
					Menu(arr, size, GainedPoints, TargetPoints, Moves);
					current_index = { 0,0 };
				}
				else if (event.key.code == sf::Keyboard::A)
				{
					//cout << "a";
					bool win_open2 = true;
					while (win_open2)
					{
						Event event2;
						while (window.pollEvent(event2))
						{
							if (event2.type == sf::Event::Closed)
							{
								window.close();
							}
							if (event2.type == sf::Event::KeyPressed)
							{
								if (event2.key.code == sf::Keyboard::Up)
								{
									//cout << "up";
									if (current_index.x > 0)
									{
										swap(arr[current_index.x--][current_index.y], arr[current_index.x][current_index.y]);
										Moves--;
									}
									win_open2 = false;
									win_open = false;
								}
								else if (event2.key.code == sf::Keyboard::Down)
								{
									//cout << "down";
									if (current_index.x < size - 1)
									{
										swap(arr[current_index.x++][current_index.y], arr[current_index.x][current_index.y]);
										Moves--;
									}
									win_open2 = false;
									win_open = false;
								}
								else if (event2.key.code == sf::Keyboard::Right)
								{
									//cout << "right";
									if (current_index.y < size - 1)
									{
										swap(arr[current_index.x][current_index.y++], arr[current_index.x][current_index.y]);
										Moves--;
									}
									win_open2 = false;
									win_open = false;
								}
								else if (event2.key.code == sf::Keyboard::Left)
								{
									//cout << "left";
									if (current_index.y > 0)
									{
										swap(arr[current_index.x][current_index.y--], arr[current_index.x][current_index.y]);
										Moves--;
									}
									win_open2 = false;
									win_open = false;
								}
								else if (event2.key.code == sf::Keyboard::S)
								{
									Save(arr, size, GainedPoints, TargetPoints, Moves);
								}
								else if (event2.key.code == sf::Keyboard::Escape)
								{
									Menu(arr, size, GainedPoints, TargetPoints, Moves);
									current_index = { 0,0 };
									win_open2 = false;
								}
							}
						}
						window.clear();
						window.draw(rect);
						PrintGraphics(window, arr, size, GainedPoints, TargetPoints, Moves);
						window.display();
					}
				}
			}

		}
		window.clear();
		rect.setPosition({ (float)current_index.y * 50.0f,(float)current_index.x * 50.0f });
		window.draw(rect);
		PrintGraphics(window, arr, size, GainedPoints, TargetPoints, Moves);
		window.display();
	}
}

int main()
{
	const int size = 9;

	int TargetPoints = 1000, GainedPoints = 0, Moves = 20;
	int arr[size][size] = { 0 };
	Vector2i current_index = { 0,0 };
	Vector2i previous_index = { 0,0 };
	Menu(arr, size, GainedPoints, TargetPoints, Moves);

	RenderWindow window(VideoMode(450, 550), "CANDY CRUSH", Style::Default);
	bool win_open = true;
	while (win_open)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			Print(arr, size, GainedPoints, TargetPoints, Moves);
			Move(window, arr, size, previous_index, current_index, GainedPoints, TargetPoints, Moves);
			Checker(window, arr, size, previous_index, current_index, GainedPoints, TargetPoints, Moves);
			if (Moves < 1)
			{
				if (GainedPoints >= TargetPoints)
				{
					cout << "******************* CONGRATULATIONS YOU WON *******************\n";
					win_open = false;
					window.close();
				}
				else
				{
					cout << "******************* GAME LOST *******************\n";
					win_open = false;
					window.close();
				}
			}
			//system("CLS");
		}
		window.clear();
		PrintGraphics(window, arr, size, GainedPoints, TargetPoints, Moves);
		window.display();
	}
	Menu(arr, size, GainedPoints, TargetPoints, Moves);
	return 0;
}


//*************************************** Candies Numbers **********************************************//
// 1 red		6 red stripe		11 red wrap
// 2 green		7 green stripe		12 green wrap
// 3 blue		8 blue stripe		13 blue wrap
// 4 yellow		9 Yellow stripe		14 yellow wrap
// 5 Orange		10 Orange Stripe	15 Orange Wrap
//               16 bomb