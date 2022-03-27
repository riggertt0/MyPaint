#pragma once
#include "UIButtons.h"
#include "Text.h"

class HelpButton : public AbstractButton {
private:
	HelpWindow help_wind;
public:
	HelpButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "")
		: AbstractButton(x, y, length, height, path_img), help_wind(GetX(), GetY() + GetHei(), 400, 30, "Img/help_window.bmp") {}
	virtual void Use() {
		help_wind.ChangeHide();
		help_wind.Show();
	}
	virtual void Show() {
		TailShow();
		help_wind.Show();
	}
};

class FileButton : public AbstractButton {
public:
	FileButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "")
		: AbstractButton(x, y, length, height, path_img) {}
	virtual void Use() {
		std::cout << "File ";
	}
};

class ImageButton : public AbstractButton {
public:
	using AbstractButton::AbstractButton;
	virtual void Use() {
		std::cout << "Image ";
	}
};

class ColorButton : public AbstractButton {
private:
	ColorRGB color_;
	Brush* brush;
public:
	ColorButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", ColorRGB color = { 0,0,0 }, Brush* brush_ = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		color_ = color;
		brush = brush_;
	}
	virtual void Show() {
		SDL_Rect rect = { GetX(), GetY(), GetLen(), GetHei() };
		SetColor(color_);
		SDL_RenderFillRect(ren, &rect);
		if (using_) {
			ColorRGB inv_color = { 255,255,255 };
			inv_color -= color_;
			SetColor(inv_color);
			ShowRect(GetX(), GetY(), GetLen(), GetHei());
		}
		SetColor({ 0,0,0 });
	}
	virtual void Use() {
		brush->SetColor(color_);
		if (brush->tool_color) {
			brush->tool_color->using_ = false;
		}
		brush->tool_color = this;
		using_ = true;
	}
};

class UpButton : public AbstractButton {
private:
	Brush* brush;
public:
	UpButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", Brush* brush_ = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		brush = brush_;
	}
	virtual void Use() {
		brush->SizeIncrease();
	}
};

class DownButton : public AbstractButton {
private:
	Brush* brush;
public:
	DownButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", Brush* brush_ = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		brush = brush_;
	}
	virtual void Use() {
		brush->SizeDecrease();

		std::cout << ' ' << brush->GetSize() << ' ';
	}
};