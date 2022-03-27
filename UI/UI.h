#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include "ForDLL.h"
#include "Show.h"
#include "CustomButtons.h"
#include "CustomTexture.h"
#include "ButtonFunc.h"

typedef IKlass* (*iklass_factory)();

const double PART_WINDOW = 0.55;
const double PART_LENGHT = 0.35;
const double PART_INDENT_SIZE_WIND = 0.05;

const double PART_INDENT_COLOR_WIND = 0.2;
const double PART_BUTTON_COLOR_WIND = 0.6;

const int INDENT_PIX = 2;

class SizeWind : public AbstractWindow {
private:
	UpButton up_button;
	DownButton down_buttom;
	ValueWind value_wind;
	ValueButton value_button;
	Brush* brush;
public:
	SizeWind(int x = 0, int y = 0, int length = 0, int height = 0, Brush* brush_ = nullptr) :
		AbstractWindow(x, y, length, height),
		up_button(x + (int)(PART_WINDOW * length), y,
			(int)(length* PART_LENGHT), (int)(length* PART_LENGHT), "Img/up_button.bmp", brush_),

		down_buttom(x + (int)(PART_WINDOW * length), (int)(y + length * PART_LENGHT + PART_INDENT_SIZE_WIND),
			(int)(length* PART_LENGHT), (int)(length* PART_LENGHT), "Img/down_button.bmp", brush_),

		value_wind(x + (int)(PART_INDENT_SIZE_WIND * length), y, (int)(length * 0.5),
			(int)(length* (PART_LENGHT * 2 + PART_INDENT_SIZE_WIND)), "Img/bg_value.bmp") {
		brush = brush_;
		std::string str = "Img/";
		str += (char)(brush->GetSize() + INT_VALUE_0);
		str += ".bmp";
		value_button = { x + (int)(PART_INDENT_SIZE_WIND * length) + INDENT_PIX, y + INDENT_PIX,
			(int)(length * 0.5) - INDENT_PIX * 2, (int)(length * (PART_LENGHT * 2 + PART_INDENT_SIZE_WIND)) - INDENT_PIX * 2, str };
	}

	void Show() {
		if (!IsHide()) {
			up_button.Show();
			down_buttom.Show();
			value_wind.Show();
			value_button.Show();
		}
	}

	void UpdateEvent(SDL_Event* event) {
		if (!IsHide()) {
			up_button.UpdateEvent(event);
			down_buttom.UpdateEvent(event);
			std::string str = "Img/";
			str += (char)(brush->GetSize() + INT_VALUE_0);
			str += ".bmp";
			value_button.SetImg(str);
		}
	}
};

class PaintButton : public AbstractButton {
private:
	SizeWind* size_wind;
	Brush* brush;
public:
	PaintButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", SizeWind* wind = nullptr, Brush* brush_ = nullptr)
		: AbstractButton(x, y, length, height, path_img)  {
		size_wind = wind;
		brush = brush_;
		ActionBegin = ActionBeginPaint;
		ActionEnd = ActionEndPaint;
		ActionUpdate = ActionUpdatePaint;
	}

	virtual void Use() {
		if (brush->tool_builtin)
			brush->tool_builtin->using_ = false;
		if (brush->tool_out)
			brush->tool_out->using_ = false;
		if (brush->tool_creator)
			brush->tool_creator->using_ = false;
		using_ = true;
		brush->tool_builtin = this;
		brush->tool = nullptr;
		brush->tool_creator = nullptr;
		size_wind->DoNoHide();
		
	}
};

class RectButton : public AbstractButton {
private:
	SizeWind* size_wind;
	Brush* brush;
public:
	RectButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", SizeWind* wind = nullptr, Brush* brush_ = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		size_wind = wind;
		brush = brush_;
		ActionBegin = ActionBeginRect_Circle;
		ActionEnd = ActionEndRect;
		ActionUpdate = ActionUpdateRect;
	}
	virtual void Use() {
		if(brush->tool_builtin)
			brush->tool_builtin->using_ = false;
		if (brush->tool_out)
			brush->tool_out->using_ = false;
		if (brush->tool_creator)
			brush->tool_creator->using_ = false;
		using_ = true;
		brush->tool_builtin = this;
		brush->tool = nullptr;
		brush->tool_creator = nullptr;
		size_wind->DoHide();
	}
};

class FillRectButton : public AbstractButton {
private:
	SizeWind* size_wind;
	Brush* brush;
public:
	FillRectButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", SizeWind* wind = nullptr, Brush* brush_ = nullptr)
		: AbstractButton(x, y, length, height, path_img){
		size_wind = wind;
		brush = brush_;
		ActionBegin = ActionBeginRect_Circle;
		ActionEnd = ActionEndFillRect;
		ActionUpdate = ActionUpdateRect;
	}
	virtual void Use() {
		if (brush->tool_builtin)
			brush->tool_builtin->using_ = false;
		if (brush->tool_out)
			brush->tool_out->using_ = false;
		if (brush->tool_creator)
			brush->tool_creator->using_ = false;
		using_ = true;
		brush->tool_builtin = this;
		brush->tool = nullptr;
		brush->tool_creator = nullptr;
		size_wind->DoHide();
	}
};

class CircleButton : public AbstractButton {
private:
	SizeWind* size_wind;
	Brush* brush;
public:
	CircleButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", SizeWind* wind = nullptr, Brush* brush_ = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		size_wind = wind;
		brush = brush_;
		ActionBegin = ActionBeginRect_Circle;
		ActionEnd = ActionEndCirc;
		ActionUpdate = ActionUpdateCirc;
	}
	virtual void Use() {
		if (brush->tool_builtin)
			brush->tool_builtin->using_ = false;
		if (brush->tool_out)
			brush->tool_out->using_ = false;
		if (brush->tool_creator)
			brush->tool_creator->using_ = false;
		using_ = true;
		brush->tool_builtin = this;
		brush->tool = nullptr;
		brush->tool_creator = nullptr;
		size_wind->DoHide();
	}
};

class FillCircleButton : public AbstractButton {
private:
	SizeWind* size_wind;
	Brush* brush;
public:
	FillCircleButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", SizeWind* wind = nullptr, Brush* brush_ = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		size_wind = wind;
		brush = brush_;
		ActionBegin = ActionBeginRect_Circle;
		ActionEnd = ActionEndFillCirc; 
		ActionUpdate = ActionUpdateCirc;
	}
	virtual void Use() {
		if (brush->tool_builtin)
			brush->tool_builtin->using_ = false;
		if (brush->tool_out)
			brush->tool_out->using_ = false;
		if (brush->tool_creator)
			brush->tool_creator->using_ = false;
		using_ = true;
		brush->tool_builtin = this;
		brush->tool = nullptr;
		brush->tool_creator = nullptr;
		size_wind->DoHide();
	}
};

class LineButton : public AbstractButton {
private:
	SizeWind* size_wind;
	Brush* brush;
public:
	LineButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", SizeWind* wind = nullptr, Brush* brush_ = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		size_wind = wind;
		brush = brush_;
		ActionBegin = ActionBeginLine;
		ActionEnd = ActionEndLine;
		ActionUpdate = ActionUpdateLine;
	}
	virtual void Use() {
		if (brush->tool_builtin)
			brush->tool_builtin->using_ = false;
		if (brush->tool_out)
			brush->tool_out->using_ = false;
		if (brush->tool_creator)
			brush->tool_creator->using_ = false;
		using_ = true;
		brush->tool_builtin = this;
		brush->tool = nullptr;
		brush->tool_creator = nullptr;
		size_wind->DoNoHide();
	}
};

class FillButton : public AbstractButton {
private:
	SizeWind* size_wind;
	Brush* brush;
public:
	FillButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", SizeWind* wind = nullptr, Brush* brush_ = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		size_wind = wind;
		brush = brush_;
		ActionBegin = ActionBeginFill;
		ActionEnd = nullptr;
		ActionUpdate = nullptr;
	}
	virtual void Use() {
		if (brush->tool_builtin)
			brush->tool_builtin->using_ = false;
		if (brush->tool_out)
			brush->tool_out->using_ = false;
		if (brush->tool_creator)
			brush->tool_creator->using_ = false;
		using_ = true;
		brush->tool_builtin = this;
		brush->tool = nullptr;
		brush->tool_creator = nullptr;
		size_wind->DoHide();
	}
};

class ExcretionButton : public AbstractButton {
private:
	SizeWind* size_wind;
	Brush* brush;
public:
	

	ExcretionButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", SizeWind* wind = nullptr, Brush* brush_ = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		size_wind = wind;
		brush = brush_;
		ActionUpdateCreator = ActionUpdateExcretion;
		ActionEndCreator = ActionEndExcretion;
	}

	virtual void Use() {
		if (brush->tool_builtin)
			brush->tool_builtin->using_ = false;
		if (brush->tool_out)
			brush->tool_out->using_ = false;
		if (brush->tool_creator)
			brush->tool_creator->using_ = false;
		using_ = true;
		brush->tool_builtin = nullptr;
		brush->tool_creator = this;
		brush->tool = nullptr;
	}
};

class ColorWindow : public AbstractWindow {
private:
	std::string path_img_;
	ColorButton color_butR;
	ColorButton color_butG;
	ColorButton color_butB;
	ColorButton color_butBL;
	ColorButton color_butY;
	ColorButton color_butW;
	SizeWind size_wind;
	PaintButton paint_button;
	RectButton rect_button;
	FillRectButton fill_rect_button;
	CircleButton circle_button;
	FillCircleButton fill_circle_button;
	LineButton line_button;
	FillButton fill_button;
	ExcretionButton excr_button;
	std::vector<UserButton> user_buttons;
	Brush* brush;
	int free_x;
	int free_y;
	int defolt_len;
	int defolt_hei;
public:
	ColorWindow(int x = 0, int y = 0, int length = 0, int height = 0, std::string path_img = "", Brush* brush_ = nullptr)
		: AbstractWindow(x, y, length, height),
		color_butR(x + (int)(PART_INDENT_COLOR_WIND * length - 2), (int)(y + PART_INDENT_COLOR_WIND / 2 * height),
			(int)(length* PART_BUTTON_COLOR_WIND / 2), (int)(length* PART_BUTTON_COLOR_WIND / 2), "Img/framecolor_wind.bmp", { 255, 0, 0 }, brush_),

		color_butG(x + (int)((PART_INDENT_COLOR_WIND + PART_BUTTON_COLOR_WIND / 2) * length + 2), (int)(y + PART_INDENT_COLOR_WIND / 2 * height),
			(int)(length* PART_BUTTON_COLOR_WIND / 2), (int)(length* PART_BUTTON_COLOR_WIND / 2), "Img/framecolor_wind.bmp", { 0, 255, 0 }, brush_),

		color_butB(x + (int)(PART_INDENT_COLOR_WIND * length - 2), (int)(y + PART_INDENT_COLOR_WIND / 2 * height + length * PART_BUTTON_COLOR_WIND / 2 + 4),
			(int)(length* PART_BUTTON_COLOR_WIND / 2), (int)(length* PART_BUTTON_COLOR_WIND / 2), "Img/framecolor_wind.bmp", { 0, 0, 255 }, brush_),

		color_butY(x + (int)((PART_INDENT_COLOR_WIND + PART_BUTTON_COLOR_WIND / 2) * length + 2), (int)(y + PART_INDENT_COLOR_WIND / 2 * height + length * PART_BUTTON_COLOR_WIND / 2 + 4),
			(int)(length* PART_BUTTON_COLOR_WIND / 2), (int)(length* PART_BUTTON_COLOR_WIND / 2), "Img/framecolor_wind.bmp", { 255, 255, 0 }, brush_),

		color_butW(x + (int)(PART_INDENT_COLOR_WIND * length - 2), (int)(y + PART_INDENT_COLOR_WIND / 2 * height + (length * PART_BUTTON_COLOR_WIND / 2 + 4) * 2),
			(int)(length* PART_BUTTON_COLOR_WIND / 2), (int)(length* PART_BUTTON_COLOR_WIND / 2), "Img/framecolor_wind.bmp", { 255, 255, 255 }, brush_),

		color_butBL(x + (int)((PART_INDENT_COLOR_WIND + PART_BUTTON_COLOR_WIND / 2) * length + 2), (int)(y + PART_INDENT_COLOR_WIND / 2 * height + (length * PART_BUTTON_COLOR_WIND / 2 + 4) * 2),
			(int)(length* PART_BUTTON_COLOR_WIND / 2), (int)(length* PART_BUTTON_COLOR_WIND / 2), "Img/framecolor_wind.bmp", { 0, 0, 0 }, brush_),

		size_wind(x + (int)(PART_INDENT_COLOR_WIND / 2 * length), (int)(y + PART_INDENT_COLOR_WIND / 2 * height + (length * PART_BUTTON_COLOR_WIND / 2 + 4) * 3 + 10 + length * 0.5),
			(int)(length * 0.9), (int)(length * 0.9), brush_),

		paint_button(x + (int)(PART_INDENT_COLOR_WIND / 2 * length), (int)(y + PART_INDENT_COLOR_WIND / 2 * height + (length * PART_BUTTON_COLOR_WIND / 2 + 4) * 3 + 5),
			(int)(length * 0.8), (int)(length * 0.5), "Img/paint_button.bmp", &size_wind, brush_),

		rect_button(x + (int)((PART_INDENT_COLOR_WIND / 2 + 0.15) * length), (int)(y + PART_INDENT_COLOR_WIND / 2 * height + (length * PART_BUTTON_COLOR_WIND / 2 + 4) * 3 + 15 + length * 1.25),
			(int)(length * 0.55), (int)(length * 0.35), "Img/rect_button.bmp", &size_wind, brush_),

		fill_rect_button(x + (int)((PART_INDENT_COLOR_WIND / 2 + 0.15) * length), (int)(y + PART_INDENT_COLOR_WIND / 2 * height + (length * PART_BUTTON_COLOR_WIND / 2 + 4) * 3 + 20 + length * 1.7),
			(int)(length * 0.55), (int)(length * 0.35), "Img/fillrect_button.bmp", &size_wind, brush_),

		circle_button(x + (int)((PART_INDENT_COLOR_WIND / 2 + 0.15) * length), (int)(y + PART_INDENT_COLOR_WIND / 2 * height + (length * PART_BUTTON_COLOR_WIND / 2 + 4) * 3 + 25 + length * 2.15),
			(int)(length * 0.55), (int)(length * 0.35), "Img/circle_button.bmp", &size_wind, brush_),

		fill_circle_button(x + (int)((PART_INDENT_COLOR_WIND / 2 + 0.15) * length), (int)(y + PART_INDENT_COLOR_WIND / 2 * height + (length * PART_BUTTON_COLOR_WIND / 2 + 4) * 3 + 30 + length * 2.6),
			(int)(length * 0.55), (int)(length * 0.35), "Img/fillcircle_button.bmp", &size_wind, brush_),

		line_button(x + (int)((PART_INDENT_COLOR_WIND / 2 + 0.1) * length), (int)(y + PART_INDENT_COLOR_WIND / 2 * height + (length * PART_BUTTON_COLOR_WIND / 2 + 4) * 3 + 35 + length * 3.05),
			(int)(length * 0.65), (int)(length * 0.45), "Img/line_button.bmp", &size_wind, brush_),

		fill_button(x + (int)((PART_INDENT_COLOR_WIND / 2 + 0.1) * length), (int)(y + PART_INDENT_COLOR_WIND / 2 * height + (length * PART_BUTTON_COLOR_WIND / 2 + 4) * 3 + 40 + length * 3.5),
			(int)(length * 0.65), (int)(length * 0.45), "Img/fill_button.bmp", &size_wind, brush_),

		excr_button(x + (int)((PART_INDENT_COLOR_WIND / 2 + 0.1) * length), (int)(y + PART_INDENT_COLOR_WIND / 2 * height + (length * PART_BUTTON_COLOR_WIND / 2 + 4) * 3 + 45 + length * 3.95),
			(int)(length * 0.65), (int)(length * 0.5), "Img/excretion_button.bmp", &size_wind, brush_)
	{
		path_img_ = path_img;

		free_x = x + (int)((PART_INDENT_COLOR_WIND / 2 + 0.15) * length);
		free_y = (int)(y + PART_INDENT_COLOR_WIND / 2 * height + (length * PART_BUTTON_COLOR_WIND / 2 + 4) * 3 + 50 + length * 4.45);
		defolt_len = (int)(length * 0.55);
		defolt_hei = (int)(length * 0.35);
		brush = brush_;
	}

	UserButton* PlaceNewButton(ITool* tool, std::string path_img) {
		if (user_buttons.size() < 4) {
			UserButton new_button(free_x, free_y, defolt_len, defolt_hei, path_img.c_str(), brush, tool);
			user_buttons.push_back(new_button);
			free_y += (int)(GetLen() * 0.5);
			return &new_button;
		}
		return nullptr;
	}

	void Show() {
		SDL_Surface* surface = IMG_Load(path_img_.c_str());
		if (!surface) {
			std::cout << "Failed to create surface\n";
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
		if (!texture) {
			std::cout << "Failed to create texture\n";
		}
		SDL_FreeSurface(surface);
		SDL_Rect rect = { GetX(), GetY(), GetLen(), GetHei() };
		if (texture) {
			SDL_RenderCopy(ren, texture, nullptr, &rect);
		}
		SDL_DestroyTexture(texture);
		color_butR.Show();
		color_butG.Show();
		color_butB.Show();
		color_butY.Show();
		color_butBL.Show();
		color_butW.Show();
		size_wind.Show();
		paint_button.Show();
		rect_button.Show();
		fill_rect_button.Show();
		circle_button.Show();
		fill_circle_button.Show();
		line_button.Show();
		fill_button.Show();
		excr_button.Show();
		for (unsigned int i = 0; i < user_buttons.size(); i++) {
			user_buttons[i].Show();
		}
	}
	void UpdateEvent(SDL_Event* event) {
		color_butR.UpdateEvent(event);
		color_butG.UpdateEvent(event);
		color_butB.UpdateEvent(event);
		color_butY.UpdateEvent(event);
		color_butBL.UpdateEvent(event);
		color_butW.UpdateEvent(event);
		size_wind.UpdateEvent(event);
		paint_button.UpdateEvent(event);
		rect_button.UpdateEvent(event);
		fill_rect_button.UpdateEvent(event);
		circle_button.UpdateEvent(event);
		fill_circle_button.UpdateEvent(event);
		line_button.UpdateEvent(event);
		fill_button.UpdateEvent(event);
		excr_button.UpdateEvent(event);
		for (unsigned int i = 0; i < user_buttons.size(); i++) {
			user_buttons[i].UpdateEvent(event);
		}
	}
};

enum WheelMode {
	VERTICAL,
	HORIZONTAL,
	ZOOM,
};

enum HotkeyMode {
	STANDART,
	CANCELLATION,
};

class CustomWindow : public AbstractButton {
private:
	Uint32* tempPixels;
	Uint32* old_tempPixels = nullptr;
	SDL_Texture* pTexture;
	std::string path_img_;
	UpFrame up_frame;
	CloseButtonBut close_button;
	Brush* brush;
	int x_click = 0;
	int y_click = 0;
	bool click;
	double scale = 1;
	WheelMode wheel_mode = VERTICAL;
	HotkeyMode hotkey_mode = STANDART;
	SDL_Rect show_rect;
	SliderManagerVertical slider_manager_vert;
	SliderManagerHorizontal slider_manager_horiz;
	int cus_tex_x = 50;
	int cus_tex_y = 60;
	int cus_tex_len = 100;
	int cus_tex_hei = 150;
	CustomTexture custom_texture;

	int x_start_change = 0;
	int y_start_change =  0;

	SDL_Texture* myTexturePart;
public:
	CustomWindow(int x = 0, int y = 0, int length = 0, int height = 0, std::string path_img = "", Brush* brush_ = nullptr)
		: AbstractButton(x, y, length, height, path_img), up_frame(GetX(), GetY() - DEFAULT_BUTTON_HEI, GetLen() + 15, 26, "Img/bg_line.bmp", this),
		close_button(GetX() + GetLen() - 10, GetY() - 25, 25, 18, "Img/close_button.bmp", this),
		slider_manager_vert(GetX() + GetLen(), GetY() + 15, 15, GetHei() - 30, "Img/bgcolor_wind.bmp", scale),
		slider_manager_horiz(GetX() + 15, GetY() + GetHei(), GetLen() - 30, 15, "Img/bg_slider_horizontal.bmp", scale),
		custom_texture(GetX() + cus_tex_x, GetY() + cus_tex_y, cus_tex_len, cus_tex_hei, nullptr){
		path_img_ = path_img;
		brush = brush_;
		Uint32 Rmask, Gmask, Bmask, Amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Rmask = 0xff000000;
		Gmask = 0x00ff0000;
		Bmask = 0x0000ff00;
		Amask = 0x000000ff;
#else
		Rmask = 0x000000ff;
		Gmask = 0x0000ff00;
		Bmask = 0x00ff0000;
		Amask = 0xff000000;
#endif
		SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, GetLen(), GetHei(), 32, Rmask, Gmask, Bmask, Amask);
		pTexture = SDL_CreateTextureFromSurface(ren, tempSurface);
		SDL_FreeSurface(tempSurface);
		tempPixels = new Uint32[GetLen() * GetHei()];

		old_tempPixels = new Uint32[GetLen() * GetHei()];
		
		memset(tempPixels, ConvertColor({ 255,255,255 }), GetLen() * GetHei() * sizeof(Uint32));
		memset(old_tempPixels, ConvertColor({ 255,255,255 }), GetLen() * GetHei() * sizeof(Uint32));
		show_rect = { 0, 0, (int)(GetLen() / scale), (int)(GetHei() / scale) };
		click = false;
	}

	~CustomWindow() {
		SDL_DestroyTexture(pTexture);
		delete[] tempPixels;
		delete[] old_tempPixels;
	}
	
	void CopyTempPix(Uint32* InCopy, Uint32* FromCopy) {
		for (int i = 0; i < GetLen(); i++) {
			for (int j = 0; j < GetHei(); j++) {
				InCopy[i + j * GetLen()] = FromCopy[i + j * GetLen()];
			}
		}
	}

	void SwapTempPix(Uint32* InCopy, Uint32* FromCopy) {
		Uint32* SimpleTempPixels = new Uint32[GetLen() * GetHei()];
		for (int i = 0; i < GetLen(); i++) {
			for (int j = 0; j < GetHei(); j++) {
				SimpleTempPixels[i + j * GetLen()] = InCopy[i + j * GetLen()];
			}
		}

		for (int i = 0; i < GetLen(); i++) {
			for (int j = 0; j < GetHei(); j++) {
				InCopy[i + j * GetLen()] = FromCopy[i + j * GetLen()];
			}
		}

		for (int i = 0; i < GetLen(); i++) {
			for (int j = 0; j < GetHei(); j++) {
				FromCopy[i + j * GetLen()] = SimpleTempPixels[i + j * GetLen()];
			}
		}

		delete[] SimpleTempPixels;
	}

	virtual void Use() {
		if (!IsHide()) {
			SDL_GetGlobalMouseState(&x_click, &y_click);
			x_click -= X_START_WINDOW;
			y_click -= Y_START_WINDOW;
			Uint32 pixelColor = ConvertColor(brush->GetColorSDL());

			if (brush->tool_builtin) {
				if (brush->tool_builtin->ActionBegin) {
					custom_texture.DoHide();
					SetPartTexture();
					CopyTempPix(old_tempPixels, tempPixels);
					brush->tool_builtin->ActionBegin(tempPixels, x_click, y_click, GetLen(), GetHei(),
						GetX(), GetY(), show_rect.x, show_rect.y, (int)scale, brush->GetSize(), pixelColor);
				}
			}

			if (brush->tool) {
				custom_texture.DoHide();
				SetPartTexture();
				CopyTempPix(old_tempPixels, tempPixels);
				brush->tool->ActionBegin(tempPixels, x_click, y_click, GetLen(), GetHei(),
					GetX(), GetY(), show_rect.x, show_rect.y, (int)scale, brush->GetSize(), pixelColor);
			}

			if (brush->tool_creator) {
				custom_texture.DoHide();
				SetPartTexture();
				//brush->tool->ActionBegin(tempPixels, x_click, y_click, GetLen(), GetHei(),
				//	GetX(), GetY(), show_rect.x, show_rect.y, (int)scale, brush->GetSize(), pixelColor);
			}

			click = true;
			
			SDL_UpdateTexture(pTexture, NULL, tempPixels, GetHei() * sizeof(Uint32));
		}
	}

	virtual void NoUse() {
		if (click) {
			int x_start = x_click;
			int y_start = y_click;
			x_start += (int)(show_rect.x * scale);
			y_start += (int)(show_rect.y * scale);
			int x_finish = 0;
			int y_finish = 0;

			SDL_GetGlobalMouseState(&x_finish, &y_finish);

			x_finish -= X_START_WINDOW;
			y_finish -= Y_START_WINDOW;
			x_finish += (int)(show_rect.x * scale);
			y_finish += (int)(show_rect.y * scale);

			Uint32 pixelColor = ConvertColor(brush->GetColorSDL());
			if (brush->tool_builtin) {
				if (brush->tool_builtin->ActionEnd) {
					brush->tool_builtin->ActionEnd(tempPixels, x_start, y_start, x_finish, y_finish, GetLen(), GetHei(),
						GetX(), GetY(), show_rect.x, show_rect.y, (int)scale, brush->GetSize(), pixelColor);
				}
			}
			if (brush->tool) {
				brush->tool->ActionEnd(tempPixels, x_start, y_start, x_finish, y_finish, GetLen(), GetHei(),
					GetX(), GetY(), show_rect.x, show_rect.y, (int)scale, brush->GetSize(), pixelColor);
			}
			if (brush->tool_creator) {
				brush->tool_creator->ActionEndCreator(this, cus_tex_x, cus_tex_y, cus_tex_len, cus_tex_hei, nullptr);
				custom_texture.DoNoHide();
				Uint32* ParttempPixels;

				ParttempPixels = new Uint32[custom_texture.GetLen() * custom_texture.GetHei()];

				for (int i = custom_texture.GetX(); i < custom_texture.GetX() + custom_texture.GetLen(); i++) {
					for (int j = custom_texture.GetY() - GetY(); j < custom_texture.GetY() + custom_texture.GetHei() - GetY(); j++) {
						ParttempPixels[i - custom_texture.GetX() + custom_texture.GetLen() * (j - (custom_texture.GetY() - GetY()))] = tempPixels[i + j * GetLen()];
						
						tempPixels[i + j * GetLen()] = ConvertColor({ 255,255,255 });						
					}
				}

				custom_texture.SetPixels(ParttempPixels, cus_tex_hei);
				//custom_texture.SetAll(cus_tex_x + GetX(), cus_tex_y + GetY(), cus_tex_len, cus_tex_hei, ParttempPixels);
			}
			SDL_UpdateTexture(pTexture, NULL, tempPixels, GetHei() * sizeof(Uint32));
		}
		click = false;
	}
	
	void Update() {
		if (!IsHide()) {
			if (click) {
				int x_finish = 0;
				int y_finish = 0;
				SDL_GetGlobalMouseState(&x_finish, &y_finish);

				x_finish -= X_START_WINDOW;
				y_finish -= Y_START_WINDOW;
				x_finish = std::clamp(x_finish, GetX(), GetX() + GetLen() - 1);
				y_finish = std::clamp(y_finish, GetY(), GetY() + GetHei() - 1);

				Uint32 pixelColor = ConvertColor(brush->GetColorSDL());
				if (brush->tool_builtin) {
					if (brush->tool_builtin->ActionUpdate) {
						brush->tool_builtin->ActionUpdate(tempPixels, x_click, y_click, x_finish, y_finish, GetLen(), GetHei(),
							GetX(), GetY(), show_rect.x, show_rect.y, (int)scale, brush->GetSize(), pixelColor);
					}
				}
				if (brush->tool) {
					brush->tool->ActionUpdate(tempPixels, x_click, y_click, x_finish, y_finish, GetLen(), GetHei(),
						GetX(), GetY(), show_rect.x, show_rect.y, (int)scale, brush->GetSize(), pixelColor);
				}
				if (brush->tool_creator) {
					brush->tool_creator->ActionUpdateCreator(tempPixels, x_click, y_click, x_finish, y_finish, GetLen(), GetHei(),
						GetX(), GetY());
					cus_tex_x = x_click;
					cus_tex_y = y_click;
					cus_tex_len = x_finish - x_click;
					cus_tex_hei = y_finish - y_click;
				}

				SDL_UpdateTexture(pTexture, NULL, tempPixels, GetHei() * sizeof(Uint32));
			}
			slider_manager_vert.Update();
			show_rect.y = (int)(slider_manager_vert.GetSliderRelativePos() * 1.1);
			show_rect.y = std::clamp(show_rect.y, 0, GetHei() - show_rect.h);

			slider_manager_horiz.Update();
			show_rect.x = (int)(slider_manager_horiz.GetSliderRelativePos() * 1.1);
			show_rect.x = std::clamp(show_rect.x, 0, GetLen() - show_rect.w);
		}
		if (IsChangePos()) {
			int x = 0;
			int y = 0;

			SDL_GetGlobalMouseState(&x, &y);

			SetX(x - X_START_WINDOW - GetLen() / 2);
			SetY(y - Y_START_WINDOW + DEFAULT_BUTTON_HEI / 2);

			up_frame.SetX(GetX());
			up_frame.SetY(GetY() - DEFAULT_BUTTON_HEI);

			close_button.SetX(GetX() + GetLen() - 10);
			close_button.SetY(GetY() - 25);

			slider_manager_vert.Moving(GetX() + GetLen(), GetY());
			slider_manager_horiz.Moving(GetX() + 15, GetY() + GetHei());
			custom_texture.Moving(GetX() + cus_tex_x - x_start_change, GetY() + cus_tex_y - y_start_change, cus_tex_len, cus_tex_hei);
		}
		custom_texture.Update();
	}

	void SetPartTexture() {
		if (custom_texture.GetPixels()) {
			for (int i = custom_texture.GetX(); i < custom_texture.GetX() + custom_texture.GetLen(); i++) {
				for (int j = custom_texture.GetY() - GetY(); j < custom_texture.GetY() + custom_texture.GetHei() - GetY(); j++) {
					if (custom_texture.GetPixels())
						tempPixels[i + j * GetLen()] = custom_texture.GetPixels()[i - custom_texture.GetX() + custom_texture.GetLen() * (j - (custom_texture.GetY() - GetY()))];
				}
			}
			SDL_UpdateTexture(pTexture, NULL, tempPixels, GetHei() * sizeof(Uint32));
		}
		custom_texture.SetPixels(nullptr, 100);
	}

	virtual bool UpdateEvent(SDL_Event* event) {
		bool ok = false;
		if (!IsHide()) {
			MouseOn();
			if (mouse_on) {
				if (event) {
					if (custom_texture.UpdateEvent(event)) { }
					else {
						SetPartTexture();
					}
					if ((*event).button.button == SDL_BUTTON_LEFT) {
						if ((*event).type == SDL_MOUSEBUTTONDOWN)
						{
							if (eve) {
								Use();
								eve = false;
								ok = true;
							}
						}
					}
					if ((*event).type == SDL_KEYDOWN) {
						if ((*event).key.keysym.sym == SDLK_LSHIFT) {
							wheel_mode = HORIZONTAL;
						}
						if ((*event).key.keysym.sym == SDLK_LCTRL) {
							wheel_mode = ZOOM;
							hotkey_mode = CANCELLATION;
						}
						if ((*event).key.keysym.sym == SDLK_z) {
							if (hotkey_mode == CANCELLATION) {
								SwapTempPix(tempPixels, old_tempPixels);
								SDL_UpdateTexture(pTexture, NULL, tempPixels, GetHei() * sizeof(Uint32));
							}
						}
					}
					else if ((*event).type == SDL_KEYUP) {
						if ((*event).key.keysym.sym == SDLK_LSHIFT || (*event).key.keysym.sym == SDLK_LCTRL) {
							wheel_mode = VERTICAL;
							hotkey_mode = STANDART;
						}
					}
					if ((*event).type == SDL_MOUSEWHEEL)
					{
						if (wheel_mode == VERTICAL) {
							if ((*event).wheel.y > 0)
							{
								if (eve) {
									slider_manager_vert.UpClick()->Use();
									slider_manager_vert.UpClick()->NoUse();
									eve = false;
								}
							}
							else if ((*event).wheel.y < 0)
							{
								if (eve) {
									slider_manager_vert.DownClick()->Use();
									slider_manager_vert.DownClick()->NoUse();
									eve = false;
								}
							}
						}
						else if (wheel_mode == HORIZONTAL) {
							if ((*event).wheel.y > 0)
							{
								if (eve) {
									slider_manager_horiz.LeftClick()->Use();
									slider_manager_horiz.LeftClick()->NoUse();
									eve = false;
								}
							}
							else if ((*event).wheel.y < 0)
							{
								if (eve) {
									slider_manager_horiz.RightClick()->Use();
									slider_manager_horiz.RightClick()->NoUse();
									eve = false;
								}
							}
						}
						else if (wheel_mode == ZOOM) {
							if ((*event).wheel.y > 0)
							{
								if (eve) {
									scale *= 2;
									if (scale > 8) scale = 8;
									slider_manager_vert.ChangeSlider(scale);
									slider_manager_horiz.ChangeSlider(scale);
									show_rect.h = (int)(GetLen() / scale);
									show_rect.w = (int)(GetHei() / scale);
									eve = false;
								}
							}
							else if ((*event).wheel.y < 0)
							{
								if (eve) {
									scale /= 2;
									if (scale < 1) scale = 1;
									slider_manager_vert.ChangeSlider(scale);
									slider_manager_horiz.ChangeSlider(scale);
									show_rect.h = (int)(GetLen() / scale);
									show_rect.w = (int)(GetHei() / scale);
									eve = false;
								}
							}
						}
					}
				}
			}
			if (event) {
				if ((*event).button.button == SDL_BUTTON_LEFT) {
					if ((*event).type == SDL_MOUSEBUTTONUP) {
						if (eve) {
							NoUse();
						}
					}
				}
			}
			close_button.UpdateEvent(event);
			if (slider_manager_vert.UpdateEvent(event)) { ok = true; }
			if (slider_manager_horiz.UpdateEvent(event)) { ok = true; }
			if (up_frame.UpdateEvent(event)) { ok = true; }
			//if (custom_texture.UpdateEvent(event)) { ok = true; }
		}
		return ok;
	}

	virtual void Show() {
		if (!IsHide()) {
			TailShow();
			SDL_Rect rect = { GetX(), GetY(), GetLen(), GetHei() };
			SDL_RenderCopy(ren, pTexture, &show_rect, &rect);

			up_frame.Show();
			close_button.Show();
			slider_manager_vert.Show();
			slider_manager_horiz.Show();
			
			custom_texture.Show();
		}
	}

	void CreatExcretion(int x, int y, int len, int hei, Uint32* tempPixels) {
		cus_tex_x = x;
		cus_tex_y = y;
		cus_tex_len = len;
		cus_tex_hei = hei;
		custom_texture.SetAll(cus_tex_x, cus_tex_y, cus_tex_len, cus_tex_hei, tempPixels);
	}
};

void ActionEndExcretion(AbstractButton* cust_wind, int x, int y, int len, int hei, Uint32* tempPixels) {
	static_cast<CustomWindow*>(cust_wind)->CreatExcretion(x, y, len, hei, tempPixels);
}

class ButtonConectCustomWind : public AbstractButton {
private:
	CustomWindow** wind_;
	int numb_of_wind;
public:
	ButtonConectCustomWind(int x = 0, int y = 0, int length = 0, int height = 0, std::string path_img = "", CustomWindow** wind = nullptr, int numb = 0) : AbstractButton(x, y, length, height, path_img) {
		wind_ = wind;
		numb_of_wind = numb;
	}

	virtual void Use() {
		for (int i = 0; i < numb_of_wind; i++) {
			wind_[i]->DoNoHide();
		}
	}
};

class WindowWind : public AbstractButton {
private:
	std::string path_img_;
	bool is_hide;
	ButtonConectCustomWind button_custom_wind;
public:
	WindowWind(int x = 0, int y = 0, int length = 0, int height = 0, std::string path_img = "", CustomWindow** wind = nullptr, int numb = 0) :
		AbstractButton(x, y, length, height, path_img), button_custom_wind(x, y, length, height, "Img/show_button.bmp", wind, numb) {
		path_img_ = path_img;
		is_hide = true;
	}

	void Show() {
		if (!is_hide) {
			TailShow();
			button_custom_wind.Show();
		}
	}

	virtual bool UpdateEvent(SDL_Event* event) {
		bool ok = false;
		button_custom_wind.UpdateEvent(event);
		return ok;
	}

	void ChangeHide() { is_hide = !is_hide; }
};

class WindowButton : public AbstractButton {
private:
	WindowWind image_wind;
public:
	WindowButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", CustomWindow** wind = nullptr, int numb = 0)
		: AbstractButton(x, y, length, height, path_img), image_wind(GetX(), GetY() + GetHei(), 40, DEFAULT_BUTTON_HEI, "Img/bg_wind.bmp", wind, numb) {}
	virtual void Show() {
		TailShow();
		image_wind.Show();
	}

	virtual void Use() {
		image_wind.ChangeHide();
		image_wind.Show();
		std::cout << "Window ";
	}

	virtual bool UpdateEvent(SDL_Event* event) {
		MouseOn();
		if (mouse_on) {
			if (event) {
				if ((*event).button.button == SDL_BUTTON_LEFT) {
					if ((*event).type == SDL_MOUSEBUTTONDOWN)
					{
						if (eve) {
							Use();
							eve = false;
							return true;
						}
					}
					else if ((*event).type == SDL_MOUSEBUTTONUP) {
						if (eve) {
							NoUse();
						}
					}
				}
			}
		}
		image_wind.UpdateEvent(event);
		return false;
	}
};

class SinglePluginButton : public AbstractButton {
private:
	std::string button_text_;
	std::string plugin_path;
	Text text;
	ColorWindow* color_wind;
	CustomWindow* cust_wind;
	Brush* brush;
public:
	SinglePluginButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", std::string button_text = "", ColorWindow* color_window = nullptr, CustomWindow* cust_wind_ = nullptr, Brush* brush_ = nullptr)
		: AbstractButton(x, y, length, height, path_img), text(ren, "Text/arial.ttf", 16, button_text, { 150, 180, 180, 255 }) {

		plugin_path = button_text_ = button_text;
		button_text_.erase(0, 7);
		if (button_text_.size() > 21) {
			while (button_text_.size() != 21) {
				button_text_.pop_back();
			}
			button_text_.push_back('.');
			button_text_.push_back('.');
			button_text_.push_back('.');
		}
		color_wind = color_window;
		cust_wind = cust_wind_;
		brush = brush_;
	}
	virtual void Show() {
		text.display(GetX(), GetY(), ren);
	}
	virtual void Use() {
		UserButton* user_but = nullptr;
		std::wstring output(plugin_path.begin(), plugin_path.end());
		HMODULE hDLL = LoadLibrary(output.c_str());
		if (hDLL) {
			ITool* (*factory_func)() = ((ITool * (*)())GetProcAddress(hDLL, "create_tool"));
			ITool* instance = factory_func();

			IWidgetFactory* (*widget_func)() = ((IWidgetFactory * (*)())GetProcAddress(hDLL, "create_widget"));
			IWidgetFactory* widget_instance = widget_func();

			user_but = color_wind->PlaceNewButton(instance, widget_instance->GetPath());
		}
	}
};

class PluginWindow : public AbstractButton {
private:
	std::vector<SinglePluginButton> plugins_buttons;
public:
	PluginWindow(int x = 0, int y = 0, int length = 0, int height = 0, std::string path_img = "", std::vector<std::string>* plugins_names_ = nullptr, ColorWindow* color_window = nullptr, CustomWindow* cust_wind_ = nullptr, Brush* brush_ = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		if (plugins_names_) {
			SetHei(height * plugins_names_->size());
			for (unsigned int i = 0; i < plugins_names_->size(); i++) {
				SinglePluginButton plugin_button(GetX() + 5, GetY() + GetHei() / plugins_names_->size() * i + 5, GetLen(), GetHei() / plugins_names_->size(), "Img/framecolor_wind.bmp", (*plugins_names_)[i], color_window, cust_wind_, brush_);
				plugins_buttons.push_back(plugin_button);
			}

		}
		DoHide();
	}
	virtual void Show() {
		if (!IsHide()) {
			TailShow();

			for (unsigned int i = 0; i < plugins_buttons.size(); i++) {
				plugins_buttons[i].Show();
			}
		}
	}

	virtual bool UpdateEvent(SDL_Event* event) {
		for (unsigned int i = 0; i < plugins_buttons.size(); i++) {
			plugins_buttons[i].UpdateEvent(event);
		}
		return false;
	}
};

class PluginButton : public AbstractButton {
private:
	PluginWindow plugin_window;
public:
	PluginButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", std::vector<std::string>* plugins_names_ = nullptr, ColorWindow* color_window = nullptr, CustomWindow* cust_wind_ = nullptr, Brush* brush_ = nullptr)
		: AbstractButton(x, y, length, height, path_img), plugin_window(GetX(), GetY() + GetHei(), 200, 30, "Img/bg_wind.bmp", plugins_names_, color_window, cust_wind_, brush_) {}
	virtual void Use() {
		plugin_window.ChangeHide();
		plugin_window.Show();
	}
	virtual void Show() {
		TailShow();
		plugin_window.Show();
	}

	virtual bool UpdateEvent(SDL_Event* event) {
		MouseOn();
		if (mouse_on) {
			if (event) {
				if ((*event).button.button == SDL_BUTTON_LEFT) {
					if ((*event).type == SDL_MOUSEBUTTONDOWN)
					{
						if (eve) {
							Use();
							eve = false;
							return true;
						}
					}
					else if ((*event).type == SDL_MOUSEBUTTONUP) {
						if (eve) {
							NoUse();
						}
					}
				}
			}
		}
		if (!plugin_window.IsHide())
			plugin_window.UpdateEvent(event);
		return false;
	}
};

class MainWindow : public AbstractWindow {
private:
	CloseButton close_button{ SCREEN_WIDTH - 25, 0, 25, 18, "Img/close_button.bmp", this };
	SimpleButton simple_button{ SCREEN_WIDTH - 50, 0, 25,18, "Img/hide_button.bmp" };
	HelpButton help_button{ 135, 0, 55, DEFAULT_BUTTON_HEI, "Img/help_button.bmp" };
	FileButton file_button{ 0, 0, 45, DEFAULT_BUTTON_HEI, "Img/file_button.bmp" };
	ImageButton image_button{ 45,0,90, DEFAULT_BUTTON_HEI,"Img/image_button.bmp" };
	WindowButton window_button;
	ColorWindow color_wind;
	CustomWindow** custom_wind;
	CustomWindow custom_wind1;
	CustomWindow custom_wind2;
	PluginButton plagin_button;
	Brush brush{ { 0,0,0 } };

	CustomTexture texture{ 100, 100, 100, 100};
public:
	MainWindow(std::vector<std::string>* plugins_name_ = nullptr, int x = 0, int y = 0, int length = 0, int height = 0) :
		AbstractWindow(x, y, length, height), color_wind(45, 45, 45, 420, "Img/bgcolor_wind.bmp", &brush),
		custom_wind1(300, 100, 300, 300, "Img/bgcustom_wind.bmp", &brush),
		custom_wind2(700, 150, 200, 200, "Img/bgcustom_wind.bmp", &brush) {
		custom_wind = new CustomWindow * [2];

		custom_wind[0] = &custom_wind1;
		custom_wind[1] = &custom_wind2;
		window_button = { 190, 0, 45, DEFAULT_BUTTON_HEI, "Img/window_button.bmp", custom_wind , 2 };
		plagin_button = { 235, 0, 45, DEFAULT_BUTTON_HEI, "Img/plugin_button.bmp", plugins_name_, &color_wind, &custom_wind1, &brush };
	}
	void Show() {
		if (!IsHide()) {
			ShowLineSprite(0, 0, SCREEN_WIDTH, 0, "Img/bg_line.bmp");
			close_button.Show();
			simple_button.Show();
			file_button.Show();
			image_button.Show();
			help_button.Show();
			window_button.Show();

			color_wind.Show();
			if (custom_wind[0])
				custom_wind[0]->Show();
			if (custom_wind[1])
				custom_wind[1]->Show();

			plagin_button.Show();
			texture.Show();
		}
	}
	virtual void Exit() {
		DoHide();
	}

	void UpdateEvent(SDL_Event* event) {
		if (IsHide()) {
			exit(0);
		}
		plagin_button.UpdateEvent(event);
		custom_wind[1]->UpdateEvent(event);
		if (custom_wind[0]->UpdateEvent(event)) {
			CustomWindow* just = custom_wind[0];
			custom_wind[0] = custom_wind[1];
			custom_wind[1] = just;
		}
		close_button.UpdateEvent(event);
		simple_button.UpdateEvent(event);
		help_button.UpdateEvent(event);
		file_button.UpdateEvent(event);
		image_button.UpdateEvent(event);
		window_button.UpdateEvent(event);

		color_wind.UpdateEvent(event);
		texture.UpdateEvent(event);
	}

	void Update() {
		custom_wind[1]->Update();
		custom_wind[0]->Update();
		texture.Update();
	}
};