#include <iostream>
#include "Window.hpp"
#include "Timer.hpp"

int main(int argc, char **argv) {
	try {
		Window::Init("Hello World!");
	}
	catch (std::runtime_error const &e) {
		std::cout << e.what() << std::endl;
		Window::Quit();
		return -1;
	}

	Timer timer;

	SDL_Texture *msg = nullptr, *ticks = nullptr, *status = nullptr;

	SDL_Color white = { 255, 255, 255 };
	SDL_Rect msgBox, ticksBox, statusBox;

	auto box = Window::Box();
	msg = Window::RenderText("Ticks Elapsed: ", "SourceSansPro-Regular.ttf", white, 30);
	msgBox.x = 0;
	msgBox.y = box.h / 2;
	SDL_QueryTexture(msg, nullptr, nullptr, &msgBox.w, &msgBox.h);
	
	std::string strTicks = std::to_string(timer.Ticks());
	ticks = Window::RenderText(strTicks.c_str(), "SourceSansPro-Regular.ttf", white, 30);
	ticksBox.x = msgBox.w + 20;
	ticksBox.y = box.h / 2;
	SDL_QueryTexture(ticks, nullptr, nullptr, &ticksBox.w, &ticksBox.h);

	status = Window::RenderText("Stopped", "SourceSansPro-Regular.ttf", white, 30);
	statusBox.x = 0;
	statusBox.y = msgBox.y - 40;
	SDL_QueryTexture(status, nullptr, nullptr, &statusBox.w, &statusBox.h);

	SDL_Event evt;
	bool quit = false;

	while (!quit) {
		// process all events that took place since the last "time".
		while (SDL_PollEvent(&evt)) {
			if (evt.type == SDL_QUIT) {
				// user is closing the window.
				quit = true;
			}
			else if (evt.type == SDL_KEYDOWN) {
				// user presses any key.
				switch (evt.key.keysym.sym) {
				case SDLK_s:
					if (timer.IsStarted()) {
						timer.Stop();
					}
					else {
						timer.Start();
					}
					break;
				case SDLK_p:
					if (timer.IsPaused()) {
						timer.Unpause();
					}
					else {
						timer.Pause();
					}
					break;
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					break;
				}
			}
		}

		if (timer.IsStarted() && !timer.IsPaused()) {
			strTicks = std::to_string(timer.Ticks());
			SDL_DestroyTexture(ticks);
			ticks = Window::RenderText(strTicks.c_str(), "SourceSansPro-Regular.ttf", white, 30);
			SDL_QueryTexture(ticks, nullptr, nullptr, &ticksBox.w, &ticksBox.h);

			SDL_DestroyTexture(status);
			status = Window::RenderText("Running", "SourceSansPro-Regular.ttf", white, 30);
			SDL_QueryTexture(status, nullptr, nullptr, &statusBox.w, &statusBox.h);
		}
		else if (timer.IsPaused()) {
			SDL_DestroyTexture(status);
			status = Window::RenderText("Paused", "SourceSansPro-Regular.ttf", white, 30);
			SDL_QueryTexture(status, nullptr, nullptr, &statusBox.w, &statusBox.h);
		}
		else {
			SDL_DestroyTexture(status);
			status = Window::RenderText("Stopped", "SourceSansPro-Regular.ttf", white, 30);
			SDL_QueryTexture(status, nullptr, nullptr, &statusBox.w, &statusBox.h);
		}

		Window::Clear();
		Window::RenderTexture(msg, msgBox);
		Window::RenderTexture(ticks, ticksBox);
		Window::RenderTexture(status, statusBox);
		Window::Present();
	}

	SDL_DestroyTexture(msg);
	SDL_DestroyTexture(ticks);
	SDL_DestroyTexture(status);

	Window::Quit();
	return 0;
}