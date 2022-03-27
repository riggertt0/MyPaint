#pragma once
#include "Show.h"

const int DEFAULT_LEN = 30;
const int DEFAULT_HEI = 30;
const int DEFAULT_BUTTON_HEI = 26;

class AbstractButton {
private:
	int x_;
	int y_;
	int length_;
	int height_;

	std::string path_img_;
	bool is_hide;
	bool change_pos;
public:
	bool mouse_on;

	void(*ActionBegin)(Uint32*, int, int, int, int, int, int, int, int, int, int, Uint32) = nullptr;
	void(*ActionEnd)(Uint32*, int, int, int, int, int, int, int, int, int, int, int, int, Uint32) = nullptr;
	void(*ActionUpdate)(Uint32*, int, int, int, int, int, int, int, int, int, int, int, int, Uint32) = nullptr;

	void(*ActionUpdateCreator)(Uint32*, int, int, int, int, int, int, int, int) = nullptr;
	void(*ActionEndCreator)(AbstractButton* , int , int , int , int , Uint32* ) = nullptr;

	bool using_ = false;

	AbstractButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "") {
		x_ = x;
		y_ = y;
		length_ = length;
		height_ = height;
		path_img_ = path_img;
		mouse_on = false;
		is_hide = false;
		change_pos = false;
	}

	void MouseOn() {
		int x = 0;
		int y = 0;
		SDL_GetGlobalMouseState(&x, &y);
		mouse_on = (x - X_START_WINDOW >= x_ &&
			x - X_START_WINDOW <= x_ + length_ &&
			y - Y_START_WINDOW >= y_ &&
			y - Y_START_WINDOW <= y_ + height_);
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
		return false;
	}
	virtual void Use() {
		std::cout << "function is not assigned";
	}

	virtual void NoUse() {
		//std::cout << "NOfunction is not assigned";
	}

	void TailShow() {
		SDL_Surface* surface = IMG_Load(path_img_.c_str());
		if (!surface) {
			std::cout << "Failed to create surface ";
			std::cout << path_img_ << '\n';
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
		if (!texture) {
			std::cout << "Failed to create texture\n";
		}
		SDL_FreeSurface(surface);
		SDL_Rect rect = { x_, y_, length_, height_ };
		if (texture) {
			SDL_RenderCopy(ren, texture, nullptr, &rect);
		}
		SDL_DestroyTexture(texture);
	}
	virtual void Show() {
		TailShow();
		if (using_)
			ShowFrame();
	}
	void Exit() {
		is_hide = true;
	}
	int GetX() { return x_; }
	int GetY() { return y_; }
	int GetLen() { return length_; }
	int GetHei() { return height_; }
	std::string GetStr() { return path_img_; }
	bool IsHide() {
		return is_hide;
	}
	void DoHide() {
		is_hide = true;
	}
	void DoNoHide() {
		is_hide = false;
	}
	void ChangeHide() { is_hide = !is_hide; }
	void SetX(int x) { x_ = x; }
	void SetY(int y) { y_ = y; }
	void SetLen(int len) { length_ = len; }
	void SetHei(int hei) { height_ = hei; }
	void SetImg(std::string path_img) { path_img_ = path_img; }
	bool IsChangePos() { return change_pos; }
	void DoChangePos() { change_pos = true; }
	void StopChangePos() { change_pos = false; }

	void ShowFrame() {
		SetColor({ 200,50,50 });
		ShowRect(x_, y_, length_, height_);
		SetColor({ 0,0,0 });
	}
};

class Brush {
private:
	ColorRGB color_;
	int size_max;
	int size_min;
	int size;
public:
	Brush(ColorRGB color = { 0,0,0 }) {
		color_ = color;
		size_max = 9;
		size_min = 1;
		size = 5;
	}
	
	void SizeIncrease() { size = std::min(size_max, ++size); }
	void SizeDecrease() { size = std::max(size_min, --size); }
	void SetColor(ColorRGB color) {
		color_ = color;
	}
	ColorRGB GetColor() { return color_; }
	int GetSize() { return size; }
	SDL_Color GetColorSDL() { 
		SDL_Color color;
		color.r = (Uint8)(color_.GetR() * 255);
		color.g = (Uint8)(color_.GetG() * 255);
		color.b = (Uint8)(color_.GetB() * 255);
		return color;
	}

	AbstractButton* tool_builtin = nullptr;
	AbstractButton* tool_color = nullptr;
	AbstractButton* tool_out = nullptr;

	AbstractButton* tool_creator = nullptr;
	ITool* tool = nullptr;
};