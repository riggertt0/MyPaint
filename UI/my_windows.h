#pragma once
#include "Brush.h"

class AbstractWindow {
private:
	int x_;
	int y_;
	int length_;
	int height_;
	bool is_hide;
public:
	AbstractWindow(int x = 0, int y = 0, int length = 0, int height = 0) {
		x_ = x;
		y_ = y;
		length_ = length;
		height_ = height;
		is_hide = false;
	}
	virtual void Exit() {
		std::cout << "exit";
	}
	bool IsHide() {
		return is_hide;
	}
	void DoHide() {
		is_hide = true;
	}
	void DoNoHide() {
		is_hide = false;
	}
	int GetX() { return x_; }
	int GetY() { return y_; }
	int GetLen() { return length_; }
	int GetHei() { return height_; }
	void SetHei(int new_hei) { height_ = new_hei; }
	void SetHide(bool ok) { is_hide = ok; }
	bool GetHide() { return is_hide; }
};

class HelpWindow : public AbstractWindow {
private:
	std::string path_img_;
public:
	HelpWindow(int x = 0, int y = 0, int length = 0, int height = 0, std::string path_img = "")
		: AbstractWindow(x, y, length, height) {
		path_img_ = path_img;
		SetHide(true);
	}
	void Show() {
		if (!GetHide()) {
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
		}
	}
	void ChangeHide() { SetHide(!GetHide()); }
};