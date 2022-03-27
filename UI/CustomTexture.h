#pragma once


class CustomTexture : public AbstractButton {
private:
	Uint32* tempPixels = nullptr;
	double step = 0.0;
	SDL_Texture* pTexture = nullptr;
	int x_click_lock;
	int y_click_lock;
	SDL_Rect show_rect;
public:
	CustomTexture(int x = 0, int y = 0, int length = DEFAULT_LEN, int height = DEFAULT_HEI, Uint32* tempPixels_ = nullptr)
		: AbstractButton(x, y, length, height), tempPixels(tempPixels_){
		DoHide();
	}

	virtual void Use() {
		DoChangePos();
		SDL_GetGlobalMouseState(&x_click_lock, &y_click_lock);
		x_click_lock -= X_START_WINDOW;
		y_click_lock -= Y_START_WINDOW;
		x_click_lock -= GetX();
		y_click_lock -= GetY();
	}

	virtual void NoUse() {
		StopChangePos();
		DoHide();
	}

	virtual void Show() {
		if (!IsHide()) {
			SDL_Rect rect = { GetX(), GetY(), GetLen(), GetHei() };
			show_rect = { 0, 0, GetLen(), GetHei() };
			SDL_RenderCopy(ren, pTexture, &show_rect, &rect);
			SetColor({ 128, 128, 128 });
			ShowDottedRect(GetX(), GetY(), GetLen(), GetHei(), step);
			SetColor({ 0,0,0 });
		}
	}

	virtual void Update() {
		if (!IsHide()) {
			step += 0.3;
			if (step > 10.0)
				step = 0.0;
		}
		if (IsChangePos()) {
			int x_click;
			int y_click;
			SDL_GetGlobalMouseState(&x_click, &y_click);
			x_click -= X_START_WINDOW;
			y_click -= Y_START_WINDOW;
			x_click -= x_click_lock;
			y_click -= y_click_lock;
			SetY(y_click);
			SetX(x_click);
		}
	}

	void Moving(int x, int y, int len, int hei) {
		SetX(x);
		SetY(y);
		SetLen(len);
		SetHei(hei);
	}

	void SetAll(int x, int y, int len, int hei, Uint32* tempPixels_) {
		if (len < 0) {
			x += len;
			len *= -1;
		}
		if (hei < 0) {
			y += hei;
			hei *= -1;
		}
		SetX(x);
		SetY(y);
		SetLen(len);
		SetHei(hei);
		tempPixels = tempPixels_;

		//exit(hei);
		//SDL_UpdateTexture(pTexture, NULL, tempPixels, hei * sizeof(Uint32));
	}

	void SetPixels(Uint32* tempPixels_, int hei) { 
		
		tempPixels = tempPixels_;
		/*if (tempPixels_) {
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

			SDL_UpdateTexture(pTexture, NULL, tempPixels, hei * sizeof(Uint32));
		}*/
	}

	Uint32* GetPixels() { return tempPixels; }

	virtual bool UpdateEvent(SDL_Event* event) {
		if (!IsHide()) {
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
								return false;
							}
						}
					}
				}
			}
		}
		return true;
	}
};