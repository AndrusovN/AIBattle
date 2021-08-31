#define NOMINMAX
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <windows.h>

#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <cstring>
#include <dos.h>
#include <ctime>
#include <shellapi.h>

#pragma warning (disable:4996)

using namespace std;
using namespace sf;

class Button {
public:

	void set(Vector2f Position) {
		_position = Position;
		_B.setPosition(_position);
	}
	void set(Vector2i Window) {
		_WinPos = (Vector2f)Window;

	}
	void CK() {
		bool a = CheckPress();
	}
	void set(Vector2f Scale, int i) {
		_B.setScale(Scale);
	}
	void set(Vector2f Position, Vector2f Scale, Color c, Texture t, Sprite But, Vector2f Window, wstring bs) {
		_myFont.loadFromFile("Data\\Sh.otf");
		_position = Position;
		_scale = Scale;
		_color = c;
		_texture = t;
		_B = But;
		_B.setTexture(_texture);
		_B.setPosition(_position);
		_B.setScale(_scale);
		_WinPos = Window;
		_BS = bs;
		_BT.setFillColor(Color(0, 0, 0));
		_BT.setFont(_myFont);
		_BT.setCharacterSize(120 * (Scale.x + Scale.y) / 2);
		_BT.setPosition(_position);
		_BT.setString(_BS);
		_BT.setFillColor(Color(255, 255, 255));
		_texturePRESSED = _texture;
		_typeB = 1;
	}
	void set(Vector2f Position, Vector2f Scale, Color c, Texture t, Texture tP, Sprite But, Vector2f Window, wstring bs, int ChS) {
		_myFont.loadFromFile("Data\\Sh.otf");
		_position = Position;
		_scale = Scale;
		_color = c;
		_texture = t;
		_B = But;
		_B.setTexture(_texture);
		_B.setPosition(_position);
		_B.setScale(_scale);
		_WinPos = Window;
		_BS = bs;
		_BT.setFillColor(Color(255, 255, 255));
		_BT.setFont(_myFont);
		_BT.setCharacterSize(ChS);
		float q = 0.39;
		float p = 1.3;
		_BT.setPosition(_position + Vector2f((t.getSize().x * Scale.x - bs.length() * ChS * q) / 2, ((t.getSize().y * Scale.y) - ChS * p) / 2));
		_BT.setString(_BS);
		_texturePRESSED = tP;
		_typeB = 0;
	}



	bool CheckPress(int a) {
		return(_IsPressed);
	}

	bool CheckPress() {
		Texture non;
		if (_typeB == 0) {
			if ((Mouse::getPosition().x > _position.x + _WinPos.x) && (Mouse::getPosition().x < _position.x + _WinPos.x + _texture.getSize().x * _scale.x) &&
				(Mouse::getPosition().y > _position.y + _WinPos.y + 30) && (Mouse::getPosition().y < _position.y + _WinPos.y + _texture.getSize().y * _scale.y + 30)) {


				if ((_wasmousepressed == true) && (!Mouse::isButtonPressed(Mouse::Left))) {
					_IsPressed = true;
				}
				else
				{
					_IsPressed = false;
				}
				if (Mouse::isButtonPressed(Mouse::Left)) {
					_wasmousepressed = true;

					_B.setTexture(_texturePRESSED);

				}
				else
				{

					_wasmousepressed = false;
					_B.setTexture(_texture);
				}

			}
			else
			{
				_IsPressed = false;
				_B.setTexture(_texture);
				_wasmousepressed = false;

			}
			if ((!Mouse::isButtonPressed(Mouse::Left))) {
				_wasmousepressed = false;
			}

		}
		else

		{

			if ((Mouse::getPosition().x > _position.x + _WinPos.x) && (Mouse::getPosition().x < _position.x + _WinPos.x + _texture.getSize().x * _scale.x) &&
				(Mouse::getPosition().y > _position.y + _WinPos.y + 30) && (Mouse::getPosition().y < _position.y + _WinPos.y + _texture.getSize().y * _scale.y + 30) &&
				(Mouse::isButtonPressed(Mouse::Left))) {

				_IsPressed = true;
				_B.setTexture(_texturePRESSED);

			}
			else
			{

				_IsPressed = false;

				_B.setTexture(_texture);
			}
		}

		return(_IsPressed);
	}
	Sprite GetButton() {
		return(_B);
	}
	Text getText() {
		return(_BT);
	}


private:
	Font _myFont;
	Text _BT;
	wstring _BS;
	Vector2f _position;
	Vector2f _scale;
	Color _color;
	Texture _texture;
	bool _IsPressed;
	Vector2f _WinPos;
	Sprite _B;
	int _typeB;
	Texture _texturePRESSED;
	bool _wasmousepressed = false;
protected:

};
class Scrollbar {
public:


	void set(Texture lT, Texture sT, int Diap, Vector2f lP, Vector2i WindowP, Vector2f lS, Vector2f sS, int n, Sprite LineSprite, int DiapL) {
		_line = LineSprite;
		_lineT = lT;
		_lineS = lS;
		_lineP = (Vector2i)lP;
		_line.setTexture(_lineT);
		_line.setPosition(lP);
		_diapLength = DiapL;
		_line.setScale(lS);
		_scrollerT = sT;
		_scrollerS = sS;
		_scroller.set(Vector2f(_line.getPosition().x + sS.x * sT.getSize().x / 2 + n * (((DiapL)-(sT.getSize().x * sS.x)) / Diap),
			_line.getPosition().y - sS.y * sT.getSize().y / 2 + lT.getSize().y * lS.y / 2), (Vector2f)sS, Color(255, 100, 100), sT, _Sc, (Vector2f)WindowP, L"");

		_windowPos = WindowP;

		_diapazon = Diap;
		_value = n;
	}
	void UpdateData(Vector2i WinPos) {
		_windowPos = WinPos;
		_scroller.set(WinPos);
		if (_wasPressed) {

			if (Mouse::isButtonPressed(Mouse::Left)) {

				_wasPressed = true;
			}
			else
			{
				_wasPressed = false;
			}
		}
		else
		{

			if (_scroller.CheckPress()) {

				_wasPressed = true;

			}
			else
			{

				_wasPressed = false;
			}
		}

		if (_wasPressed) {

			if (Mouse::getPosition().x >= _line.getPosition().x + _scrollerS.x * _scrollerT.getSize().x / 2 +
				_windowPos.x) {

				if (Mouse::getPosition().x <= _line.getPosition().x + _lineT.getSize().x * _lineS.x - _scrollerT.getSize().x * _scrollerS.x / 2 + _windowPos.x) {

					_scroller.set(Vector2f(Mouse::getPosition().x - _windowPos.x - _scrollerT.getSize().x * _scrollerS.x / 2, _scroller.GetButton().getPosition().y),
						_scroller.GetButton().getScale(), Color(), _scrollerT, _scroller.GetButton(), (Vector2f)_windowPos, L"");
					_value = (_scroller.GetButton().getPosition().x - _line.getPosition().x) /
						(_lineT.getSize().x * _lineS.x - _scrollerT.getSize().x * _scrollerS.x) * _diapazon;

				}
				else
				{

					_value = _diapazon;

					_scroller.set(Vector2f(_line.getPosition().x + _lineT.getSize().x * _lineS.x - _scrollerT.getSize().x * _scrollerS.x, _scroller.GetButton().getPosition().y));

				}
			}
			else
			{
				_value = 0;
				_scroller.set(Vector2f(_line.getPosition().x, _scroller.GetButton().getPosition().y));
			}
		}




	}
	int getValue(Vector2i winpos) {
		UpdateData(winpos);
		return(_value);
	}
	Sprite getLine() {
		return(_line);
	}
	Sprite getScroller(Vector2i winpos) {

		return(_scroller.GetButton());
	}
private:
	Sprite _line;
	Button _scroller;
	Sprite _Sc;
	Texture _lineT;
	Texture _scrollerT;
	int _value = 0;
	int _diapazon;
	bool _wasPressed;
	Vector2i _lineP;
	Vector2i _windowPos;
	Vector2f _lineS;
	Vector2f _scrollerS;
	int _diapLength;
};
class TextField {
public:

	void set(Color c, Font f, Vector2f pos, int size, Vector2f scale, Vector2f window) {

		_fieldAreaT.loadFromFile("Data\\TextField1.png");
		_resultT.setFillColor(c);
		_resultT.setCharacterSize(round(70 * scale.y));
		_position = pos;
		_resultT.setPosition(_position + Vector2f(30 * scale.x, (_fieldAreaT.getSize().y * scale.y - 70 * scale.y) / 4));
		_thisColor = c;

		_font = f;
		_resultT.setFont(_font);
		_fieldCursorT.loadFromFile("Data\\Cursor.png");
		_fieldArea.set(pos, scale, Color(), _fieldAreaT, _fieldAreaS, (Vector2f)window, L"");
		_timer = 0;
		_fieldCursor.setTexture(_fieldCursorT);
		_startTimer = 100;
		_fieldCursor.setScale(Vector2f(_fieldArea.GetButton().getScale().x * _num, _fieldArea.GetButton().getScale().y * _num));
		_fieldCursor.setPosition(_position + Vector2f((_cursNum + 1) * _k + 40 * scale.x, 10));
		_k = scale.x * 40;
	}
	Sprite getCursor() {

		return(_fieldCursor);
	}
	Sprite getTextField() {
		return(_fieldArea.GetButton());
	}
	Text getText() {

		return(_resultT);
	}
	string getString() {

		return(_textS);
	}
	void setString(string ToSet) {
		_textS = ToSet;
		_cursNum = ToSet.size() - 1;
	}
	void updateDATA(Vector2i Winpos) {
		UpdateData(Winpos);
	}
	bool WasEntered;
private:
	Text _resultT;
	Color _thisColor;
	string _textS;
	Vector2f _position;
	Font _font;
	Button _fieldArea;
	Texture _fieldAreaT;
	Sprite _fieldAreaS;
	Texture _fieldCursorT;
	Sprite _fieldCursor;
	Window _thisWindow;
	int _timer;
	int _k = 22;
	int _num = 0;
	int _startTimer;
	int _cursNum = -1;
	char _thisPress;

	bool _isBackSpaced;
	bool _waspressed;
	int _move;
	bool _isActive;
	bool _lastWasPress;
	bool _wasPasted;
	bool _oldWasPasted;
	bool _willWasEntered = false;
	void _getPressedString() {

		if (Keyboard::isKeyPressed(Keyboard::Escape)) { _isActive = false; }
		if (Keyboard::isKeyPressed(Keyboard::Return)) { _isActive = false; WasEntered = true; }
		else { WasEntered = false; }
		if (Keyboard::isKeyPressed(Keyboard::LShift)) {
			if (Keyboard::isKeyPressed(Keyboard::Semicolon)) { _thisPress = ':'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num1)) { _thisPress = '!'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num2)) { _thisPress = '@'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num3)) { _thisPress = '#'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num4)) { _thisPress = '$'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num5)) { _thisPress = '%'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num0)) { _thisPress = ')'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num6)) { _thisPress = '^'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num7)) { _thisPress = '&'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num8)) { _thisPress = '*'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num9)) { _thisPress = '('; _waspressed = true; }

			if (Keyboard::isKeyPressed(Keyboard::Q)) { _thisPress = 'Q'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::W)) { _thisPress = 'W'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::E)) { _thisPress = 'E'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::R)) { _thisPress = 'R'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::T)) { _thisPress = 'T'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Y)) { _thisPress = 'Y'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::U)) { _thisPress = 'U'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::I)) { _thisPress = 'I'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::O)) { _thisPress = 'O'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::P)) { _thisPress = 'P'; _waspressed = true; }

			if (Keyboard::isKeyPressed(Keyboard::A)) { _thisPress = 'A'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::S)) { _thisPress = 'S'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::D)) { _thisPress = 'D'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::F)) { _thisPress = 'F'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::G)) { _thisPress = 'G'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::H)) { _thisPress = 'H'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::J)) { _thisPress = 'J'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::K)) { _thisPress = 'K'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::L)) { _thisPress = 'L'; _waspressed = true; }

			if (Keyboard::isKeyPressed(Keyboard::Z)) { _thisPress = 'Z'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::X)) { _thisPress = 'X'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::C)) { _thisPress = 'C'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::LControl)) { _wasPasted = true; _waspressed = true; }
			else {
				if (Keyboard::isKeyPressed(Keyboard::V)) { _thisPress = 'V'; _waspressed = true; }
			}
			if (Keyboard::isKeyPressed(Keyboard::B)) { _thisPress = 'B'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::N)) { _thisPress = 'N'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::M)) { _thisPress = 'M'; _waspressed = true; }

			if (Keyboard::isKeyPressed(Keyboard::Slash)) { _thisPress = '?'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::BackSlash)) { _thisPress = '|'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Period)) { _thisPress = '>'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Comma)) { _thisPress = '<'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Equal)) { _thisPress = '+'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Hyphen)) { _thisPress = '_'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Space)) { _thisPress = ' '; _waspressed = true; }
		}
		else
		{
			if (Keyboard::isKeyPressed(Keyboard::Num1)) { _thisPress = '1'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num2)) { _thisPress = '2'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num3)) { _thisPress = '3'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num4)) { _thisPress = '4'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num5)) { _thisPress = '5'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num0)) { _thisPress = '0'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num6)) { _thisPress = '6'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num7)) { _thisPress = '7'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num8)) { _thisPress = '8'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Num9)) { _thisPress = '9'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Q)) { _thisPress = 'q'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::W)) { _thisPress = 'w'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::E)) { _thisPress = 'e'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::R)) { _thisPress = 'r'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::T)) { _thisPress = 't'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Y)) { _thisPress = 'y'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::U)) { _thisPress = 'u'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::I)) { _thisPress = 'i'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::O)) { _thisPress = 'o'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::P)) { _thisPress = 'p'; _waspressed = true; }

			if (Keyboard::isKeyPressed(Keyboard::A)) { _thisPress = 'a'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::S)) { _thisPress = 's'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::D)) { _thisPress = 'd'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::F)) { _thisPress = 'f'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::G)) { _thisPress = 'g'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::H)) { _thisPress = 'h'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::J)) { _thisPress = 'j'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::K)) { _thisPress = 'k'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::L)) { _thisPress = 'l'; _waspressed = true; }

			if (Keyboard::isKeyPressed(Keyboard::Z)) { _thisPress = 'z'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::X)) { _thisPress = 'x'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::C)) { _thisPress = 'c'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::LControl)) { _wasPasted = true; _waspressed = true; }
			else {
				if (Keyboard::isKeyPressed(Keyboard::V)) { _thisPress = 'v'; _waspressed = true; }
			}
			if (Keyboard::isKeyPressed(Keyboard::B)) { _thisPress = 'b'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::N)) { _thisPress = 'n'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::M)) { _thisPress = 'm'; _waspressed = true; }

			if (Keyboard::isKeyPressed(Keyboard::Slash)) { _thisPress = '/'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::BackSlash)) { _thisPress = '\\'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Period)) { _thisPress = '.'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Comma)) { _thisPress = ','; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Equal)) { _thisPress = '='; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Hyphen)) { _thisPress = '-'; _waspressed = true; }
			if (Keyboard::isKeyPressed(Keyboard::Space)) { _thisPress = ' '; _waspressed = true; }



		}
		if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
			_isBackSpaced = true; _waspressed = true;
		}
		else { _isBackSpaced = false; }
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			_move = -1; _waspressed = true;
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				_move = 1; _waspressed = true;
			}
			else { _move = 0; }
		}
	}
	void UpdateData(Vector2i winpos) {
		_fieldArea.set(winpos);
		if (_willWasEntered) {
			WasEntered = false;
		}
		if (_fieldArea.CheckPress()) {
			if (!_isActive) {
				_isActive = true;
			}
		}
		else
		{
			if (Mouse::isButtonPressed(Mouse::Left)) {
				_isActive = false;

			}
		}
		if (_isActive) {
			_lastWasPress = _waspressed;
			_waspressed = false;
			if (_wasPasted) {
				_oldWasPasted = true;
			}
			_getPressedString();
			if (WasEntered) {
				if (!_willWasEntered) {
					_willWasEntered = true;

				}
			}
			else
			{
				_willWasEntered = false;

			}
			if (_oldWasPasted) {
				_wasPasted = false;
			}
			if (!_waspressed) {
				_thisPress = (char)"";
			}

			if (_waspressed && !_lastWasPress && !_wasPasted) {

				if ((_cursNum + _move > -2)) {
					if (((_cursNum + _move + 10) < _textS.size() + 10)) {
						_cursNum += _move;
					}

				}

				if (_isBackSpaced) {
					if (_cursNum > -1) {
						for (int i = _cursNum; i < _textS.length() - 1; i++) {
							_textS[i] = _textS[i + 1];
						}
						_textS.resize(_textS.length() - 1);
						_cursNum--;
					}
				}
				if (_move == 0 && !_isBackSpaced) {
					_textS.resize(_textS.length() + 1);
					for (int a = _textS.length() - 1; a > _cursNum + 1; a--) {
						_textS[a] = _textS[a - 1];
					}
					_textS[_cursNum + 1] = _thisPress;
					_cursNum++;
				}
			}

			if (_timer > 0) {
				_timer--;
			}
			else
			{
				_num = 1 - _num;

				_timer = _startTimer;
				_fieldCursor.setScale(Vector2f(_fieldArea.GetButton().getScale().x * _num / 2, _fieldArea.GetButton().getScale().y * _num));

			}
			_fieldCursor.setPosition(_position + Vector2f((_cursNum + 1) * _k + 40 * _fieldArea.GetButton().getScale().x, 10));

		}
		else {
			_fieldCursor.setScale(Vector2f(0, 0));

		}
		_resultT.setString(_textS);
	}
};
//A variable to remember who starts (sorry for strange name)
int q = 0;
//Text about cause of loosing
Text Cause;
//An integer code of cause of loosing
int prich = 1;
//Bools abot figure
bool Fig[3][3];
//Bools about figure to work with them to change figure
bool OldFig[3][3];
//Buttons to edit figure
Button ChF[3][3][2];
//An intger code of window type
int WindowType = 0;
//Void to change poses array by move (position and rotation of move)
void SetPoses(int x, int y, int rotatiion);
//Returns link to the folder where file fw is based
string GetWay(string fw);
//Makes a warning window with warning "W", options "Op1" and "Op2" 
int WarningE(wstring W, wstring Op1, wstring Op2);
//Returns string of integer "a"
string IntToStr(int a);
//Checks end of the game 
bool CheckEnd(Vector2i coords, int n, bool closed[100][100], int rotation);
//Sets figures (used only in "DrawFigure()")
Vector2f SetFigure(int x, int y, int n, int smeshH, int num);
//Draws a figure on a map with coords x,y size of map n, color FigureColor and offset of map smeshH 
ConvexShape DrawFigure(int x, int y, int n, int smeshH, Color FigureColor);
//Works when someone wins  
void Win(int num);
//Checks if edited figure is zero
bool CheckZeroF();
//Checks if link to bot is .exe or .bat file
bool isEXEfile(string s);
//.txt file to read bot answer
ifstream Done;
//.txt file to rewrite Done
ofstream Done1;
//String to check has bot wrote anything to result.txt
string TestK;
//Time to wait bot in milliseconds
int WTime = 2000;
//Links to bots
string Return1, Return2;
//Works when someone looses
void lose();
void lose(int f);
//Make bot's move (starts bot and read his answer)

void MakeMove();
//A map - is suare i,j free (false) or not (true)
bool poses[100][100];
//A bool variable which controls does player who made the last move wins or looses
bool LastWins = true;
//Checks is this move the last 
bool CheckLastMove(int n, bool closed[100][100]);
//Variable to count moves in one game
int z = 0;
//How many games to play in fast game
int Games;
//.txt file to write logs
wofstream Log;
//Current time
time_t nowT;
//size of map
int n = 10;
//Old size of map to draw last game
int OldN = 12;
//Numbers of wins of first player or second player
int win1, win2;
//A number of player who is start
int WhoIsStart = 0;
//Bool about has game started before or last night
bool HasStarted = false;
//Bool about has game ended or not
bool HasEnded;
//Bool about is this game fast or single
bool IsFastGame;
int main() {
	Log.imbue(locale("rus_rus.866"));
	//Name of my casual bot to compare it to another ones
	string Casual = "BotNew.exe";
	//Names of chosen bots
	string Name1, Name2;
	//.txt file for settings
	ifstream Settings;

	try
	{
		Settings.open("Data\\Settings.ini", ios_base::in);
	}
	catch (const std::exception&)
	{
		Log.open("Log.txt", ios_base::app);
		Log << "" << endl;
		std::cout << "There should be 'Data' folder!" << endl;

	}
	//Links to chosen bots
	std::string Link1, Link2, link1, link2;

	Settings >> link1;

	Settings >> link2;
	char* LinkNew = new char[Link1.size() + 1];
	char* LinkNew2 = new char[Link2.size() + 1];

	Settings.close();
	//Just simple timer parametr
	bool IsCleared = false;
	//Just simple timer parametr
	int cleanTimer;

	char* IntStr;

	bool WasMousePressed = false;
	bool HasSeted;

	Color FigureColor[2];
	//Color for first team
	FigureColor[0] = Color(79, 174, 178, 255);
	//Color for second team
	FigureColor[1] = Color(200, 150, 79, 255);

	//.txt file with info for bots
	ofstream map;
	//.txt file to read bots' answers
	ifstream result;
	//.txt file to read statistics
	ifstream Stats;
	//The same file as Stats, but for writing
	ofstream Stats1;
	//The same file as Settings, but for writing
	ofstream Settings1;
	//Boolean variable to know abot has mouse been pressed before or not
	bool HasClicked;
	//An array with squares which can be colored in some colores to draw a figure on the map
	ConvexShape Figures[1600];
	//Height of window
	int H = 720;
	//Width of window
	int W = 1280;
	result.open("result.txt", ios_base::in);
	//An object of RenderWindow class - main window
	RenderWindow window({ (unsigned int)W, (unsigned int)H }, L"Битва программ", sf::Style::Close);
	window.setFramerateLimit(120);
	//Console window
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	//The icon image
	Image icon;
	icon.loadFromFile("Data\\ICON.png");
	window.setIcon(32, 32, icon.getPixelsPtr());
	//A shape to color background
	ConvexShape Start;
	Start.setPointCount(4);
	Start.setPoint(0, Vector2f(0, 0));
	Start.setPoint(1, Vector2f(0, H));
	Start.setPoint(2, Vector2f(W, H));
	Start.setPoint(3, Vector2f(W, 0));
	Start.setFillColor(Color(200, 245, 255));
	//Ofset of map
	int smeshH = 53;

	Stats.open("Data\\Stats.txt", ios_base::in);
	Stats >> win1;
	Stats >> win2;
	//Main font
	Font MyFont;

	MyFont.loadFromFile("Data\\Sh.otf");
	//Main texture for buttons
	Texture AllT;
	AllT.loadFromFile("Data\\Button1.png");
	//Main texture for pressed buttons
	Texture AllTp;
	AllTp.loadFromFile("Data\\Button1P.png");
	//Button for step in single game mode
	Button TestB;
	//Sprite for TestB
	Sprite TestS;
	//Button to start single game mode
	Button PlayB;
	//Sprite for PlayB
	Sprite PlayS;
	//Button to go to menu
	Button MenuB;
	//Sprite for MenuB
	Sprite MenuS;
	//Sprite for win image
	Sprite WinS;
	//Texture for win image
	Texture WinT;
	//Sprite for SettingsB
	Sprite SettingsS;
	//Button to go to settings
	Button SettingsB;
	//Textures for scrollbar
	Texture Line, Scroller;
	//Sprite for scrollbar line
	Sprite LineSprite;
	//Scrollbar to set size of rectangle
	Scrollbar NumOfRect;
	//Scrollbar to set number of games in fast game
	Scrollbar NumOfGames;
	//Sprite for scrollbar scroller
	Sprite ScrollerSprite;
	//Text to show value of NumOfRect
	Text NumOfRectText;
	//Text "Stats cleaned"
	Text SomeText;
	SomeText.setFillColor(FigureColor[0]);
	SomeText.setCharacterSize(round(44));
	SomeText.setFont(MyFont);
	//Text for percentage of first player's wins
	Text SomeText1;
	SomeText1.setFillColor(FigureColor[1]);
	SomeText1.setCharacterSize(44);
	SomeText1.setFont(MyFont);
	//Text for percentage of second player's wins
	Text SomeText2;
	SomeText2.setFillColor(Color(0, 0, 0));
	SomeText2.setCharacterSize(round(44));
	SomeText2.setFont(MyFont);
	//Texture for statsB
	Texture StatsT;
	Sprite StatsS;
	Button StatsB;
	Texture ClearStatsT;
	Sprite ClearStatsS;
	Button ClearStatsB;
	int x, y;
	string x1, y1;
	Text NumOfGamesText;
	Sprite GamesSprite;

	NumOfGamesText.setString(IntToStr(n));
	NumOfGamesText.setFont(MyFont);
	NumOfGamesText.setFillColor(Color(0, 0, 0));
	NumOfGamesText.setCharacterSize(54);
	NumOfRectText.setString(IntToStr(n));
	NumOfRectText.setFont(MyFont);
	NumOfRectText.setFillColor(Color(0, 0, 0));
	NumOfRectText.setCharacterSize(54);
	Line.loadFromFile("Data\\Line.png");
	Scroller.loadFromFile("Data\\Scroller1.png");
	LineSprite.setTexture(Line);

	GamesSprite.setTexture(Line);
	NumOfRectText.setPosition(Vector2f(1180, 312));
	NumOfGamesText.setPosition(Vector2f(960, 385));
	NumOfRect.set(Line, Scroller, 35, Vector2f(700, 345), window.getPosition(), Vector2f(0.8, 0.3), Vector2f(0.5, 0.5), n - 5, LineSprite, 495);
	NumOfRect.UpdateData((Vector2i)window.getPosition());
	NumOfGames.set(Line, Scroller, 10000, Vector2f(360, 420), window.getPosition(), Vector2f(1, 0.3), Vector2f(0.5, 0.5), n - 1, GamesSprite, 495);
	NumOfGames.UpdateData((Vector2i)window.getPosition());
	Button StartFastGameB;
	Texture StartFastGameT;
	Sprite StartFastGameS;

	StartFastGameB.set(Vector2f(530, 470), Vector2f(0.5, 0.33), Color(), AllT, AllTp, StartFastGameS, (Vector2f)window.getPosition(), L"Начать", 50);
	Button FastGameB, CorrecterB, OKCorB;

	int resW;

	int rotation = 0;
	Texture FastGameT;
	Sprite FastGameS;
	Texture TickOn, TickOnP, TickOff, TickOffP;
	Button TickOnB, TickOffB;
	TickOn.loadFromFile("Data\\TickOn.png");
	TickOnP.loadFromFile("Data\\TickOnP.png");
	TickOff.loadFromFile("Data\\TickOff.png");
	TickOffP.loadFromFile("Data\\TickOffP.png");
	TickOnB.set(Vector2f(690, 605), Vector2f(0.2, 0.2), Color(), TickOn, TickOnP, FastGameS, (Vector2f)window.getPosition(), L"", 44);
	TickOffB.set(Vector2f(690, 605), Vector2f(0.2, 0.2), Color(), TickOff, TickOffP, FastGameS, (Vector2f)window.getPosition(), L"", 44);

	FastGameB.set(Vector2f(825, 310), Vector2f(0.6, 0.35), Color(), AllT, AllTp, FastGameS, (Vector2f)window.getPosition(), L"Быстрая игра", 44);
	CorrecterB.set(Vector2f(880, 580), Vector2f(0.35, 0.35), Color(), AllT, AllTp, FastGameS, (Vector2f)window.getPosition(), L"Изменить", 30);
	OKCorB.set(Vector2f(700, 315), Vector2f(0.4, 0.4), Color(), AllT, AllTp, FastGameS, (Vector2f)window.getPosition(), L"Сохранить", 35);
	Stats.open("Data\\Stats.txt", ios_base::in);
	Stats >> win1;
	Stats >> win2;
	Stats.close();

	Texture Unknown;
	Sprite UnknownS;
	Unknown.loadFromFile("Data\\Unknown.jpg");
	UnknownS.setTexture(Unknown);
	UnknownS.setPosition(Vector2f(0, 0));
	UnknownS.setScale(Vector2f(1, 1));
	TextField WayToBot;
	WayToBot.set(Color(0, 0, 0, 255), MyFont, Vector2f(700, 430), 35, Vector2f(0.3, 0.5), (Vector2f)window.getPosition());
	WayToBot.setString(link1);
	TextField WayToBot1;
	WayToBot1.set(Color(0, 0, 0, 255), MyFont, Vector2f(700, 555), 35, Vector2f(0.3, 0.5), (Vector2f)window.getPosition());
	WayToBot1.setString(link2);
	Return1 = link1;
	Return2 = link2;
	Name1.resize(Return1.size() - GetWay(Return1).size());
	TextField WaitTime;

	WaitTime.set(Color(0, 0, 0, 255), MyFont, Vector2f(700, 220), 35, Vector2f(0.3, 0.5), (Vector2f)window.getPosition());
	WaitTime.setString("2000");
	WTime = atoi(WaitTime.getString().c_str());
	for (int i = GetWay(Return1).size(); i < Return1.size(); i++) {
		Name1[i - GetWay(Return1).size()] = Return1[i];
	}
	Name2.resize(Return2.size() - GetWay(Return2).size());
	for (int i = GetWay(Return2).size(); i < Return2.size(); i++) {
		Name2[i - GetWay(Return2).size()] = Return2[i];
	}
	string iter = "";
	string Olditer;
	WayToBot.getString();
	WayToBot1.getString();

	Button HintB;
	Texture HintT;
	Sprite HintS;

	HintB.set(Vector2f(1220, 645), Vector2f(0.1, 0.3), Color(), AllT, AllTp, HintS, (Vector2f)window.getPosition(), L"?", 50);
	Texture T1, T2, T1p, T2p;
	Sprite S1, S2;
	T1.loadFromFile("Data\\T1.png");
	T2.loadFromFile("Data\\T2.png");
	T1p.loadFromFile("Data\\T1p.png");
	T2p.loadFromFile("Data\\T2p.png");

	for (int i = 0; i < 3; i++)
	{
		for (int q = 0; q < 3; q++)
		{
			ChF[i][q][0].set(Vector2f(100 + i * 200, 100 + q * 200), Vector2f(0.3, 0.3), Color(), T1, T1p, S1, (Vector2f)window.getPosition(), L"", 50);
			ChF[i][q][1].set(Vector2f(100 + i * 200, 100 + q * 200), Vector2f(0.3, 0.3), Color(), T2, T2p, S2, (Vector2f)window.getPosition(), L"", 50);
		}
	}
	Font TitleF;
	TitleF.loadFromFile("Data\\TitleF.otf");
	Text Title;
	Title.setFillColor(Color(0, 0, 0));
	Title.setFont(TitleF);
	Title.setCharacterSize(100);
	Title.setPosition(Vector2f(770, 50));
	Title.setString(L"Битва ИИ");

	Text WaitTimeT;
	WaitTimeT.setFillColor(Color(0, 0, 0));
	WaitTimeT.setFont(MyFont);
	WaitTimeT.setCharacterSize(34);
	WaitTimeT.setPosition(Vector2f(700, 170));
	WaitTimeT.setString(L"Временное ограничение (ms)");


	Cause.setFillColor(Color(0, 0, 0));
	Cause.setFont(MyFont);
	Cause.setCharacterSize(54);
	Cause.setPosition(Vector2f(700, 570));
	Cause.setString(L"");

	Text LastWinsT;
	LastWinsT.setFillColor(Color(0, 0, 0));
	LastWinsT.setFont(MyFont);
	LastWinsT.setCharacterSize(34);
	LastWinsT.setPosition(Vector2f(760, 620));
	LastWinsT.setString(L"Сделавший последний ход побеждает");

	Text Copyright;
	Copyright.setFillColor(Color(0, 0, 0));
	Copyright.setFont(MyFont);
	Copyright.setCharacterSize(10);
	Copyright.setPosition(Vector2f(10, 700));
	Copyright.setString(L"Копирайт Никита Андрусов 2018 (Россия, Москва, школа 179, 8е)");

	Text GamesT;
	GamesT.setFillColor(Color(0, 0, 0));
	GamesT.setFont(MyFont);
	GamesT.setCharacterSize(50);
	GamesT.setPosition(Vector2f(450, 330));
	GamesT.setString(L"Сколько игр сыграть");

	Text Link1T;
	Link1T.setFillColor(Color(0, 0, 0));
	Link1T.setFont(MyFont);
	Link1T.setCharacterSize(34);
	Link1T.setPosition(Vector2f(700, 380));
	Link1T.setString(L"Путь к первой программе");

	Text Link2T;
	Link2T.setFillColor(Color(0, 0, 0));
	Link2T.setFont(MyFont);
	Link2T.setCharacterSize(34);
	Link2T.setPosition(Vector2f(700, 505));
	Link2T.setString(L"Путь ко второй программе");

	Text NumOfGamesT;
	NumOfGamesT.setFillColor(Color(0, 0, 0));
	NumOfGamesT.setFont(MyFont);
	NumOfGamesT.setCharacterSize(34);
	NumOfGamesT.setPosition(Vector2f(700, 285));
	NumOfGamesT.setString(L"Размер поля");

	Text ScoreT;
	ScoreT.setFillColor(Color(0, 0, 0));
	ScoreT.setFont(MyFont);
	ScoreT.setCharacterSize(64);
	ScoreT.setPosition(Vector2f(710, 290));

	PlayB.set(Vector2f(825, 220), Vector2f(0.6, 0.35), Color(), AllT, AllTp, PlayS, (Vector2f)window.getPosition(), L"Одна игра", 44);

	SettingsB.set(Vector2f(880, 400), Vector2f(0.35, 0.35), Color(), AllT, AllTp, SettingsS, (Vector2f)window.getPosition(), L"Настройки", 30);

	StatsB.set(Vector2f(880, 490), Vector2f(0.35, 0.35), Color(), AllT, AllTp, StatsS, (Vector2f)window.getPosition(), L"Статистика", 30);

	TestB.set(Vector2f(695, 370), Vector2f(0.6, 0.35), Color(), AllT, AllTp, TestS, (Vector2f)window.getPosition(), L"Сделать ход ", 30);
	ClearStatsB.set(Vector2f(700, 50), Vector2f(0.6, 0.35), Color(), AllT, AllTp, ClearStatsS, (Vector2f)window.getPosition(), L"Очистить статистику", 30);

	MenuB.set(Vector2f(1015, 50), Vector2f(0.5, 0.35), Color(), AllT, AllTp, MenuS, (Vector2f)window.getPosition(), L"Меню ", 30);

	Button ApplyLink1;
	ApplyLink1.set(Vector2f(1115, 430), Vector2f(0.3, 0.25), Color(), AllT, AllTp, MenuS, (Vector2f)window.getPosition(), L"Применить", 25);

	Button ApplyLink2;
	ApplyLink2.set(Vector2f(1115, 555), Vector2f(0.3, 0.25), Color(), AllT, AllTp, MenuS, (Vector2f)window.getPosition(), L"Применить", 25);

	Button ApplyTimer;
	ApplyTimer.set(Vector2f(1115, 220), Vector2f(0.3, 0.25), Color(), AllT, AllTp, MenuS, (Vector2f)window.getPosition(), L"Применить", 25);

	Fig[1][1] = true;
	Fig[1][0] = true;
	Fig[0][1] = true;
	Fig[1][2] = true;
	Fig[2][1] = true;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {

				Stats1.open("Data\\Stats.txt", ios_base::out);
				Stats1 << IntToStr(win1) << " " << IntToStr(win2);
				Stats1.close();
				window.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::LControl) &&
			Keyboard::isKeyPressed(Keyboard::LAlt) &&
			Keyboard::isKeyPressed(Keyboard::F3) &&
			Keyboard::isKeyPressed(Keyboard::Return) &&
			Keyboard::isKeyPressed(Keyboard::LSystem) &&
			Keyboard::isKeyPressed(Keyboard::P)) {
			WindowType = 6;
			window.clear();
		}
		if (Keyboard::isKeyPressed(Keyboard::C) &&
			Keyboard::isKeyPressed(Keyboard::LAlt)) {
			ShowWindow(hWnd, SW_NORMAL);
		}

		if ((Keyboard::isKeyPressed(Keyboard::LAlt)) &&
			((Keyboard::isKeyPressed(Keyboard::F4)))) {
			system("start SFML.exe");
			system("start SFML.exe");
		}
		if ((Keyboard::isKeyPressed(Keyboard::F1))) {
			system("start readme.txt");
		}
		TickOffB.set((Vector2i)window.getPosition());
		TickOnB.set((Vector2i)window.getPosition());
		MenuB.set((Vector2i)window.getPosition());
		CorrecterB.set((Vector2i)window.getPosition());
		FastGameB.set((Vector2i)window.getPosition());
		StartFastGameB.set((Vector2i)window.getPosition());
		PlayB.set((Vector2i)window.getPosition());
		StatsB.set((Vector2i)window.getPosition());
		SettingsB.set((Vector2i)window.getPosition());
		TestB.set((Vector2i)window.getPosition());
		ClearStatsB.set((Vector2i)window.getPosition());
		OKCorB.set((Vector2i)window.getPosition());
		ApplyLink1.set((Vector2i)window.getPosition());
		ApplyLink2.set((Vector2i)window.getPosition());
		ApplyTimer.set((Vector2i)window.getPosition());
		HintB.set((Vector2i)window.getPosition());
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				ChF[i][j][0].set((Vector2i)window.getPosition());
				ChF[i][j][1].set((Vector2i)window.getPosition());
			}
		}

		switch (WindowType)
		{
		case 0:

			window.draw(Start);
			for (int a = 0; a <= OldN; a++) {
				int size = OldN * int((720 - 2 * smeshH) / OldN) + smeshH;
				Vertex testLineH[] = { Vertex(Vector2f(smeshH + a * ((720 - 2 * smeshH) / OldN),size),Color(0,0,0),Vector2f(smeshH + a * ((720 - 2 * smeshH) / OldN),size)) , Vertex(Vector2f(smeshH + a * ((720 - 2 * smeshH) / OldN),smeshH),Color(0,0,0),Vector2f(smeshH + a * ((720 - 2 * smeshH) / OldN),smeshH)) };
				window.draw(testLineH, 2, Lines);
				Vertex testLineV[] = { Vertex(Vector2f(size,smeshH + a * ((720 - 2 * smeshH) / OldN)),Color(0,0,0),Vector2f(size,smeshH + a * ((720 - 2 * smeshH) / OldN))) , Vertex(Vector2f(smeshH,smeshH + a * ((720 - 2 * smeshH) / OldN)),Color(0,0,0),Vector2f(smeshH,smeshH + a * ((720 - 2 * smeshH) / OldN))) };
				window.draw(testLineV, 2, Lines);
			}
			for (int i = 0; i < 40; i++)
			{
				for (int q = 0; q < 40; q++)
				{
					window.draw(Figures[40 * i + q]);
				}
			}

			window.draw(Title);
			window.draw(SettingsB.GetButton());
			window.draw(PlayB.GetButton());
			window.draw(StatsB.GetButton());
			window.draw(FastGameB.GetButton());
			window.draw(HintB.GetButton());
			window.draw(SettingsB.getText());
			window.draw(PlayB.getText());
			window.draw(StatsB.getText());
			window.draw(FastGameB.getText());
			window.draw(HintB.getText());
			window.draw(Copyright);
			window.draw(CorrecterB.GetButton());
			window.draw(CorrecterB.getText());

			if (!WasMousePressed) {
				if (CorrecterB.CheckPress() || ((Keyboard::isKeyPressed(Keyboard::LControl)) &&
					((Keyboard::isKeyPressed(Keyboard::R))))) {
					WindowType = 7;
					for (int i = 0; i < 3; i++)
					{
						for (int a = 0; a < 3; a++)
						{
							OldFig[i][a] = Fig[i][a];
						}
					}
				}
				if (HintB.CheckPress()) {

					system("start readme.txt");

				}
				if (FastGameB.CheckPress() || ((Keyboard::isKeyPressed(Keyboard::LControl)) &&
					((Keyboard::isKeyPressed(Keyboard::F))))) {
					window.clear();
					WindowType = 5;
					window.display();
				}
				Cause.setString(L"");
				if (PlayB.CheckPress() || ((Keyboard::isKeyPressed(Keyboard::LControl)) &&
					((Keyboard::isKeyPressed(Keyboard::G))))) {
					if (!(Name1 == Casual) || !(Name2 == Casual)) {
						OldN = n;
						z = 0;

						window.clear();
						WindowType = 1;
						window.display();
						HasStarted = false;

					}
					else {
						resW = WarningE(L"Вы не выбрали игроков!", L"Использовать стандартных", L"Выбрать других");
						if (resW == 1) {
							WindowType = 3;
							window.clear();
						}
						else {
							if (resW == 0) {
								OldN = n;
								z = 0;
								window.clear();
								WindowType = 1;
								window.display();
							}

						}
					}

				}
				if (StatsB.CheckPress() || ((Keyboard::isKeyPressed(Keyboard::LControl)) &&
					((Keyboard::isKeyPressed(Keyboard::S))))) {

					window.clear();
					WindowType = 4;
					window.display();
				}
				if (SettingsB.CheckPress() || ((Keyboard::isKeyPressed(Keyboard::LControl)) &&
					((Keyboard::isKeyPressed(Keyboard::N))))) {

					window.clear();
					WindowType = 3;
					HasSeted = false;
					window.display();
				}

			}
			break;
		case 1:

			if (!HasStarted) {
				if (!IsFastGame) {
					Cause.setString(L"");
				}

				for (int i = 0; i < 40; i++)
				{
					for (int q = 0; q < 40; q++)
					{
						Figures[40 * i + q] = DrawFigure(i + 1, q + 1, n, smeshH, Color(0, 0, 0, 0));
					}
				}
				z = 0;
				HasStarted = true;
				for (int c = 0; c < 100; c++) {


					for (int d = 0; d < 100; d++) {
						poses[c][d] = true;
					}
				}
				q = WhoIsStart;
				window.clear();
			}

			if (TestB.CheckPress() || (IsFastGame)) {
				if (!HasClicked || IsFastGame) {
					Done.close();

					Done1.open("result.txt", ios_base::out);

					Done1.close();
					HasClicked = true;
					window.clear();
					map.open("map.txt", ios_base::out);
					for (int i = 0; i < 3; i++)
					{
						for (int w = 0; w < 3; w++)
						{
							if (Fig[i][w]) {
								map << "1 ";
							}
							else
							{
								map << "0 ";
							}
						}
					}
					map << endl;
					map << n << endl;
					for (int c = 0; c < n; c++) {
						for (int d = 0; d < n; d++) {
							if (poses[c][d]) {
								map << "0 ";
							}
							else
							{
								map << "1 ";
							}
						}
					}
					map.close();
					result.close();

					MakeMove();
					if (TestK == "") {
						MakeMove();
					}

					result.open("result.txt", ios_base::in);
					result >> x1;
					result >> y1;
					rotation = 0;
					try
					{
						result >> rotation;
						rotation = rotation % 4;
					}

					catch (const std::exception&)
					{
						cout << "Player " + IntToStr(q) + " wrote some dich!";
						Log.open("Log.txt", ios_base::app);
						time(&nowT);
						Log << ctime(&nowT) << "Игрок " << q << " вывел не координаты!" << endl;

						Log.close();
					}

					result.close();
					Log.open("Log.txt", ios_base::app);
					time(&nowT);
					//Log << ctime(&nowT) << x1 << " " << y1 << " поворот: " << rotation << endl;
					Log.close();
					Done1.open("result.txt", ios_base::out);
					Done1.close();
					if ((x == atoi(x1.c_str())) && (y == atoi(y1.c_str()))) {
						std::cout << q << " не совершил хода!" << endl;

						prich = 0;
					}
					try
					{
						x = atoi(x1.c_str());
						y = atoi(y1.c_str());
					}
					catch (const std::exception&)
					{
						cout << "Player " + IntToStr(q) + " wrote some dich!";
						Log.open("Log.txt", ios_base::app);
						time(&nowT);
						Log << ctime(&nowT) << "Игрок " << q << " вывел не координаты!" << endl;
						Log.close();
					}

					if (prich != 0)
					{
						for (int i = -1; i < 2; i++)
						{
							for (int w = -1; w < 2; w++)
							{
								if (Fig[i + 1][w + 1]) {
									switch (rotation) {
									case 0:
									{
										if ((x + i > 0) && (y + w > 0) && (x + i < n + 1) && (y + w < n + 1)) {
											Figures[(x - 1 + i) * 40 + y + w - 1].setFillColor(FigureColor[q]);
										}
										break;
									}
									case 1:
									{
										if ((x - w > 0) && (y + i > 0) && (x - w < n + 1) && (y + i < n + 1)) {
											Figures[(x - 1 - w) * 40 + y + i - 1].setFillColor(FigureColor[q]);
										}
										break;
									}
									case 2:
									{
										if ((x - i > 0) && (y - w > 0) && (x - i < n + 1) && (y - w < n + 1)) {
											Figures[(x - 1 - i) * 40 + y - w - 1].setFillColor(FigureColor[q]);
										}
										break;
									}
									case 3:
									{
										if ((x + w > 0) && (y - i > 0) && (x + w < n + 1) && (y - i < n + 1)) {
											Figures[(x - 1 + w) * 40 + y - i - 1].setFillColor(FigureColor[q]);
										}
										break;
									}
									default:
									{
										if ((x + i > 0) && (y + w > 0) && (x + i < n + 1) && (y + w < n + 1)) {
											Figures[(x - 1 + i) * 40 + y + w - 1].setFillColor(FigureColor[q]);
										}
										break;
									}
									}

								}

							}
						}
					}

					if (CheckEnd(Vector2i(x, y), n, poses, rotation)) {

						SetPoses(x, y, rotation);

						if (!LastWins) {
							if (CheckLastMove(n, poses)) {

								lose();
								Cause.setString(IntToStr(2 - q) + L"-й совершил последний ход");
							}
							else
							{
								z++;
								q = 1 - q;
							}
						}
						else
						{
							if (CheckLastMove(n, poses)) {
								lose(1 - q);
								Win(q);
								Cause.setString(IntToStr(1 + q) + L"-й совершил последний ход");
							}
							else {
								z++;
								q = 1 - q;
							}

						}

					}
					else
					{
						lose();
					}
				}
			}
			else
			{
				HasClicked = false;
			}
			window.draw(Start);
			window.draw(Copyright);
			ScoreT.setString(L"Счет: " + IntToStr(win1) + ":" + IntToStr(win2));
			window.draw(ScoreT);
			for (int a = 0; a <= n; a++) {
				int size = n * int((720 - 2 * smeshH) / n) + smeshH;
				Vertex testLineH[] = { Vertex(Vector2f(smeshH + a * ((720 - 2 * smeshH) / n),size),Color(0,0,0),Vector2f(smeshH + a * ((720 - 2 * smeshH) / n),size)) , Vertex(Vector2f(smeshH + a * ((720 - 2 * smeshH) / n),smeshH),Color(0,0,0),Vector2f(smeshH + a * ((720 - 2 * smeshH) / n),smeshH)) };
				window.draw(testLineH, 2, Lines);
				Vertex testLineV[] = { Vertex(Vector2f(size,smeshH + a * ((720 - 2 * smeshH) / n)),Color(0,0,0),Vector2f(size,smeshH + a * ((720 - 2 * smeshH) / n))) , Vertex(Vector2f(smeshH,smeshH + a * ((720 - 2 * smeshH) / n)),Color(0,0,0),Vector2f(smeshH,smeshH + a * ((720 - 2 * smeshH) / n))) };
				window.draw(testLineV, 2, Lines);
			}

			for (int i = 0; i < 40; i++)
			{
				for (int q = 0; q < 40; q++)
				{
					window.draw(Figures[40 * i + q]);
				}
			}
			window.draw(MenuB.GetButton());
			window.draw(Cause);
			window.draw(MenuB.getText());
			if (!WasMousePressed) {
				if (MenuB.CheckPress() || ((Keyboard::isKeyPressed(Keyboard::LControl)) &&
					((Keyboard::isKeyPressed(Keyboard::M))))) {
					window.clear();
					WindowType = 0;
					IsFastGame = false;
					for (int c = 0; c < 100; c++) {

						for (int d = 0; d < 100; d++) {
							if (c * 100 + d < 1600) {
								Figures[c * 100 + d].setFillColor(Color(0, 0, 0, 0));

							}
							poses[c][d] = true;
						}
					}
					window.display();
				}
			}

			if (!IsFastGame) {
				window.draw(TestB.GetButton());
				window.draw(TestB.getText());
			}

			break;
		case 2:
			window.draw(Start);

			window.draw(Copyright);
			window.draw(MenuB.GetButton());
			window.draw(MenuB.getText());
			if (HasEnded) {
				if (q == 0) {
					WinT.loadFromFile("Data\\Win0.png");
					win1++;
				}
				else
				{
					WinT.loadFromFile("Data\\Win1.png");
					win2++;
				}

				HasEnded = false;
			}
			WinS.setTexture(WinT);
			WinS.setScale(0.7, 0.7);
			WinS.setPosition((int)(W / 2 - (WinT.getSize().x / 2) * WinS.getScale().x), (int)(H / 2 - (WinT.getSize().y / 2) * WinS.getScale().y));
			window.draw(WinS);
			if (!WasMousePressed) {
				if (MenuB.CheckPress() || ((Keyboard::isKeyPressed(Keyboard::LControl)) &&
					((Keyboard::isKeyPressed(Keyboard::M))))) {
					window.clear();
					WindowType = 0;
					window.display();
				}
			}
			if (IsFastGame) {
				if (Games > 0) {
					WindowType = 1;
					Games--;

				}
				else
				{
					IsFastGame = false;
					window.clear();
					WindowType = 4;
					window.display();
				}
			}
			break;
		case 3:

			window.clear();
			window.draw(Start);
			window.draw(Copyright);
			if (!HasSeted) {


				HasSeted = true;
			}
			if (LastWins) {
				window.draw(TickOnB.GetButton());
			}
			else
			{
				window.draw(TickOffB.GetButton());
			}

			n = NumOfRect.getValue((Vector2i)window.getPosition()) + 5;
			window.draw(WayToBot.getTextField());
			window.draw(WayToBot.getText());
			window.draw(ApplyLink1.GetButton());
			window.draw(ApplyLink1.getText());
			window.draw(ApplyLink2.GetButton());
			window.draw(ApplyLink2.getText());
			window.draw(WayToBot.getCursor());
			WayToBot.updateDATA((Vector2i)window.getPosition());
			WayToBot1.updateDATA((Vector2i)window.getPosition());
			WaitTime.updateDATA((Vector2i)window.getPosition());
			if (WayToBot.WasEntered || (ApplyLink1.CheckPress())) {

				if (isEXEfile(WayToBot.getString())) {
					Return1 = WayToBot.getString();
					Settings1.open("Data\\Settings.ini", ios_base::out);
					Settings1 << WayToBot.getString();
					Settings1 << " ";
					Settings1 << Return2;
					Settings1.close();
					Name1.resize(Return1.size() - GetWay(Return1).size());
					for (int i = GetWay(Return1).size(); i < Return1.size(); i++) {
						Name1[i - GetWay(Return1).size()] = Return1[i];
					}
				}
				else
				{
					WayToBot.setString(Return1);
					std::cout << "This is not link to .exe file" << endl;
				}

			}

			window.draw(LastWinsT);
			window.draw(WayToBot1.getTextField());
			window.draw(WayToBot1.getText());
			window.draw(WayToBot1.getCursor());
			window.draw(WaitTimeT);
			window.draw(Link1T);
			window.draw(Link2T);
			window.draw(ApplyTimer.GetButton());
			window.draw(ApplyTimer.getText());

			window.draw(NumOfGamesT);
			window.draw(WaitTime.getTextField());
			window.draw(WaitTime.getText());
			window.draw(WaitTime.getCursor());
			if (WaitTime.WasEntered || ApplyTimer.CheckPress()) {
				WTime = atoi(WaitTime.getString().c_str());
			}
			if (WayToBot1.WasEntered || (ApplyLink2.CheckPress())) {
				if (isEXEfile(WayToBot1.getString())) {
					Return2 = WayToBot1.getString();
					Settings1.open("Data\\Settings.ini", ios_base::out);
					Settings1 << Return1;
					Settings1 << " ";
					Settings1 << WayToBot1.getString();
					Settings1.close();
					Name2.resize(Return2.size() - GetWay(Return2).size());
					for (int i = GetWay(Return2).size(); i < Return2.size(); i++) {
						Name2[i - GetWay(Return2).size()] = Return2[i];
					}
				}
				else
				{
					WayToBot1.setString(Return2);
					std::cout << "This is not link to .exe file" << endl;
				}
			}
			window.draw(NumOfRect.getLine());
			window.draw(NumOfRect.getScroller((Vector2i)window.getPosition()));

			if (!WasMousePressed) {
				if (TickOnB.CheckPress()) {
					LastWins = !LastWins;
				}

				if (MenuB.CheckPress() || ((Keyboard::isKeyPressed(Keyboard::LControl)) &&
					((Keyboard::isKeyPressed(Keyboard::M))))) {

					WindowType = 0;
					for (int i = 0; i < 40; i++)
					{
						for (int j = 0; j < 40; j++)
						{
							Figures[40 * i + j] = DrawFigure(i + 1, j + 1, n, smeshH, Color(0, 0, 0, 0));
						}
					}

					if (isEXEfile(WayToBot1.getString())) {
						Return2 = WayToBot1.getString();
						Settings1.open("Data\\Settings.ini", ios_base::out);
						Settings1 << Return1;
						Settings1 << " ";
						Settings1 << WayToBot1.getString();
						Settings1.close();
						Name2.resize(Return2.size() - GetWay(Return2).size());
						for (int i = GetWay(Return2).size(); i < Return2.size(); i++) {
							Name2[i - GetWay(Return2).size()] = Return2[i];
						}
					}
					else
					{
						WindowType = 3;
						WayToBot1.setString(Return2);
						std::cout << "This is not link to .exe file" << endl;
					}
					if (isEXEfile(WayToBot.getString())) {
						Return1 = WayToBot.getString();
						Settings1.open("Data\\Settings.ini", ios_base::out);
						Settings1 << WayToBot.getString();
						Settings1 << " ";
						Settings1 << Return2;
						Settings1.close();
						Name1.resize(Return1.size() - GetWay(Return1).size());
						for (int i = GetWay(Return1).size(); i < Return1.size(); i++) {
							Name1[i - GetWay(Return1).size()] = Return1[i];
						}
					}
					else
					{
						WindowType = 3;
						WayToBot.setString(Return1);
						std::cout << "This is not link to .exe file" << endl;
					}

				}
				if (ClearStatsB.CheckPress()) {
					win1 = 0;
					win2 = 0;
					Stats1.open("Data\\Stats.txt", ios_base::out);
					Stats1 << IntToStr(win1) << " " << IntToStr(win2);
					Stats1.close();
					Log.open("Log.txt", ios_base::out);
					Log.close();

					IsCleared = true;
					SomeText.setPosition(Vector2f(700, 120));
					SomeText.setString(L"Статистика очищена");
					window.draw(SomeText);
					cleanTimer = 255;
					SomeText.setFillColor(Color(0, 0, 0, cleanTimer));

				}
			}

			if (IsCleared) {
				cleanTimer -= 5;
				if (cleanTimer <= 0) {
					IsCleared = false;
					cleanTimer = 0;
				}

				SomeText.setFillColor(Color(0, 0, 0, cleanTimer));
				window.draw(SomeText);

			}
			NumOfRectText.setString(IntToStr(NumOfRect.getValue((Vector2i)window.getPosition()) + 5));
			window.draw(MenuB.GetButton());
			window.draw(MenuB.getText());
			window.draw(NumOfRectText);
			window.draw(ClearStatsB.GetButton());
			window.draw(ClearStatsB.getText());
			for (int a = 0; a <= n; a++) {
				int size = n * int((720 - 2 * smeshH) / n) + smeshH;
				Vertex testLineH[] = { Vertex(Vector2f(smeshH + a * ((720 - 2 * smeshH) / n),size),Color(0,0,0),Vector2f(smeshH + a * ((720 - 2 * smeshH) / n),size)) , Vertex(Vector2f(smeshH + a * ((720 - 2 * smeshH) / n),smeshH),Color(0,0,0),Vector2f(smeshH + a * ((720 - 2 * smeshH) / n),smeshH)) };
				window.draw(testLineH, 2, Lines);
				Vertex testLineV[] = { Vertex(Vector2f(size,smeshH + a * ((720 - 2 * smeshH) / n)),Color(0,0,0),Vector2f(size,smeshH + a * ((720 - 2 * smeshH) / n))) , Vertex(Vector2f(smeshH,smeshH + a * ((720 - 2 * smeshH) / n)),Color(0,0,0),Vector2f(smeshH,smeshH + a * ((720 - 2 * smeshH) / n))) };
				window.draw(testLineV, 2, Lines);
			}

			break;
		case 4:
			window.draw(Start);
			window.draw(Copyright);
			if (!WasMousePressed) {
				if (MenuB.CheckPress() || ((Keyboard::isKeyPressed(Keyboard::LControl)) &&
					((Keyboard::isKeyPressed(Keyboard::M))))) {

					WindowType = 0;

				}
			}
			if (win1 + win2 != 0) {
				SomeText.setPosition(Vector2f(50, 320));
				SomeText.setFillColor(FigureColor[0]);
				SomeText.setString(Name1 + " " + IntToStr((int)round(1000 * (float)win1 / (win1 + win2)) / 10) + '.' + IntToStr(round(1000 * (float)win1 / (win1 + win2)) - ((int)round(1000 * (float)win1 / (win1 + win2)) / 10) * 10) + L" процентов побед");

				SomeText1.setPosition(Vector2f(50, 470));
				SomeText1.setString(Name2 + " " + IntToStr((int)round(1000 * (float)win2 / (win1 + win2)) / 10) + '.' + IntToStr(round(1000 * (float)win2 / (win1 + win2)) - ((int)round(1000 * (float)win2 / (win1 + win2)) / 10) * 10) + L" процентов побед");


				window.draw(SomeText1);
				window.draw(SomeText);
			}
			SomeText2.setPosition(Vector2f(50, 130));
			SomeText2.setString(L"Проведено игр : " + IntToStr(win1 + win2));
			window.draw(MenuB.GetButton());
			window.draw(MenuB.getText());
			window.draw(SomeText2);
			break;

		case 5:
			window.clear();
			window.draw(Start);
			window.draw(Copyright);
			NumOfGamesText.setString(IntToStr(round(pow(10, (float)NumOfGames.getValue((Vector2i)window.getPosition()) / 2500))));
			window.draw(NumOfGamesText);
			window.draw(NumOfGames.getLine());
			window.draw(NumOfGames.getScroller((Vector2i)window.getPosition()));
			window.draw(StartFastGameB.GetButton());
			window.draw(StartFastGameB.getText());
			window.draw(MenuB.GetButton());
			window.draw(MenuB.getText());
			window.draw(GamesT);
			if (!WasMousePressed) {
				if (MenuB.CheckPress() || ((Keyboard::isKeyPressed(Keyboard::LControl)) &&
					((Keyboard::isKeyPressed(Keyboard::M))))) {
					window.clear();
					WindowType = 0;
					window.display();
				}
				if (StartFastGameB.CheckPress()) {

					if (!(Name1 == Casual) || !(Name2 == Casual)) {
						window.clear();
						WindowType = 1;
						Games = round(pow(10, (float)NumOfGames.getValue((Vector2i)window.getPosition()) / 2500)) - 1;
						IsFastGame = true;
						z = 0;
						HasStarted = false;
						OldN = n;
						Cause.setString(L"");

						window.display();

						for (int c = 0; c < 100; c++) {


							for (int d = 0; d < 100; d++) {
								if (c * 40 + d < 1600) {
									Figures[c * 40 + d].setFillColor(Color(0, 0, 0, 0));
								}

								poses[c][d] = true;
							}
						}
						q = WhoIsStart;

					}
					else {
						resW = WarningE(L"Вы не выбрали игроков!", L"Использовать стандартных", L"Выбрать других");
						if (resW == 1) {
							WindowType = 3;
							window.clear();
						}
						else {
							if (resW == 0) {
								window.clear();
								WindowType = 1;
								Games = round(pow(10, (float)NumOfGames.getValue((Vector2i)window.getPosition()) / 2500)) - 1;
								IsFastGame = true;
								window.display();
							}

						}
					}
				}
			}
			break;
		case 6:

			window.draw(Start);
			window.draw(UnknownS);
			window.draw(Copyright);
			window.draw(Copyright);
			break;
		case 7:

			window.draw(Start);
			window.draw(Copyright);
			window.draw(MenuB.GetButton());
			window.draw(MenuB.getText());
			window.draw(OKCorB.GetButton());
			window.draw(OKCorB.getText());

			for (int i = 0; i < 3; i++)
			{
				for (int q = 0; q < 3; q++)
				{
					if (Fig[i][q]) {
						window.draw(ChF[i][q][0].GetButton());
					}
					else
					{
						window.draw(ChF[i][q][1].GetButton());
					}
				}
			}

			if (!WasMousePressed) {
				if (MenuB.CheckPress() || ((Keyboard::isKeyPressed(Keyboard::LControl)) &&
					((Keyboard::isKeyPressed(Keyboard::M))))) {
					if (!CheckZeroF()) {
						bool flag = true;
						for (int i = 0; i < 3; i++)
						{
							for (int j = 0; j < 3; j++)
							{
								if (Fig[i][j] != OldFig[i][j]) {
									flag = false;
								}
							}
						}
						if (!flag) {
							if (WarningE(L"Вы не сохранили изменения!", L"Остаться", L"Выти без сохранения") == 1) {
								for (int i = 0; i < 3; i++)
								{
									for (int a = 0; a < 3; a++)
									{
										Fig[i][a] = OldFig[i][a];
									}
								}
								window.clear();
								WindowType = 0;
								window.display();
							}

						}
						else
						{
							for (int i = 0; i < 3; i++)
							{
								for (int a = 0; a < 3; a++)
								{
									Fig[i][a] = OldFig[i][a];
								}
							}
							window.clear();
							WindowType = 0;
							window.display();
						}

					}

				}
				if (OKCorB.CheckPress())
				{
					for (int i = 0; i < 3; i++)
					{
						for (int a = 0; a < 3; a++)
						{
							OldFig[i][a] = Fig[i][a];
						}
					}
				}
				for (int i = 0; i < 3; i++)
				{
					for (int q = 0; q < 3; q++)
					{
						if (Fig[i][q]) {
							if (ChF[i][q][0].CheckPress()) {
								Fig[i][q] = false;
							}
						}
						else
						{
							if (ChF[i][q][1].CheckPress()) {
								Fig[i][q] = true;
							}
						}
					}
				}

			}

			break;
		default:
			break;
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			WasMousePressed = true;
		}
		else
		{
			WasMousePressed = false;
		}
		window.display();
		if (!IsFastGame && HasEnded && (WindowType == 2)) {
			Sleep(1000);
		}
	}
	map.close();

}
Vector2f SetFigure(int x, int y, int n, int smeshH, int num) {
	x = x - 1;
	y = y - 1;
	int size = int((720 - smeshH * 2) / n);
	Vector2f res = Vector2f(size * x + smeshH, size * y + smeshH);
	return(res);

}

ConvexShape DrawFigure(int x, int y, int n, int smeshH, Color FigureColor) {
	ConvexShape Figure;
	Figure.setPointCount(4);
	Figure.setPoint(0, Vector2f(SetFigure(x, y, n, smeshH, 0).x, SetFigure(x, y, n, smeshH, 0).y + 1));
	Figure.setPoint(1, Vector2f(SetFigure(x + 1, y, n, smeshH, 0).x - 1, SetFigure(x + 1, y, n, smeshH, 0).y + 1));
	Figure.setPoint(2, Vector2f(SetFigure(x + 1, y + 1, n, smeshH, 0).x - 1, SetFigure(x + 1, y + 1, n, smeshH, 0).y/* - 1*/));
	Figure.setPoint(3, Vector2f(SetFigure(x, y + 1, n, smeshH, 0).x, SetFigure(x, y + 1, n, smeshH, 0).y/* - 1*/));




	Figure.setFillColor(FigureColor);
	return (Figure);
}
bool CheckEnd(Vector2i coords, int n, bool closed[100][100], int rotation) {
	bool itog = true;

	itog = (coords.x < n + 1) && itog;
	itog = (coords.x > 0) && itog;
	itog = (coords.y < n + 1) && itog;
	itog = (coords.y > 0) && itog;
	if (!itog)
	{
		prich = 2;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int w = 0; w < 3; w++)
		{
			if (Fig[i][w])
			{
				switch (rotation) {
				case 0:
				{
					if ((coords.x + i - 1 > 0) && (coords.y + w - 1 > 0) && (coords.x + i - 1 < n + 1) && (coords.y + w - 1 < n + 1)) {
						itog = itog && closed[coords.x + i - 2][coords.y + w - 2];

					}
					else
					{
						itog = false;
					}
					break;
				}
				case 1:
				{
					if ((coords.x - w + 1 > 0) && (coords.y + i - 1 > 0) && (coords.x - w + 1 < n + 1) && (coords.y + i - 1 < n + 1)) {
						itog = itog && closed[coords.x - w][coords.y + i - 2];

					}
					else
					{
						itog = false;
					}
					break;
				}
				case 2:
				{
					if ((coords.x - i + 1 > 0) && (coords.y - w + 1 > 0) && (coords.x - i + 1 < n + 1) && (coords.y - w + 1 < n + 1)) {
						itog = itog && closed[coords.x - i][coords.y - w];

					}
					else
					{
						itog = false;
					}
					break;
				}
				case 3:
				{
					if ((coords.x + w - 1 > 0) && (coords.y - i + 1 > 0) && (coords.x + w - 1 < n + 1) && (coords.y - i + 1 < n + 1)) {
						itog = itog && closed[coords.x + w - 2][coords.y - i];

					}
					else
					{
						itog = false;
					}
					break;
				}
				default:
				{
					if ((coords.x + i - 1 > 0) && (coords.y + w - 1 > 0) && (coords.x + i - 1 < n + 1) && (coords.y + w - 1 < n + 1)) {
						itog = itog && closed[coords.x + i - 2][coords.y + w - 2];

					}
					else
					{
						itog = false;
					}
					break;
				}
				}

			}

		}
	}
	return(itog);
}

bool CheckLastMove(int n, bool closed[100][100]) {
	bool res1, res2, res3, res4 = true;

	int res = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			res1 = true;
			res2 = true;
			res3 = true;
			res4 = true;
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					if (Fig[k][l]) {
						if (((i + k - 1) < n) && (i + k - 1 >= 0) && (j + l - 1 < n) && (j + l - 1 >= 0))
						{
							res1 = res1 && closed[i + k - 1][j + l - 1];

						}
						else
						{
							res1 = false;
						}

						if (((i + l - 1) < n) && (i + l - 1 >= 0) && (j - k + 1 < n) && (j - k + 1 >= 0))
						{
							res2 = res2 && closed[i + l - 1][j - k + 1];
						}
						else
						{
							res2 = false;
						}

						if (((i - l + 1) < n) && (i - l + 1 >= 0) && (j + k - 1 < n) && (j + k - 1 >= 0))
						{
							res3 = res3 && closed[i - l + 1][j + k - 1];
						}
						else
						{
							res3 = false;
						}

						if (((i - k + 1) < n) && (i - k + 1 >= 0) && (j - l + 1 < n) && (j - l + 1 >= 0))
						{
							res4 = res4 && closed[i - k + 1][j - l + 1];
						}
						else
						{
							res4 = false;
						}

					}
				}

			}
			if (res1 || res2 || res3 || res4)
			{
				res++;
			}

		}
	}
	return(!(res > 0));
}


void Win(int num) {
	if (num == 1) {
		std::cout << "1st player won" << endl;
	}
	else
	{
		std::cout << "2nd player won" << endl;
	}
}
string IntToStr(int a) {
	int n = a;
	int x = 0;
	int y = 1;
	string Itog;
	while (n >= 1) {
		n /= 10;
		y *= 10;
		x++;
	}
	y /= 10;
	for (int c = 0; c < x; c++) {
		switch (a / y - (a / (y * 10) * 10))
		{

		case 0:
			Itog += "0";
			break;
		case 1:
			Itog += "1";
			break;
		case 2:
			Itog += "2";
			break;
		case 3:
			Itog += "3";
			break;
		case 4:
			Itog += "4";
			break;
		case 5:
			Itog += "5";
			break;
		case 6:
			Itog += "6";
			break;
		case 7:
			Itog += "7";
			break;
		case 8:
			Itog += "8";
			break;
		case 9:
			Itog += "9";
			break;

		default:

			break;
		}
		y /= 10;
	}
	if (a == 9120) {
		Itog = "10000";
	}
	if (a == 0) {
		Itog = "0";
	}
	return(Itog);
}

string GetWay(string fw) {
	int b = 0;
	int c = 0;
	for (int a = 0; a < fw.length() - 3; a++) {
		if (fw[a] == '.') {
			if (fw[a + 1] == 'e') {
				if (fw[a + 2] == 'x') {
					if (fw[a + 3] == 'e') {
						c = a;
						b = a;
						break;
					}
				}
			}
		}
	}
	for (int z = b; z > 0; z--) {
		if (fw[z] == '\\') {
			b = z;
			break;
		}
	}
	if (b == c) {
		b = -1;
	}
	string result = fw;
	result.resize(b + 1);
	return(result);
}
bool isEXEfile(string s) {
	int i = s.length() - 4;
	bool result = false;
	if (s[i] == '.') {
		if (s[i + 1] == 'e') {
			if (s[i + 2] == 'x') {
				if (s[i + 3] == 'e') {
					result = true;
				}
			}
		}
	}
	if (s[i] == '.') {
		if (s[i + 1] == 'b') {
			if (s[i + 2] == 'a') {
				if (s[i + 3] == 't') {
					result = true;
				}
			}
		}
	}
	if (s[i + 1] == '.') {
		if (s[i + 2] == 'p') {
			if (s[i + 3] == 'y') {
				result = true;
			}
		}
	}
	if (s[i] == '.') {
		if (s[i + 1] == 'j') {
			if (s[i + 2] == 'a') {
				if (s[i + 3] == 'r') {
					result = true;
				}
			}
		}
	}
	if (result == false) {
		int H = 400;
		int W = 200;
		RenderWindow exceptionW({ (unsigned int)H, (unsigned int)W }, "Error!", sf::Style::Close);
		exceptionW.setFramerateLimit(120);
		ConvexShape Start;
		Start.setPointCount(4);
		Start.setPoint(0, Vector2f(0, 0));
		Start.setPoint(1, Vector2f(0, W));
		Start.setPoint(2, Vector2f(H, W));
		Start.setPoint(3, Vector2f(H, 0));
		Start.setFillColor(Color(255, 0, 0));
		Font MyFont;

		MyFont.loadFromFile("Data\\Sh.otf");
		Text T;
		T.setFillColor(Color(255, 255, 255));
		T.setFont(MyFont);
		T.setCharacterSize(68);
		T.setPosition(Vector2f(20, 10));
		string S = "Wrong file name";

		T.setString(S);
		exceptionW.draw(Start);
		exceptionW.draw(T);
		exceptionW.display();
		Button OK;

		Texture AllT, AllTp;
		AllT.loadFromFile("Data\\Button1.png");
		AllTp.loadFromFile("Data\\Button1p.png");
		Sprite OKS;
		OK.set(Vector2f(120, 100), Vector2f(0.35, 0.35), Color(), AllT, AllTp, OKS, (Vector2f)exceptionW.getPosition(), L"OK", 40);
		while (exceptionW.isOpen())
		{
			Event event;
			while (exceptionW.pollEvent(event)) {
				if (event.type == Event::Closed) {
					exceptionW.clear();

					exceptionW.close();
				}
			}
			exceptionW.draw(Start);
			exceptionW.draw(T);
			exceptionW.draw(OK.GetButton());
			exceptionW.draw(OK.getText());
			exceptionW.display();
			if (OK.CheckPress()) {
				exceptionW.clear();

				exceptionW.close();
				break;
			}

		}

	}

	return (result);

}
bool CheckZeroF() {
	bool res = true;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << i << " " << j << endl;
			if (OldFig[i][j]) {
				res = false;
				break;
			}
		}
		if (!res)
		{
			break;
		}
	}

	if (res) {
		int width = 750;
		int height = 200;

		ConvexShape Start;
		Start.setPointCount(4);
		Start.setPoint(0, Vector2f(0, 0));
		Start.setPoint(1, Vector2f(0, height));
		Start.setPoint(2, Vector2f(width, height));
		Start.setPoint(3, Vector2f(width, 0));
		Start.setFillColor(Color(255, 230, 0));
		Font MyFont;

		MyFont.loadFromFile("Data\\Sh.otf");
		Text T;
		T.setFillColor(Color(0, 0, 0));
		T.setFont(MyFont);
		T.setCharacterSize(68);
		T.setPosition(Vector2f(20, 10));
		T.setString("You have not chosen any figure!");
		Texture AllT, AllTp;
		AllT.loadFromFile("Data\\Button1.png");
		AllTp.loadFromFile("Data\\Button1p.png");
		Button OK;
		Sprite OKS;
		RenderWindow WarningW({ (unsigned int)width, (unsigned int)height }, "Warning!", sf::Style::Close);
		WarningW.setFramerateLimit(120);
		OK.set(Vector2f(250, 100), Vector2f(0.5, 0.35), Color(), AllT, AllTp, OKS, (Vector2f)WarningW.getPosition(), L"OK", 40);
		while (WarningW.isOpen())
		{
			Event event;
			while (WarningW.pollEvent(event)) {
				if (event.type == Event::Closed) {
					WarningW.clear();

					WarningW.close();
				}
			}

			WarningW.draw(Start);
			WarningW.draw(OK.GetButton());

			WarningW.draw(OK.getText());

			if (OK.CheckPress()) {

				WarningW.clear();

				WarningW.close();
				break;
			}
			WarningW.draw(T);
			WarningW.display();
		}
	}
	return(res);
}
int WarningE(wstring W, wstring Op1, wstring Op2) {
	int res = -1;
	int width = 750;
	int height = 300;
	RenderWindow WarningW({ (unsigned int)width, (unsigned int)height }, "Warning!", sf::Style::Close);
	WarningW.setFramerateLimit(120);
	ConvexShape Start;
	Start.setPointCount(4);
	Start.setPoint(0, Vector2f(0, 0));
	Start.setPoint(1, Vector2f(0, height));
	Start.setPoint(2, Vector2f(width, height));
	Start.setPoint(3, Vector2f(width, 0));
	Start.setFillColor(Color(255, 230, 0));
	Font MyFont;

	MyFont.loadFromFile("Data\\Sh.otf");
	Text T;
	T.setFillColor(Color(0, 0, 0));
	T.setFont(MyFont);
	T.setCharacterSize(68);
	T.setPosition(Vector2f(20, 10));

	T.setString(W);

	Button OK, Cancel;

	Texture AllT, AllTp;
	AllT.loadFromFile("Data\\Button1.png");
	AllTp.loadFromFile("Data\\Button1p.png");
	Sprite OKS, CancelS;
	OK.set(Vector2f(143, 100), Vector2f(1, 0.35), Color(), AllT, AllTp, OKS, (Vector2f)WarningW.getPosition(), Op1, 40);
	Cancel.set(Vector2f(143, 200), Vector2f(1, 0.35), Color(), AllT, AllTp, CancelS, (Vector2f)WarningW.getPosition(), Op2, 40);
	while (WarningW.isOpen())
	{
		Event event;
		while (WarningW.pollEvent(event)) {
			if (event.type == Event::Closed) {
				WarningW.clear();

				WarningW.close();
			}
		}

		WarningW.draw(Start);
		WarningW.draw(OK.GetButton());
		WarningW.draw(Cancel.GetButton());
		WarningW.draw(OK.getText());
		WarningW.draw(Cancel.getText());
		if (OK.CheckPress()) {
			res = 0;
			WarningW.clear();

			WarningW.close();
			break;
		}
		if (Cancel.CheckPress()) {
			res = 1;
			WarningW.clear();

			WarningW.close();
			break;
		}
		WarningW.draw(T);
		WarningW.display();

	}

	return(res);
}

void MakeMove() {
	try
	{
		if (q == 0) {

			ShellExecute(NULL, NULL, (char*)(Return1).c_str(), NULL, NULL, SW_HIDE);

		}
		else
		{
			ShellExecute(NULL, NULL, (char*)(Return2).c_str(), NULL, NULL, SW_HIDE);

		}
	}
	catch (const std::exception&)
	{
		std::cout << "Invalid link to .exe bot file" << endl;
		WindowType = 3;

	}
	Done1.open("result.txt", ios_base::out);
	Done1.close();
	for (int i = 0; i < (int)round(WTime / 50); i++) {
		TestK = "";
		Done.open("result.txt");
		Done >> TestK;
		Done.close();
		if (TestK == "") {

			Sleep(50);

			continue;
		}
		else {

			break;
		}
	}
	try {
		string name, name1;
		if (q == 0) {
			name1.resize(Return1.size() - GetWay(Return1).size());
			for (int i = GetWay(Return1).size(); i < Return1.size(); i++) {
				name1[i - GetWay(Return1).size()] = Return1[i];
			}
		}
		else {
			name1.resize(Return2.size() - GetWay(Return2).size());
			for (int i = GetWay(Return2).size(); i < Return2.size(); i++) {
				name1[i - GetWay(Return2).size()] = Return2[i];
			}
		}

		name = "taskkill /IM " + name1 + " /f";

		const char* NAME = new char[name.size() + 1];
		NAME = name.c_str();
		system(NAME);

	}
	catch (exception E) {

	}

}

void SetPoses(int x, int y, int rotation) {
	for (int i = 0; i < 3; i++)
	{
		for (int q = 0; q < 3; q++)
		{
			if (Fig[i][q]) {
				switch (rotation) {
				case 0:
				{

					poses[x + i - 2][y + q - 2] = false;

					break;
				}
				case 1:
				{

					poses[x - q][y + i - 2] = false;

					break;
				}
				case 2:
				{

					poses[x - i][y - q] = false;

					break;
				}
				case 3:
				{
					poses[x + q - 2][y - i] = false;

					break;
				}
				default:
				{
					poses[x + i - 2][y + q - 2] = false;

					break;
				}
				}

			}
		}
	}
}

void lose() {
	Log.open("Log.txt", ios_base::app);
	time(&nowT);
	Log << ctime(&nowT) << "Победил игрок " << q << endl;
	Log << "Причина: ";
	if (prich == 0) {
		prich = 1;
		Log << "Игровой алгоритм не ответил" << endl;
		Cause.setString(IntToStr(1 + q) + L"-й не ответил");
	}
	else
	{
		if (prich == 1) {
			Log << "Игровой алгоритм задел занятую клетку" << endl;
			Cause.setString(IntToStr(1 + q) + L"-й сходил в занятую клетку");
		}
		else
		{
			if (prich == 2)
			{
				prich = 1;
				Log << "Игровой алгоритм вышел за пределы поля" << endl;
				Cause.setString(IntToStr(1 + q) + L"-й сходил вне поля");
			}
		}
	}
	Log << endl;
	Log.close();
	z++;
	q = 1 - q;
	Win(1 - q);
	WhoIsStart = 1 - WhoIsStart;
	if (!IsFastGame) {
		WindowType = 2;
	}
	else
	{
		if (q == 0) {

			win1++;
		}
		else
		{

			win2++;
		}
		if (Games == 0) {
			WindowType = 4;
			IsFastGame = false;
		}
		Games--;

	}


	OldN = n;
	HasEnded = true;
	HasStarted = false;
}

void lose(int f) {
	Log.open("Log.txt", ios_base::app);
	time(&nowT);
	Log << ctime(&nowT) << "Победил игрок " << f << endl;
	Log << "Причина: ";
	if (prich == 0) {
		prich = 1;
		Log << "Игровой алгоритм не ответил" << endl;
		Cause.setString(IntToStr(1 + f) + L"-й не ответил");
	}
	else
	{
		if (prich == 1) {
			Log << "Игровой алгоритм задел занятую клетку" << endl;
			Cause.setString(IntToStr(1 + f) + L"-й сходил в занятую клетку");
		}
		else
		{
			if (prich == 2)
			{
				prich = 1;
				Log << "Игровой алгоритм вышел за пределы поля" << endl;
				Cause.setString(IntToStr(1 + f) + L"-й сходил вне поля");
			}
		}
	}
	Log << endl;
	Log.close();
	z++;
	f = 1 - f;
	Win(1 - f);
	WhoIsStart = 1 - WhoIsStart;
	if (!IsFastGame) {
		WindowType = 2;
	}
	else
	{
		if (f == 0) {

			win1++;
		}
		else
		{

			win2++;
		}
		if (Games == 0) {
			WindowType = 4;
			IsFastGame = false;
		}
		Games--;

	}


	OldN = n;
	HasEnded = true;
	HasStarted = false;
}