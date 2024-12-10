#include "./include/cpu.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_timer.h>
#include <cstdlib>
#include <ctime>

const int WINDOW_WIDTH = 160;
const int WINDOW_HEIGHT = 144;
const int WINDOW_SCALE = 10;
const int IPF = 15;

SDL_Window *initWindow() {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  SDL_Window *window =
      SDL_CreateWindow("GameBoy Emulator",           // window title
                       WINDOW_WIDTH * WINDOW_SCALE,  // width, in pixels
                       WINDOW_HEIGHT * WINDOW_SCALE, // height, in pixels
                       SDL_WINDOW_OPENGL             // flags - see below
      );

  // Check that the window was successfully created
  if (window == NULL) {
    // In the case that the window could not be made...
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n",
                 SDL_GetError());
    return NULL;
  }
  return window;
}

int main(int argc, char *argv[]) {
  srand(time(0));
  // if (argc == 1) {
  //   SDL_Log("ERROR: enter name of rom to run");
  //   return 1;
  // }
  const char *romName = argv[1];

  // cpu cpu;
  // cpu.init();
  // if (!cpu.loadRom(romName)) {
  //   cpu.running = false;
  //   return 1;
  //   // error already logged
  // }

  SDL_Window *window = initWindow();
  if (window == NULL) {
    // Handle the error, already logged by createWindow
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
  SDL_Texture *texture = SDL_CreateTexture(
      renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
      WINDOW_WIDTH * WINDOW_SCALE, WINDOW_HEIGHT * WINDOW_SCALE);

  SDL_SetRenderTarget(renderer, texture);

  // TODO: audio (maybe not implement)
  SDL_AudioSpec audioSpec;
  audioSpec.format = SDL_AUDIO_S8;
  audioSpec.channels = 4; // four channels (change to two and compress???)
  audioSpec.freq = 48000;

  SDL_AudioStream *audioStream = SDL_OpenAudioDeviceStream(
      SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audioSpec, NULL, NULL);

  SDL_ResumeAudioStreamDevice(audioStream);
  SDL_PutAudioStreamData(audioStream, NULL, 800);

  // while (Cpu.running) {
  //   SDL_Event event;
  //   while (SDL_PollEvent(&event)) {
  //     switch (event.type) {
  //     case (SDL_EVENT_QUIT):
  //       break;
  //     case (SDL_EVENT_KEY_DOWN): {
  //       switch (event.key.scancode) {
  //         {
  //         case (SDL_SCANCODE_ESCAPE): {
  //           SDL_DestroyWindow(window);
  //           SDL_Quit();
  //           return 0;
  //           break;
  //         }
  //         default:
  //           break;
  //         }
  //       }
  //       break;
  //     }
  //     case (SDL_EVENT_KEY_UP): {
  //       switch (event.key.scancode) {
  //       default:
  //         break;
  //       }
  //       break;
  //     }
  //     }
  //   }

  // modify this
  //   for (int i = 0; i < IPF; i++) {
  //     cpu.executeCycle();
  //     if (cpu.breakIPF) {
  //       break;
  //     }
  //   }
  //   if (cpu.draw) {
  //     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  //     SDL_RenderClear(renderer);
  //     for (int y = 0; y < 32; y++) {
  //       for (int x = 0; x < 64; x++) {
  //         if (cpu.gfx[x + (y * 64)]) {
  //           SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  //           SDL_FRect rect = {static_cast<float>(x * WINDOW_SCALE),
  //                             static_cast<float>(y * WINDOW_SCALE),
  //                             WINDOW_SCALE, WINDOW_SCALE};
  //           SDL_RenderFillRect(renderer, &rect);
  //         }
  //       }
  //     }
  //     SDL_SetRenderTarget(renderer, NULL);
  //     SDL_RenderPresent(renderer);
  //     cpu.draw = false;
  //   }
  // }
  //

  // close window
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
