#include <stdio.h>
#include <time.h>
#include "Include/SDL2/SDL.h"

int init();
void kill();

SDL_Window *window;
SDL_Surface *surface;

const float SPEED = 10;

int main(int argc, char* args[]){
  
  srand(time(NULL));

  // Initialization
  if (init() != 0)
    return 1;
    
  // ==INITIALIZING OBJECTS==
  
  // Drawing Paddles
    
    // Player 1 
  SDL_Rect p1 = (SDL_Rect) {0, 40, 40, 200}; // Is a rectangle, drawn to show paddle for Player 1
  Uint32 p1_color = 0xffffff4f;                // Unsigned Integer with code Hexadecimal? (Yellow)
  SDL_FillRect(surface, &p1, p1_color);      // Surface is pointer (I guess I see why) 

    // Player 2
  SDL_Rect p2 = (SDL_Rect) {600, 40, 40, 200}; // Player 2 Paddle
  Uint32 p2_color = 0xffff4fff;               // (Magenta)
  SDL_FillRect(surface, &p2, p2_color); 
  
  // Ball
  SDL_Rect ball = (SDL_Rect) {320, 40, 40, 40};
  Uint32 ball_color = 0xff6fffff;
  SDL_FillRect(surface, &ball, ball_color);
  int towards_right = 1;
  int towards_top = 0;                        // 0 for straight, -1 for top +1 for bottom

  //    ============== GAME LOOP =================
  unsigned short gameLoop = 1;                         // C Does not have bool as built in type
  SDL_Event event;
  
  //Keep This at the bottom of the program
  while (gameLoop) {
    
    // Get Pos
    //printf("%d ", p2.y);
    //printf(" %d\n", p2.y + 200);

    // Get Inputs or Events 
    while (SDL_PollEvent(&event) != 0) {
      // Exiting Game
      switch (event.type) {
        case SDL_QUIT:
          gameLoop = 0;
          break;
      } 
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    // Keyboard Inputs

    const int bound_X = 0, bound_Y = 280;
      
      // Player 2 Inputs
    if (state[SDL_SCANCODE_UP] && p2.y > bound_X) {
      SDL_FillRect(surface, &p2, 0x00000000);
      p2.y -= SPEED;
      SDL_FillRect(surface, &p2, p2_color);
    }

    if (state[SDL_SCANCODE_DOWN] && p2.y < bound_Y) { 
      SDL_FillRect(surface, &p2, 0x00000000);
      p2.y += SPEED;
      SDL_FillRect(surface, &p2, p2_color);
    }
       // Player 1 Inputs
    if (state[SDL_SCANCODE_W] && p1.y > bound_X) {
      SDL_FillRect(surface, &p1, 0x00000000);
      p1.y -= SPEED;
      SDL_FillRect(surface, &p1, p1_color);
    }

    if (state[SDL_SCANCODE_S] && p1.y < bound_Y) {
      SDL_FillRect(surface, &p1, 0x00000000);
      p1.y += SPEED;
      SDL_FillRect(surface, &p1, p1_color);
    }


     // Ball Movement
    SDL_FillRect(surface, &ball, 0x00000000); 
    if (ball.x >= (p2.x - 40) && ball.y <= p2.y + 200 && ball.y >= p2.y) {
      towards_right = -1;
      towards_top = -1 + rand() % 3;
    }
    else if (ball.x <= (p1.x + 40) && ball.y <= p1.y + 200 && ball.y >= p1.y) {
      towards_right = 1;
      towards_top = -1 + rand() % 3;
    }
    if (towards_right == 1) {
      ball.x += rand() % 3;
    } else {
      ball.x -= rand() % 3;
    }

    // Detection of If ball has hit screen boundaries
    if (ball.y <= 0 && (ball.x != p2.x + 40 || ball.x != p2.x - 40)) {
      towards_top = -1;
    }
    else if (ball.y >= 440 && (ball.x != p2.x + 40 || ball.x != p2.x - 40)) {
      towards_top = 1;
    }
    if (towards_top == 1){
      ball.y -= rand() % 3;
    }
    else if (towards_top == -1){
      ball.y += rand() % 3;
    }

    // Scoring Check
    if (ball.x >= p2.x) {
      printf("P1 Scores!\n");
      ball.x = 320;
      towards_right = -1;
      SDL_Delay(1000);
    }
    else if (ball.x <= p1.x) {
      printf("P2 Scores!\n");
      ball.x = 320;
      towards_right = 1;
      SDL_Delay(1000);
    }
      
    SDL_FillRect(surface, &ball, ball_color);

    // Redrawing onto Window
    SDL_UpdateWindowSurface(window);
    SDL_Delay(1);
  }
 
  
  // Deallocation 
  kill();
  
  return 0;
}

int init(){

  // ---Setting Up Window----
  SDL_InitSubSystem(SDL_INIT_VIDEO);

  // Initialization of SDL 
  if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
    printf("Error Initializing SDL\n");
    system("pause");
    return 1;
  }

  // Creating Window
  window = SDL_CreateWindow("Pong Attempt 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);  
  // Check to see if Window is made
  if (window == NULL) {
    printf("Window Could not be created!\n");
    system("pause");
    return 1;
  }

  // Creating Surface to draw on
  surface = SDL_GetWindowSurface(window);  //Takes our initialized window as a surface to be drawed on

  return 0;
}

void kill(){
  // Removing All Objects from memory and Deallocation
  SDL_DestroyWindow(window);
  surface = NULL;
  window = NULL;

  SDL_Quit();

}

