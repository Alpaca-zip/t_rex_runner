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
    ROS_INFO("T-Rex runner game node initialized.");
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
      ROS_ERROR("Failed to initialize the SDL2 library.");
      ROS_ERROR("SDL2 Error: %s", SDL_GetError());
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
      ROS_ERROR("Failed to create window.");
      ROS_ERROR("SDL2 Error: %s", SDL_GetError());
      return;
    }

    window_surface = SDL_GetWindowSurface(window);
    if(!window_surface)
    {
      ROS_ERROR("Failed to get the surface from the window.");
      ROS_ERROR("SDL2 Error: %s", SDL_GetError());
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
    std::string full_path = ros::package::getPath("t_rex_runner") + "/imgs/" + file_name;
    SDL_Surface *image = SDL_LoadBMP(full_path.c_str());
    if(!image)
    {
      ROS_ERROR("Failed to load image.");
      ROS_ERROR("SDL2 Error: %s", SDL_GetError());
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
  ros::init(argc, argv, "game_node");

  GameNode GN;
  GN.openIntroWindow();

  //ros::spin();
  GN.~GameNode();
  return 0;
}
