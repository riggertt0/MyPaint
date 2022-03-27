#pragma once
#include <queue>

void ActionBeginPaint(Uint32* tempPixels, int x_click, int y_click, int len, int hei, int get_x, int get_y, int show_rect_x, int show_rect_y, int scale, int size, Uint32 pixelColor) {
	x_click += (int)(show_rect_x * scale);
	y_click += (int)(show_rect_y * scale);
	if (x_click - get_x >= 0 && y_click - get_y >= 0 && (int)x_click - get_x < len * scale && y_click - get_y < hei * scale) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if ((int)x_click - get_x + i < len * scale) {
					if ((int)y_click - get_y + j >= 0 && (int)y_click - get_y + j < hei * scale) {
						tempPixels[(int)(((int)x_click - get_x) / scale) + len * ((int)(((int)y_click - get_y) / scale) + j) + i] = pixelColor;
					}
					if ((int)y_click - get_y - j >= 0 && (int)y_click - get_y - j < hei * scale) {
						tempPixels[(int)(((int)x_click - get_x) / scale) + len * ((int)(((int)y_click - get_y) / scale) - j) + i] = pixelColor;
					}
				}
				if (x_click - get_x - i > 0) {
					if ((int)y_click - get_y + j >= 0 && (int)y_click - get_y + j < hei * scale) {
						tempPixels[(int)(((int)x_click - get_x) / scale) + len * ((int)(((int)y_click - get_y) / scale) + j) - i] = pixelColor;
					}
					if ((int)y_click - get_y - j >= 0 && (int)y_click - get_y - j < hei * scale) {
						tempPixels[(int)(((int)x_click - get_x) / scale) + len * ((int)(((int)y_click - get_y) / scale) - j) - i] = pixelColor;
					}
				}
			}
		}
	}
}

void ActionEndPaint(Uint32* tempPixels, int x_start, int y_start, int x_finish, int y_finish, int len, int hei, int get_x, int get_y, int show_rect_x, int show_rect_y, int scale, int size, Uint32 pixelColor) {}

void ActionUpdatePaint(Uint32* tempPixels, int x_start, int y_start, int x_finish, int y_finish, int len, int hei, int get_x, int get_y, int show_rect_x, int show_rect_y, int scale, int size, Uint32 pixelColor) {
	SDL_GetGlobalMouseState(&x_start, &y_start);
	x_start -= X_START_WINDOW;
	y_start -= Y_START_WINDOW;
	ActionBeginPaint(tempPixels, x_start, y_start, len, hei, get_x, get_y, show_rect_x, show_rect_y, scale, size, pixelColor);
}

void ActionBeginRect_Circle(Uint32* tempPixels, int x_click, int y_click, int len, int hei, int get_x, int get_y, int show_rect_x, int show_rect_y, int scale, int size, Uint32 pixelColor) {}

void ActionEndRect(Uint32* tempPixels, int x_start, int y_start, int x_finish, int y_finish, int len, int hei, int get_x, int get_y, int show_rect_x, int show_rect_y, int scale, int size, Uint32 pixelColor) {
	if (x_finish < x_start) std::swap(x_finish, x_start);
	if (y_finish < y_start) std::swap(y_finish, y_start);
	for (int i = x_start; i <= x_finish; i++) {
		if ((i - get_x) >= 0 && (i - get_x) < len * scale) {
			tempPixels[(int)(((int)i - get_x) / scale) + len * (int)(((int)y_start - get_y) / scale)] = pixelColor;
			tempPixels[(int)(((int)i - get_x) / scale) + len * (int)(((int)y_finish - get_y) / scale)] = pixelColor;
		}
	}
	for (int i = y_start; i < y_finish; i++) {
		if ((i - get_y) >= 0 && (i - get_y) < hei * scale) {
			if ((x_start - get_x) >= 0 && (x_start - get_x) < len * scale) {
				tempPixels[(int)(((int)x_start - get_x) / scale) + len * (int)(((int)i - get_y) / scale)] = pixelColor;
			}
			if ((x_finish - get_x) >= 0 && (x_finish - get_x) < len * scale) {
				tempPixels[(int)(((int)x_finish - get_x) / scale) + len * (int)(((int)i - get_y) / scale)] = pixelColor;
			}
		}
	}
}

void ActionEndFillRect(Uint32* tempPixels, int x_start, int y_start, int x_finish, int y_finish, int len, int hei, int get_x, int get_y, int show_rect_x, int show_rect_y, int scale, int size, Uint32 pixelColor) {
	if (x_finish < x_start) std::swap(x_finish, x_start);
	if (y_finish < y_start) std::swap(y_finish, y_start);
	for (int i = x_start; i <= x_finish; i++) {
		for (int j = y_start; j < y_finish; j++) {
			if ((i - get_x) >= 0 && (i - get_x) < len * scale && (j - get_y) >= 0 && (j - get_y) < hei * scale) {
				tempPixels[(int)(((int)i - get_x) / scale) + len * (int)(((int)j - get_y) / scale)] = pixelColor;
			}
		}
	}
}

void ActionUpdateRect(Uint32* tempPixels, int x_start, int y_start, int x_finish, int y_finish, int len, int hei, int get_x, int get_y, int show_rect_x, int show_rect_y, int scale, int size, Uint32 pixelColor) {
	SDL_Rect rect = { get_x, get_y, len, hei };
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
	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, len, hei, 32, Rmask, Gmask, Bmask, Amask);
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);
	Uint32* newtempPixels = new Uint32[len * hei];
	memset(newtempPixels, 0, len * hei * sizeof(Uint32));

	if (x_finish < x_start) std::swap(x_finish, x_start);
	if (y_finish < y_start) std::swap(y_finish, y_start);
	for (int i = x_start; i <= x_finish; i++) {
		newtempPixels[i - get_x + len * (y_start  - get_y)] = pixelColor;
		newtempPixels[i - get_x + len * (y_finish - get_y)] = pixelColor;
	}
	for (int i = y_start; i <= y_finish; i++) {
		newtempPixels[x_start -  get_x + len * (i - get_y)] = pixelColor;
		newtempPixels[x_finish - get_x + len * (i - get_y)] = pixelColor;
	}
	SDL_UpdateTexture(newTexture, NULL, newtempPixels, hei * sizeof(Uint32));
	SDL_Rect rect1 = { get_x, get_y, len, hei };
	SDL_RenderCopy(ren, newTexture, nullptr, &rect1);
	SDL_DestroyTexture(newTexture);
	delete[] newtempPixels;
}

void ActionEndCirc(Uint32* tempPixels, int x_start, int y_start, int x_finish, int y_finish, int len, int hei, int get_x, int get_y, int show_rect_x, int show_rect_y, int scale, int size, Uint32 pixelColor) {
	double len_r = sqrt((x_finish - x_start) * (x_finish - x_start) + (y_finish - y_start) * (y_finish - y_start));

	for (int i = (int)(x_start - len_r - 1); i <= x_start + len_r + 1; i++) {
		for (int j = (int)(y_start - len_r - 1); j < y_start + len_r + 1; j++) {
			if (abs((i - x_start) * (i - x_start) + (j - y_start) * (j - y_start) - len_r * len_r) < len_r) {
				if ((i - get_x) >= 0 && (i - get_x) < len * scale && (j - get_y) >= 0 && (j - get_y) < hei * scale) {
					tempPixels[(int)(((int)i - get_x) / scale) + len * (int)(((int)j - get_y) / scale)] = pixelColor;
				}
			}
		}
	}
}

void ActionEndFillCirc(Uint32* tempPixels, int x_start, int y_start, int x_finish, int y_finish, int len, int hei, int get_x, int get_y, int show_rect_x, int show_rect_y, int scale, int size, Uint32 pixelColor) {
	double len_r = sqrt((x_finish - x_start) * (x_finish - x_start) + (y_finish - y_start) * (y_finish - y_start));

	for (int i = (int)(x_start - len_r - 1); i <= x_start + len_r + 1; i++) {
		for (int j = (int)(y_start - len_r - 1); j < y_start + len_r + 1; j++) {
			if ((i - x_start) * (i - x_start) + (j - y_start) * (j - y_start) < len_r * len_r) {
				if ((i - get_x) >= 0 && (i - get_x) < len * scale && (j - get_y) >= 0 && (j - get_y) < hei * scale) {
					tempPixels[(int)((i - get_x) / scale) + len * (int)((j - get_y) / scale)] = pixelColor;
				}
			}
		}
	}
}

void ActionUpdateCirc(Uint32* tempPixels, int x_start, int y_start, int x_finish, int y_finish, int len, int hei, int get_x, int get_y, int show_rect_x, int show_rect_y, int scale, int size, Uint32 pixelColor) {
	SDL_Rect rect = { get_x, get_y, len, hei };
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
	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, len, hei, 32, Rmask, Gmask, Bmask, Amask);
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);
	Uint32* newtempPixels = new Uint32[len * hei];
	memset(newtempPixels, 0, len * hei * sizeof(Uint32));

	double len_r = sqrt((x_finish - x_start) * (x_finish - x_start) + (y_finish - y_start) * (y_finish - y_start));
	for (int i = (int)(x_start - len_r - 1); i <= x_start + len_r + 1; i++) {
		for (int j = (int)(y_start - len_r - 1); j < y_start + len_r + 1; j++) {
			if (abs((i - x_start) * (i - x_start) + (j - y_start) * (j - y_start) - len_r * len_r) < len_r) {
				if ((i - get_x) >= 0 && (i - get_x) < len && (j - get_y) >= 0 && (j - get_y) < hei) {
					newtempPixels[(i - get_x) + len * (j - get_y)] = pixelColor;
				}
			}
		}
	}
	SDL_UpdateTexture(newTexture, NULL, newtempPixels, hei * sizeof(Uint32));
	SDL_Rect rect1 = { get_x, get_y, len, hei };
	SDL_RenderCopy(ren, newTexture, nullptr, &rect1);
	SDL_DestroyTexture(newTexture);
	delete[] newtempPixels;
}

void ActionBeginLine(Uint32* tempPixels, int x_click, int y_click, int len, int hei, int get_x, int get_y, int show_rect_x, int show_rect_y, int scale, int size, Uint32 pixelColor) {
	x_click += (int)(show_rect_x * scale);
	y_click += (int)(show_rect_y * scale);
	if (x_click - get_x >= 0 && y_click - get_y >= 0 && (int)x_click - get_x < len * scale && y_click - get_y < hei * scale) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if ((int)x_click - get_x + i < len * scale) {
					if ((int)y_click - get_y + j >= 0 && (int)y_click - get_y + j < hei * scale) {
						tempPixels[(int)(((int)x_click - get_x) / scale) + len * ((int)(((int)y_click - get_y) / scale) + j) + i] = pixelColor;
					}
					if ((int)y_click - get_y - j >= 0 && (int)y_click - get_y - j < hei * scale) {
						tempPixels[(int)(((int)x_click - get_x) / scale) + len * ((int)(((int)y_click - get_y) / scale) - j) + i] = pixelColor;
					}
				}
				if (x_click - get_x - i > 0) {
					if ((int)y_click - get_y + j >= 0 && (int)y_click - get_y + j < hei * scale) {
						tempPixels[(int)(((int)x_click - get_x) / scale) + len * ((int)(((int)y_click - get_y) / scale) + j) - i] = pixelColor;
					}
					if ((int)y_click - get_y - j >= 0 && (int)y_click - get_y - j < hei * scale) {
						tempPixels[(int)(((int)x_click - get_x) / scale) + len * ((int)(((int)y_click - get_y) / scale) - j) - i] = pixelColor;
					}
				}
			}
		}
	}
}

void ActionEndLine(Uint32* tempPixels, int x_start, int y_start, int x_finish, int y_finish, int len, int hei, int get_x, int get_y, int show_rect_x, int show_rect_y, int scale, int size, Uint32 pixelColor) {
	double x_now = x_start;
	double y_now = y_start;
	int size_step = 1;
	double max_step = std::max(abs((x_finish - x_start) / size_step), abs((y_finish - y_start) / size_step));
	if (max_step != 0) {
		double x_step = (x_finish - x_start) / max_step;
		double y_step = (double)((y_finish - y_start) / max_step);

		for (int step = 0; step < max_step; step++) {
			x_now += x_step;
			y_now += y_step;
			if (x_now - get_x >= 0 && y_now - get_y >= 0 && (int)x_now - get_x < len * scale && y_now - get_y < hei * scale) {
				for (int i = 0; i < size; i++) {
					for (int j = 0; j < size; j++) {
						if ((int)x_now - get_x + i < len * scale) {
							if ((int)y_now - get_y + j >= 0 && (int)y_now - get_y + j < hei * scale) {
								tempPixels[(int)(((int)x_now - get_x) / scale) + len * ((int)(((int)y_now - get_y) / scale) + j) + i] = pixelColor;
							}
							if ((int)y_now - get_y - j >= 0 && (int)y_now - get_y - j < hei * scale) {
								tempPixels[(int)(((int)x_now - get_x) / scale) + len * ((int)(((int)y_now - get_y) / scale) - j) + i] = pixelColor;
							}
						}
						if (x_now - get_x - i > 0) {
							if ((int)y_now - get_y + j >= 0 && (int)y_now - get_y + j < hei * scale) {
								tempPixels[(int)(((int)x_now - get_x) / scale) + len * ((int)(((int)y_now - get_y) / scale) + j) - i] = pixelColor;
							}
							if ((int)y_now - get_y - j >= 0 && (int)y_now - get_y - j < hei * scale) {
								tempPixels[(int)(((int)x_now - get_x) / scale) + len * ((int)(((int)y_now - get_y) / scale) - j) - i] = pixelColor;
							}
						}
					}
				}
			}
		}
	}
}

void ActionUpdateLine(Uint32* tempPixels, int x_start, int y_start, int x_finish, int y_finish, int len, int hei, int get_x, int get_y, int show_rect_x, int show_rect_y, int scale, int size, Uint32 pixelColor) {
	double x_now = x_start;
	double y_now = y_start;
	SDL_Rect rect = { get_x, get_y, len, hei };
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
	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, len, hei, 32, Rmask, Gmask, Bmask, Amask);
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);
	Uint32* newtempPixels = new Uint32[len * hei];
	memset(newtempPixels, 0, len * hei * sizeof(Uint32));

	int size_step = 1;
	double max_step = std::max(abs((x_finish - x_start) / size_step), abs((y_finish - y_start) / size_step));
	if (max_step != 0) {
		double x_step = (x_finish - x_start) / max_step;
		double y_step = (double)((y_finish - y_start) / max_step);

		for (int step = 0; step < max_step; step++) {
			x_now += x_step;
			y_now += y_step;
			if (x_now - get_x >= 0 && y_now - get_y >= 0 && (int)x_now - get_x < len && y_now - get_y < hei ) {
				for (int i = 0; i < size * scale; i++) {
					for (int j = 0; j < size * scale; j++) {
						if ((int)x_now - get_x + i < len) {
							if ((int)y_now - get_y + j >= 0 && (int)y_now - get_y + j < hei) {
								newtempPixels[(int)(((int)x_now - get_x)) + len * ((int)(((int)y_now - get_y) ) + j) + i] = pixelColor;
							}
							if ((int)y_now - get_y - j >= 0 && (int)y_now - get_y - j < hei) {
								newtempPixels[(int)(((int)x_now - get_x) ) + len * ((int)(((int)y_now - get_y) ) - j) + i] = pixelColor;
							}
						}
						if (x_now - get_x - i > 0) {
							if ((int)y_now - get_y + j >= 0 && (int)y_now - get_y + j < hei ) {
								newtempPixels[(int)(((int)x_now - get_x) ) + len * ((int)(((int)y_now - get_y)) + j) - i] = pixelColor;
							}
							if ((int)y_now - get_y - j >= 0 && (int)y_now - get_y - j < hei ) {
								newtempPixels[(int)(((int)x_now - get_x)) + len * ((int)(((int)y_now - get_y)) - j) - i] = pixelColor;
							}
						}
					}
				}
			}
		}
	}
	SDL_UpdateTexture(newTexture, NULL, newtempPixels, hei * sizeof(Uint32));
	SDL_Rect rect1 = { get_x, get_y, len, hei };
	SDL_RenderCopy(ren, newTexture, nullptr, &rect1);
	SDL_DestroyTexture(newTexture);
	delete[] newtempPixels;
}

struct Pixel {
	Uint32 tempPixel = 0;
	int ind_x = 0;
	int ind_y = 0;
	bool visit = false;
	Pixel* up_neighbor = nullptr;
	Pixel* down_neighbor = nullptr;
	Pixel* left_neighbor  = nullptr;
	Pixel* right_neighbor = nullptr;
	Pixel* i = this;
	
};

void RecursivePixelColoring(std::queue<Pixel*> graph_que, Uint32* old_pixelColor, Uint32* new_pixelColor) {
	while (!graph_que.empty()) {
		Pixel* pixel = graph_que.front();
		graph_que.pop();
		if (pixel->tempPixel == *old_pixelColor) {

			if (pixel->left_neighbor && pixel->left_neighbor->visit == false) {
				pixel->left_neighbor->visit = true;
				graph_que.push(pixel->left_neighbor);
			}

			if (pixel->right_neighbor && pixel->right_neighbor->visit == false) {
				pixel->right_neighbor->visit = true;
				graph_que.push(pixel->right_neighbor);
			}

			if (pixel->down_neighbor && pixel->down_neighbor->visit == false) {
				pixel->down_neighbor->visit = true;
				graph_que.push(pixel->down_neighbor);
			}

			if (pixel->up_neighbor && pixel->up_neighbor->visit == false) {
				pixel->up_neighbor->visit = true;
				graph_que.push(pixel->up_neighbor);
			}
			pixel->tempPixel = *new_pixelColor;
		}
	}
}

void ActionBeginFill(Uint32* tempPixels, int x_click, int y_click, int len, int hei, int get_x, int get_y, int show_rect_x, int show_rect_y, int scale, int size, Uint32 pixelColor) {
	x_click += (int)(show_rect_x * scale);
	y_click += (int)(show_rect_y * scale);
	std::queue<Pixel*> graph_que;
	Pixel* tree = new Pixel[len * hei];
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < hei; j++) {
			tree[i + len * j].tempPixel = tempPixels[i + len * j];
			tree[i + len * j].ind_x = i;
			tree[i + len * j].ind_y = j;
			if(j > 0 )
				tree[i + len * j].up_neighbor = &(tree[i + len * (j - 1)]);
			if(j < hei - 1)
				tree[i + len * j].down_neighbor = &(tree[i + len * (j + 1)]);
			if(i < len - 1)
				tree[i + len * j].right_neighbor = tree[(i + 1) + len * j].i;
			if (i > 0)
				tree[i + len * j].left_neighbor = tree[(i - 1) + len * j].i;
		}
	}
	int help_x = (int)(((int)x_click - get_x) / scale);
	int help_y = (int)(((int)y_click - get_y) / scale);
	Uint32 old_pixelColor = tempPixels[help_x + len * help_y];
	graph_que.push(tree[help_x + len * help_y].i);
	RecursivePixelColoring(graph_que , &old_pixelColor, &pixelColor);

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < hei; j++) {
			tempPixels[i + len * j] = tree[i + len * j].tempPixel;
		}
	}
}

void ActionUpdateExcretion(Uint32* tempPixels, int x_start, int y_start, int x_finish, int y_finish, int len, int hei, int get_x, int get_y) {
	Uint32 pixelColor = 255 * pow(2, 23);
	SDL_Rect rect = { get_x, get_y, len, hei };
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
	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, len, hei, 32, Rmask, Gmask, Bmask, Amask);
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);
	Uint32* newtempPixels = new Uint32[len * hei];
	memset(newtempPixels, 0, len * hei * sizeof(Uint32));

	if (x_finish < x_start) std::swap(x_finish, x_start);
	if (y_finish < y_start) std::swap(y_finish, y_start);
	for (int i = x_start; i <= x_finish; i++) {
		newtempPixels[i - get_x + len * (y_start - get_y)] = pixelColor;
		newtempPixels[i - get_x + len * (y_finish - get_y)] = pixelColor;
	}
	for (int i = y_start; i <= y_finish; i++) {
		newtempPixels[x_start - get_x + len * (i - get_y)] = pixelColor;
		newtempPixels[x_finish - get_x + len * (i - get_y)] = pixelColor;
	}
	SDL_UpdateTexture(newTexture, NULL, newtempPixels, hei * sizeof(Uint32));
	SDL_Rect rect1 = { get_x, get_y, len, hei };
	SDL_RenderCopy(ren, newTexture, nullptr, &rect1);
	SDL_DestroyTexture(newTexture);
	delete[] newtempPixels;
}

void ActionEndExcretion(AbstractButton* cust_wind, int x, int y, int len, int hei, Uint32* tempPixels);