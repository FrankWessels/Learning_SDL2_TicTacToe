//Using SDL and standard IO
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<stdio.h>
#include<string>
#include<vector>



class TicTacToe {
	private:
	SDL_Rect game;
	SDL_Rect menu;
	SDL_Texture *background;
	SDL_Texture *cross;
	SDL_Texture *circle;
	int play[9] = {0, 2, 1, 2, 1, 0, 0, 0, 0};
	SDL_Rect locations[9];
	SDL_Renderer **renderer;
	public:
	TicTacToe(SDL_Renderer **r, int width) {
		renderer = r;

		//load textures
		background = IMG_LoadTexture(*renderer, "images/background.png");
		cross = IMG_LoadTexture(*renderer, "images/cross.png");
		circle = IMG_LoadTexture(*renderer, "images/circle.png");
		
		setSize(width);
		
		render();
	}
	void setSize(int width) {
		int sizegame = (int)(width*3/4);
		int sizemenu = width - sizegame;
		int margin = (int)(sizegame/(sizemenu/10));
		
		game.x = sizemenu; game.y = 0; game.w = sizegame; game.h = sizegame;
		menu.x = 0; menu.y = 0; menu.w = sizemenu; menu.h = sizegame;
		
		//Set texture locations
		locations[0].x = sizemenu + margin;
		locations[3].x = sizemenu + margin;
		locations[6].x = sizemenu + margin;
		locations[1].x = sizemenu + (int)(1*sizegame/3) + margin;
		locations[4].x = sizemenu + (int)(1*sizegame/3) + margin;
		locations[7].x = sizemenu + (int)(1*sizegame/3) + margin;
		locations[2].x = sizemenu + (int)(2*sizegame/3) + margin;
		locations[5].x = sizemenu + (int)(2*sizegame/3) + margin;
		locations[8].x = sizemenu + (int)(2*sizegame/3) + margin;
		locations[0].y = margin;
		locations[1].y = margin;
		locations[2].y = margin;
		locations[3].y = (int)(1*sizegame/3) + margin;
		locations[4].y = (int)(1*sizegame/3) + margin;
		locations[5].y = (int)(1*sizegame/3) + margin;
		locations[6].y = (int)(2*sizegame/3) + margin;
		locations[7].y = (int)(2*sizegame/3) + margin;
		locations[8].y = (int)(2*sizegame/3) + margin;	
		locations[0].w = (int)(1*sizegame/3) - margin - margin;
		locations[1].w = (int)(1*sizegame/3) - margin - margin;
		locations[2].w = (int)(1*sizegame/3) - margin - margin;
		locations[3].w = (int)(1*sizegame/3) - margin - margin;
		locations[4].w = (int)(1*sizegame/3) - margin - margin;
		locations[5].w = (int)(1*sizegame/3) - margin - margin;
		locations[6].w = (int)(1*sizegame/3) - margin - margin;
		locations[7].w = (int)(1*sizegame/3) - margin - margin;
		locations[8].w = (int)(1*sizegame/3) - margin - margin;
		locations[0].h = (int)(1*sizegame/3) - margin - margin;
		locations[1].h = (int)(1*sizegame/3) - margin - margin;
		locations[2].h = (int)(1*sizegame/3) - margin - margin;
		locations[3].h = (int)(1*sizegame/3) - margin - margin;
		locations[4].h = (int)(1*sizegame/3) - margin - margin;
		locations[5].h = (int)(1*sizegame/3) - margin - margin;
		locations[6].h = (int)(1*sizegame/3) - margin - margin;
		locations[7].h = (int)(1*sizegame/3) - margin - margin;
		locations[8].h = (int)(1*sizegame/3) - margin - margin;
	}
	void render() {
		//render textures
		SDL_RenderCopy(*renderer, background, NULL, &game);
		for (int i = 0; i < 9; i++) {
			if (play[i] == 1) {
				SDL_RenderCopy(*renderer, cross, NULL, &locations[i]);
			}
			if (play[i] == 2) {
				SDL_RenderCopy(*renderer, circle, NULL, &locations[i]);
			}			
		}
	}
	int wincheck(int t) {
		if (play[4] == t) {
			if (play[0] == t && play[8] == t) {
				return t;
			}
			if (play[1] == t && play[7] == t) {
				return t;
			}
			if (play[2] == t && play[6] == t) {
				return t;
			}	
			if (play[3] == t && play[5] == t) {
				return t;
			}
		}
		else if (play[0] == t) {
			if (play[1] == t && play[2] == t) {
				return t;
			}
			if (play[3] == t && play[4] == t) {
				return t;
			}			
		}
		else if (play[8] == t) {
			if (play[6] == t && play[7] == t) {
				return t;
			}
			if (play[2] == t && play[5] == t) {
				return t;
			}
		}
	}
	void handleEvents() {

	}
};

class Window {
	private:
	//window
	SDL_Window *win;
	//Window dimensions
	SDL_Rect box;
	//window title
	char *title;
	//background color
	int rgba [4] = {0, 0, 0, 0};
	//Load game
	TicTacToe *t;
	//renderer
	SDL_Renderer *renderer;
	public:
	//window id
	int id;
	//window focus
	bool focus;
	//default constructor
	Window() {
		box.x = 300; box.y = 300; box.w = 512; box.h = 512;
		title = "";
		win = SDL_CreateWindow("", box.x, box.y, box.w, box.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		SDL_SetRenderDrawColor(renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		id = SDL_GetWindowID(win);
		focus = false;
		t = new TicTacToe(&renderer, box.w);
	}
	Window(int x, int y, int w, int h, char *title) {
		box.x = x; box.y = y; box.w = w; box.h = h;
		title = title;
		win = SDL_CreateWindow(title, box.x, box.y, box.w, box.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		SDL_SetRenderDrawColor(renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		id = SDL_GetWindowID(win);
		focus = false;		
		t = new TicTacToe(&renderer, box.w);		
	}
	void handleEvents(SDL_Event e) {
		if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
			rgba[2] = e.window.data1;
			rgba[3] = e.window.data2;
			SDL_RenderClear(renderer);
			render();
		}
		if (e.window.event == SDL_WINDOWEVENT_MOVED) {
			rgba[0] = e.window.data1;
			rgba[1] = e.window.data2;
		}
		if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
			focus = true;
		}		
		if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
			focus = false;
		}
	}
	void render() {
		t->render();
		SDL_RenderPresent(renderer);
	}
	SDL_Window *getWindow() {
		return win;
	}
	SDL_Renderer **getRenderer() {
		return &renderer;
	}	
	void destroy() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(win);
	}
};

class Program {
	private:
	std::vector<Window> windows;
	SDL_Event e;
	bool running;
	//inputdata (the program can act on events but also read on states)
	const Uint8 *currentKeyStates;
	int mouseX = 0;
	int mouseY = 0;
	bool mousemotion = false;
	int mouseButtons[4] = {0, 0, 0, 0};
	public:

	Program() {
		//Here the most basic form of the program is written
		//For this program we will use SDL2
		//Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);
		
		//This program uses 1 window
		Window window(400, 200, 800, 600, "TicTacToe");
		windows.push_back(window);
		
		
		//now simply run the program
		run();

	}
	void run() {
		running = true;
		
		while (running) {
			handleEvents();
			
			//updates the renderer
			for (int i = 0; i < windows.size(); i++) {
				windows[i].render();
			}
		}

		//Quit SDL subsystems 
		SDL_Quit();
	}
	Window *getWindowbyID(int id) {
		Window *w = NULL;
		for (int i = 0; i < windows.size(); i++) {
			if (windows[i].id == id) {
				w = &windows[i];
				break;
			}
		}
		return w;
	}
	void handleEvents() {
		while(SDL_PollEvent(&e) != 0) {
			//quit when pressing on x
			if (e.type == SDL_QUIT) {
				running = false;
			}
			//send window events to the coorsponding window
			if (e.type == SDL_WINDOWEVENT) {
				getWindowbyID(e.window.windowID)->handleEvents(e);
			}
		}
	}
};



int main( int argc, char* args[]) {
	
	Program program;
	
	return 0;
}
