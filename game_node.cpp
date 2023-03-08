/**
 * Copyright (C) 2023  Alpaca-zip
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "utility.h"

class GameNode : public ParamServer
{
private:

  int width = 600;
  int height = 150;
  int window_size[2] = {width, height};
  int background_color[3] = {235, 235, 235};

  int t_rex_index = 0;
  int t_rex_update_counter = 0;

  SDL_Window *window;
  SDL_Surface *window_surface, *message_balloon, *logo, *ground, *t_rex;
  SDL_Rect ground_clip, t_rex_clip;

public:

  GameNode()
  {
    initializeSDL();
    printf("T-Rex runner game node initialized.\n");
  }

  ~GameNode()
  {
    SDL_FreeSurface(window_surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  void initializeSDL()
  {
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
    {
      printf("Failed to initialize the SDL2 library.\n");
      printf("SDL2 Error: %s\n", SDL_GetError());
      return;
    }
  }

  void openIntroWindow()
  {
    message_balloon = loadImage("message_balloon.bmp");
    ground = loadImage("ground.bmp");
    logo = loadImage("logo.bmp");
    t_rex = loadImage("t_rex.bmp");

    window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_size[0], window_size[1], 0);
    if(!window)
    {
      printf("Failed to create window.\n");
      printf("SDL2 Error: %s\n", SDL_GetError());
      return;
    }

    window_surface = SDL_GetWindowSurface(window);
    if(!window_surface)
    {
      printf("Failed to get the surface from the window.\n");
      printf("SDL2 Error: %s\n", SDL_GetError());
      return;
    }

    bool keep_window_open = true;
    while(keep_window_open)
    {
      SDL_Event e;
      while(SDL_PollEvent(&e) > 0)
      {
        switch(e.type)
        {
          case SDL_QUIT:
            keep_window_open = false;
            break;
        }
      }

      SDL_FillRect(window_surface, nullptr, SDL_MapRGB(window_surface->format, background_color[0], background_color[1], background_color[2]));

      // message balloon
      drawImage(message_balloon, window_surface, 106, 45, width/10, height*0.4);

      // ground
      ground_clip = selectSprite(ground, 15, 1, 0, 0);
      drawSprite(ground, ground_clip, window_surface, -1, -1, width/20, height*0.85);

      // logo
      drawImage(logo, window_surface, 282, 30, width*0.33, height*0.5);

      // t-rex
      t_rex_clip = updateTrex(t_rex);
      drawSprite(t_rex, t_rex_clip, window_surface, 44, 47, width/15, height*0.65);

      SDL_UpdateWindowSurface(window);
      SDL_FreeSurface(window_surface);
    }
  }

  SDL_Surface *loadImage(std::string file_name)
  {
    std::string current_path = SDL_GetBasePath();
    std::string full_path = current_path + "imgs/" + file_name;
    printf("Load image from: %s\n", full_path.c_str());
    SDL_Surface *image = SDL_LoadBMP(full_path.c_str());
    if(!image)
    {
      printf("Failed to load image.\n");
      printf("SDL2 Error: %s\n", SDL_GetError());
      return 0;
    }
    return image;
  }

  void drawImage(SDL_Surface *image, SDL_Surface *windows_surface, int size_x, int size_y, int position_x, int position_y)
  {
    SDL_Rect dstrect;
    dstrect.x = position_x;
    dstrect.y = position_y;
    dstrect.w = image->w;
    dstrect.h = image->h;
    if(size_x != -1) dstrect.w = size_x;
    if(size_y != -1) dstrect.h = size_y;
    SDL_BlitScaled(image, NULL, windows_surface, &dstrect);
    SDL_Delay(10);
  }

  SDL_Rect selectSprite(SDL_Surface *sprite_sheet_image, int column, int row, int num_x, int num_y)
  {
    SDL_Rect sprite_clip;
    sprite_clip.w = sprite_sheet_image->w / column;
    sprite_clip.h = sprite_sheet_image->h / row;
    sprite_clip.x = num_x * sprite_clip.w;
    sprite_clip.y = num_y * sprite_clip.h;
    return sprite_clip;
  }

  void drawSprite(SDL_Surface *sprite, SDL_Rect sprite_clip, SDL_Surface *windows_surface, int size_x, int size_y, int position_x, int position_y)
  {
    SDL_Rect dstrect;
    dstrect.x = position_x;
    dstrect.y = position_y;
    dstrect.w = sprite_clip.w;
    dstrect.h = sprite_clip.h;
    if(size_x != -1) dstrect.w = size_x;
    if(size_y != -1) dstrect.h = size_y;
    SDL_BlitScaled(sprite, &sprite_clip, windows_surface, &dstrect);
    SDL_Delay(10);
  }

  SDL_Rect updateTrex(SDL_Surface *sprite_sheet_image)
  {
    if(t_rex_index == 0)
    {
      if(t_rex_update_counter % 150 == 149) t_rex_index = (t_rex_index + 1)%2;
    }
    else
    {
      if(t_rex_update_counter % 10 == 9) t_rex_index = (t_rex_index + 1)%2;
    }

    t_rex_update_counter += 1;
    return selectSprite(sprite_sheet_image, 6, 1, t_rex_index, 0);
  }
};

int main(int argc, char** argv)
{
  GameNode GN;
  GN.openIntroWindow();
  GN.~GameNode();
  return 0;
}
