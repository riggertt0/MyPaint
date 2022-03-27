#pragma once
#include "my_windows.h"

class SimpleButton : public AbstractButton {
public:
	using AbstractButton::AbstractButton;
	virtual void Use() {
		std::cout << "Simple ";
	}
};

class CloseButton : public AbstractButton {
private:
	AbstractWindow* parent_;
public:
	CloseButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", AbstractWindow* parent = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		parent_ = parent;
	}
	virtual void Use() {
		if (parent_) {
			parent_->Exit();
		}
		else
			std::cout << "an attempt to close an object by a null pointer";
	}
};

class CloseButtonBut : public AbstractButton {
private:
	AbstractButton* parent_;
public:
	CloseButtonBut(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", AbstractButton* parent = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		parent_ = parent;
	}
	virtual void Use() {
		if (parent_) {
			parent_->Exit();
		}
		else
			std::cout << "an attempt to close an object by a null pointer";
	}
};

class UpFrame : public AbstractButton {
private:
	AbstractButton* parent;
public:
	UpFrame(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", AbstractButton* parent_ = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		parent = parent_;
	}
	virtual void Show() {
		ShowLineSprite(GetX(), GetY(), GetX() + GetLen(), GetY() + GetHei(), GetStr());
	}
	virtual void Use() {
		parent->DoChangePos();
	}
	virtual void NoUse() {
		parent->StopChangePos();
	}
};

class ValueWind : public AbstractButton {
public:
	using AbstractButton::AbstractButton;
};

class ValueButton : public AbstractButton {
public:
	using AbstractButton::AbstractButton;
};

class SliderVertical : public AbstractButton {
private:
	AbstractButton* slider_manager_;
	int x_click_lock;
	int y_click_lock;
	bool click;
public:
	SliderVertical(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", AbstractButton* slider_manager = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		slider_manager_ = slider_manager;
		x_click_lock = -1;
		y_click_lock = -1;
		click = false;
	}
	virtual void Use() {
		click = true;
		SDL_GetGlobalMouseState(&x_click_lock, &y_click_lock);
		x_click_lock -= X_START_WINDOW;
		y_click_lock -= Y_START_WINDOW;
		x_click_lock -= GetX();
		y_click_lock -= GetY();
	}
	void Update() {
		if (click) {
			int x_click;
			int y_click;
			SDL_GetGlobalMouseState(&x_click, &y_click);
			x_click -= X_START_WINDOW;
			y_click -= Y_START_WINDOW;
			y_click -= y_click_lock;
			y_click = std::max(slider_manager_->GetY() + 3, y_click);
			y_click = std::min(slider_manager_->GetY() + slider_manager_->GetHei() - GetHei() - 3, y_click);
			SetY(y_click);
		}
	}
	virtual void NoUse() {
		click = false;
	}
	virtual bool UpdateEvent(SDL_Event* event) {
		bool ok = false;

		MouseOn();
		if (mouse_on) {
			if (event) {
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
			}
		}
		if (event) {
			if ((*event).button.button == SDL_BUTTON_LEFT) {
				if ((*event).type == SDL_MOUSEBUTTONUP) {
					if (eve) {
						NoUse();
						//ok = true;
					}
				}
			}
		}
		return ok;
	}
};

class SliderHorizontal : public AbstractButton {
private:
	AbstractButton* slider_manager_;
	int x_click_lock;
	int y_click_lock;
	bool click;
public:
	SliderHorizontal(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", AbstractButton* slider_manager = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		slider_manager_ = slider_manager;
		x_click_lock = -1;
		y_click_lock = -1;
		click = false;
	}
	virtual void Use() {
		click = true;
		SDL_GetGlobalMouseState(&x_click_lock, &y_click_lock);
		x_click_lock -= X_START_WINDOW;
		y_click_lock -= Y_START_WINDOW;
		x_click_lock -= GetX();
		y_click_lock -= GetY();
	}
	void Update() {
		if (click) {
			int x_click;
			int y_click;
			SDL_GetGlobalMouseState(&x_click, &y_click);
			x_click -= X_START_WINDOW;
			y_click -= Y_START_WINDOW;
			x_click -= x_click_lock;
			x_click = std::max(slider_manager_->GetX() + 3, x_click);
			x_click = std::min(slider_manager_->GetX() + slider_manager_->GetLen() - GetLen() - 3, x_click);
			SetX(x_click);
		}
	}
	virtual void NoUse() {
		click = false;
	}
	virtual bool UpdateEvent(SDL_Event* event) {
		bool ok = false;

		MouseOn();
		if (mouse_on) {
			if (event) {
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
			}
		}
		if (event) {
			if ((*event).button.button == SDL_BUTTON_LEFT) {
				if ((*event).type == SDL_MOUSEBUTTONUP) {
					if (eve) {
						NoUse();
						//ok = true;
					}
				}
			}
		}
		return ok;
	}
};

class UpButtonSlider : public AbstractButton {
private:
	SliderVertical* slider_;
	bool click;
public:
	UpButtonSlider(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "",SliderVertical* slider = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		slider_ = slider;
		click = false;
	}
	void Use() {
		int new_pos = std::max(slider_->GetY() - 10, GetY() + GetHei() + 3);
		slider_->SetY(new_pos);
		click = true;
	}
	void Update() {
		if (click) {
			Use();
			SDL_Delay(10);
		}
	}
	virtual void NoUse() {
		click = false;
	}
	virtual bool UpdateEvent(SDL_Event* event) {
		bool ok = false;

		MouseOn();
		if (mouse_on) {
			if (event) {
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
		return ok;
	}
};

class RightButtonSlider : public AbstractButton {
private:
	SliderHorizontal* slider_;
	bool click;
public:
	RightButtonSlider(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", SliderHorizontal* slider = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		slider_ = slider;
		click = false;
	}
	void Use() {
		int new_pos = std::min(slider_->GetX() + 10, GetX() - slider_->GetLen() - 3);
		slider_->SetX(new_pos);
		click = true;
	}
	void Update() {
		if (click) {
			Use();
			SDL_Delay(10);
		}
	}
	virtual void NoUse() {
		click = false;
	}
	virtual bool UpdateEvent(SDL_Event* event) {
		bool ok = false;

		MouseOn();
		if (mouse_on) {
			if (event) {
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
		return ok;
	}
};

class LeftButtonSlider : public AbstractButton {
private:
	SliderHorizontal* slider_;
	bool click;
public:
	LeftButtonSlider(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", SliderHorizontal* slider = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		slider_ = slider;
		click = false;
	}
	void Use() {		
		int new_pos = std::max(slider_->GetX() - 10, GetX() + GetLen() + 3);
		slider_->SetX(new_pos);
		click = true;
	}
	void Update() {
		if (click) {
			Use();
			SDL_Delay(10);
		}
	}
	virtual void NoUse() {
		click = false;
	}
	virtual bool UpdateEvent(SDL_Event* event) {
		bool ok = false;

		MouseOn();
		if (mouse_on) {
			if (event) {
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
		return ok;
	}
};

class DownButtonSlider : public AbstractButton {
private:
	SliderVertical* slider_;
	bool click;
public:
	DownButtonSlider(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", SliderVertical* slider = nullptr)
		: AbstractButton(x, y, length, height, path_img) {
		slider_ = slider;
		click = false;
	}
	void Use() {
		int new_pos = std::min(slider_->GetY() + 10, GetY() - slider_->GetHei() - 3);
		slider_->SetY(new_pos);
		click = true;
	}
	void Update() {
		if (click) {
			Use();
			SDL_Delay(10);
		}
	}
	virtual void NoUse() {
		click = false;	
	}
	virtual bool UpdateEvent(SDL_Event* event) {
		bool ok = false;

		MouseOn();
		if (mouse_on) {
			if (event) {
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
		return ok;
	}
};

class SliderManagerVertical : public AbstractButton {
private:
	SliderVertical slider;
	UpButtonSlider up_button;
	DownButtonSlider down_button;
	double scale_;
public:
	SliderManagerVertical(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", double scale = 1)
		: AbstractButton(x, y, length, height, path_img), slider(x + 3, y + 3, length - 6, (int)(height / scale), "Img/slider_button.bmp", this),
		up_button{x, y - length, length, length, "Img/up_button.bmp", &slider},
		down_button{ x, y + height, length, length, "Img/down_button.bmp", &slider }{
		scale_ = scale;
	}
	virtual void Show() {
		TailShow();
		up_button.Show();
		down_button.Show();
		slider.Show();
	}
	virtual bool UpdateEvent(SDL_Event* event) {
		bool ok = false;
		if (slider.UpdateEvent(event)) { ok = true; }
		if (up_button.UpdateEvent(event)) { ok = true; }
		if (down_button.UpdateEvent(event)) { ok = true; }
		return ok;
	}
	void Update() {
		slider.Update();
		up_button.Update();
		down_button.Update();
	}
	void Moving(int x, int y) {
		int slider_pos_regarding_y = slider.GetY() - GetY();
		y += 15;
		SetX(x);
		SetY(y);
		up_button.SetX(x);
		up_button.SetY(y - GetLen());
		down_button.SetX(x);
		down_button.SetY(y + GetHei());
		slider.SetX(x + 3);
		slider.SetY(slider_pos_regarding_y + y);
	}
	int GetSliderRelativePos() {
		return slider.GetY() - GetY();
	}
	UpButtonSlider* UpClick() {
		return &up_button;
	}
	DownButtonSlider* DownClick() {
		return &down_button;
	}
	void ChangeSlider(double scale) {
		scale_ = scale;
		slider.SetHei((int)(GetHei() / scale));
		if (slider.GetY() + slider.GetHei() > GetY() + GetHei()) {
			slider.SetY(GetY() + GetHei() - slider.GetHei() - 3);
		}
	}
};

class SliderManagerHorizontal : public AbstractButton {
private:
	SliderHorizontal slider;
	RightButtonSlider right_button;
	LeftButtonSlider left_button;
	double scale_;
public:
	SliderManagerHorizontal(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", double scale = 1)
		: AbstractButton(x, y, length, height, path_img), slider(x + 3, y + 3, (int)(length / scale), height - 6, "Img/slider_button.bmp", this),
		right_button{ x + length, y, height, height, "Img/right_button.bmp", &slider },
		left_button{ x - height, y, height, height, "Img/left_button.bmp", &slider }{
		scale_ = scale;
	}
	virtual void Show() {
		TailShow();
		right_button.Show();
		left_button.Show();
		slider.Show();
	}
	virtual bool UpdateEvent(SDL_Event* event) {
		bool ok = false;
		if (slider.UpdateEvent(event)) { ok = true; }
		if (right_button.UpdateEvent(event)) { ok = true; }
		if (left_button.UpdateEvent(event)) { ok = true; }
		return ok;
	}
	void Update() {
		slider.Update();
		right_button.Update();
		left_button.Update();
	}
	void Moving(int x, int y) {
		int slider_pos_regarding_x = slider.GetX() - GetX();
		SetX(x);
		SetY(y);
		right_button.SetX(x + GetLen());
		right_button.SetY(y);
		left_button.SetX(x - 15);
		left_button.SetY(y);
		slider.SetX(x + slider_pos_regarding_x);
		slider.SetY(y + 3);
	}
	int GetSliderRelativePos() {
		return slider.GetX() - GetX();
	}

	RightButtonSlider* RightClick() {
		return &right_button;
	}
	LeftButtonSlider* LeftClick() {
		return &left_button;
	}
	void ChangeSlider(double scale) {
		scale_ = scale;
		slider.SetLen((int)(GetLen() / scale));
		if (slider.GetX() + slider.GetLen() > GetX() + GetLen()) {
			slider.SetX(GetX() + GetLen() - slider.GetLen() - 3);
		}
	}
};

class UserButton : public AbstractButton {
private:
	Brush* brush;
	ITool* tool;
public:
	UserButton(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, std::string path_img = "", Brush* brush_ = nullptr, ITool* tool_ = nullptr)
		: AbstractButton(x, y, length, height, path_img), tool(tool_) {
		brush = brush_;
	}
	virtual void Use() {
		if (brush->tool_builtin)
			brush->tool_builtin->using_ = false;
		if (brush->tool_out)
			brush->tool_out->using_ = false;
		if (brush->tool_creator)
			brush->tool_creator->using_ = false;
		brush->tool_out = this;
		brush->tool_builtin = nullptr;
		brush->tool = tool;
		brush->tool_creator = nullptr;
		using_ = true;
	}
};