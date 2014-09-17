#include "SDL_test_common.h"
#include "SDL2_gfxPrimitives.h"


/* Screen size */
#define WIDTH	DEFAULT_WINDOW_WIDTH
#define HEIGHT	DEFAULT_WINDOW_HEIGHT

/* viewport border */
#define BORDER	10

#define NUM_RANDOM	4096

/* Coordinates */
static Sint16 rx[NUM_RANDOM], rx[NUM_RANDOM], ry[NUM_RANDOM], ry[NUM_RANDOM];

/* Triangles */
static Sint16 tx1[NUM_RANDOM][3], tx1[NUM_RANDOM][3], ty1[NUM_RANDOM][3], ty1[NUM_RANDOM][3];

/* Squares (made of 2 triangles) */
static Sint16 sx1[NUM_RANDOM][6], sx1[NUM_RANDOM][6], sy1[NUM_RANDOM][6], sy1[NUM_RANDOM][6];

/* Line widths */
static Uint8 lw[NUM_RANDOM];

/* Radii and offsets */
static Sint16 rr1[NUM_RANDOM], rr2[NUM_RANDOM];

/* Start and stop angles */
static Sint16 a1[NUM_RANDOM], a2[NUM_RANDOM];

/* RGB colors and alpha */
static char rr[NUM_RANDOM], rg[NUM_RANDOM], rb[NUM_RANDOM], ra[NUM_RANDOM];

/*! 
\brief Generate an array of random screen coordinates, radii and RGBA values with an offset for drawing tests.

\param seed The seed for random number generation. If negative, uses current time as seed.
*/
void InitRandomPoints(int seed)
{
	int i;
	float af;

	/* Initialize random number generator */
	if (seed < 0) {
      srand((unsigned int)time(NULL));
	} else {
      srand((unsigned int)seed);
	}

	for (i=0; i<NUM_RANDOM; i++) {
		/* Random points in a quadrant */
		rx[i]=rand() % (WIDTH/2);
		ry[i]=rand() % (HEIGHT/2);

		/* 5-Pixel Triangle */
		tx1[i][0]=rx[i];
		ty1[i][0]=ry[i];
		tx1[i][1]=rx[i]+1;
		ty1[i][1]=ry[i]+2;
		tx1[i][2]=rx[i]+2;
		ty1[i][2]=ry[i]+1;

		/* 10x10 square made from 3 triangles */
		sx1[i][0]=rx[i];
		sy1[i][0]=ry[i];
		sx1[i][1]=rx[i]+10;
		sy1[i][1]=ry[i];
		sx1[i][2]=rx[i];
		sy1[i][2]=ry[i]+10;
		sx1[i][3]=rx[i];
		sy1[i][3]=ry[i]+10;
		sx1[i][4]=rx[i]+10;
		sy1[i][4]=ry[i];
		sx1[i][5]=rx[i]+10;
		sy1[i][5]=ry[i]+10;

		/* Line widths */
		lw[i]=2 + (rand() % 7);

		/* Random Radii */
		rr1[i]=rand() % 32;
		rr2[i]=rand() % 32;

		/* Random Angles */
		a1[i]=rand() % 360;
		a2[i]=rand() % 360;

		/* Random Colors */
		rr[i]=rand() & 255;
		rg[i]=rand() & 255;
		rb[i]=rand() & 255;

		/* X-position dependent Alpha */
		af=((float)rx[i]/(float)(WIDTH/2));
		ra[i]=(int)(255.0*af);
	} 
}

/* Set a viewport based on a rect with a border */
void SetViewport(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
{ 
	SDL_Rect clip;
	clip.x = x1+BORDER;
	clip.y = y1+BORDER;
	clip.w = x2-x1-2*BORDER;
	clip.h = y2-y1-2*BORDER;
	SDL_RenderSetViewport(renderer, &clip);
}

/* Set a viewport rectangle based on a rect */
void SetViewportNoBorder(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
{ 
	SDL_Rect clip;
	clip.x = x1;
	clip.y = y1;
	clip.w = x2-x1;
	clip.h = y2-y1;
	SDL_RenderSetViewport(renderer, &clip);
}

/* Clear currently set viewport rectangle (if any) */
void ClearViewport(SDL_Renderer *renderer)
{ 
	SDL_RenderSetViewport(renderer, NULL);
}

#define TLEN 256

/* Clear the screen, draw guides and color areas and titles */
void ClearScreen(SDL_Renderer *renderer, const char *title)
{
	int x,y;
	float stepx, stepy, fx, fy, fxy;
	char titletext[TLEN+1];

	/* Clear the screen */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

	/* Draw the colored area */
	stepx=1.0f/(WIDTH/2);
	stepy=1.0f/((HEIGHT-80)/2);
	fx=0.0;
	for (x=WIDTH/2; x<WIDTH; x++) {
		fy=0.0;
		for (y=(HEIGHT-40)/2+60; y<HEIGHT; y++) {
			fxy=1.0f-fx*fy;
			pixelRGBA(renderer,x,y,(int)(128.0*fx*fx),(int)(128.0*fxy*fxy),(int)(128.0*fy*fy),255);
			fy += stepy;
		}
		fx += stepx;
	}

	/* Segment and titles */
	hlineRGBA(renderer, 0, WIDTH, 40-1, 255,255,255,255);
	hlineRGBA(renderer, 0, WIDTH, 60-1, 255,255,255,255);
	hlineRGBA(renderer, 0, WIDTH, (HEIGHT-40)/2+40+1, 255,255,255,255); 
	hlineRGBA(renderer, 0, WIDTH, (HEIGHT-40)/2+60-1, 255,255,255,255); 
	vlineRGBA(renderer, WIDTH/2, 40, HEIGHT, 255,255,255,255);
	SDL_strlcpy(titletext,"Current Primitive: ",TLEN);
	SDL_strlcat(titletext,title,TLEN);
	SDL_strlcat(titletext,"  -  Space to continue. ESC to Quit.",TLEN);
	stringRGBA (renderer, WIDTH/2-4*strlen(titletext),10-4,titletext,255,255,0,255);
	SDL_strlcpy(titletext,"A=255 on Black",TLEN);
	stringRGBA (renderer, WIDTH/4-4*strlen(titletext),50-4,titletext,255,255,255,255);
	SDL_strlcpy(titletext,"A=0-254 on Black",TLEN);
	stringRGBA (renderer, 3*WIDTH/4-4*strlen(titletext),50-4,titletext,255,255,255,255);
	SDL_strlcpy(titletext,"A=255, Color Test",TLEN);
	stringRGBA (renderer, WIDTH/4-4*strlen(titletext),(HEIGHT-40)/2+50-4,titletext,255,255,255,255);
	SDL_strlcpy(titletext,"A=0-254 on Color",TLEN);
	stringRGBA (renderer, 3*WIDTH/4-4*strlen(titletext),(HEIGHT-40)/2+50-4,titletext,255,255,255,255);
}

/* Clear a center box for accuracy testing */
void ClearCenter(SDL_Renderer *renderer, const char *title)
{
	SDL_Rect r;
	int i, j;
	r.x = WIDTH/2 - 60;
	r.y = HEIGHT/2 - 30;
	r.w = 2 * 60;
	r.h = 2 * 25;
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &r);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &r);
	SDL_SetRenderDrawColor(renderer, 64, 64, 64, SDL_ALPHA_OPAQUE);
	for (i = -15; i < 15; i += 5) {
  	  for (j = -15; j < 15; j += 5) {
		  SDL_RenderDrawPoint(renderer, WIDTH/2 + i, HEIGHT/2 + j);
	  }
	}
	stringRGBA (renderer, WIDTH/2 - 4*strlen(title),r.y + 2,title,255,255,255,255);
}

/* !< Function pointer to a primitives test function */
typedef int (*PrimitivesTestCaseFp)(SDL_Renderer *renderer);

void ExecuteTest(SDL_Renderer *renderer, PrimitivesTestCaseFp testCase, int testNum, const char * testName)
{
	char titletext[TLEN+1];
    Uint32 then, now, numPrimitives;
	ClearScreen(renderer, testName);
	then = SDL_GetTicks();
	numPrimitives = testCase(renderer);
	now = SDL_GetTicks();
    if (now > then) {
        double fps = ((double) numPrimitives * 1000) / (now - then);
        SDL_snprintf(titletext, TLEN, "Test %2i %20s: %10.1f /sec", testNum, testName, fps);
	    stringRGBA (renderer, WIDTH/2-4*strlen(titletext),30-4,titletext,255,255,255,255);
		SDL_Log(titletext);
    }
}

/* --------------------- Tests ------------------------ */

int TestPixel(SDL_Renderer *renderer)
{
	int i;
	char r,g,b;
	int step = 1;

	/* Draw A=255 */
	SetViewport(renderer,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i += step) {
		pixelRGBA(renderer, rx[i], ry[i], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetViewport(renderer,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i += step) {
		pixelRGBA(renderer, rx[i], ry[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetViewport(renderer,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i += step) {
		pixelRGBA(renderer, rx[i], ry[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetViewport(renderer,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i += step) {
		if (rx[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		pixelRGBA(renderer, rx[i], ry[i], r, g, b, 255);
	}

	/* Clear viewport */
	ClearViewport(renderer);

	/* Accuracy test */
	ClearCenter(renderer, "1x1 pixel");
	pixelRGBA(renderer, WIDTH/2, HEIGHT/2, 255, 255, 255, 255);
	
	return (4 * NUM_RANDOM) / step;
}



int main(int argc, char *argv[])
{
    int i, done, drawn, test = 0;
    SDL_Event event;
    Uint32 then, now, frames;
    int numTests;

    /* Initialize test framework */
    state = SDLTest_CommonCreateState(argv, SDL_INIT_VIDEO);
    if (!state) {
        return 1;
    }

    SDL_Log("SDL2_gfx %i.%i.%i: testgfx", SDL2_GFXPRIMITIVES_MAJOR, SDL2_GFXPRIMITIVES_MINOR, SDL2_GFXPRIMITIVES_MICRO);
    SDL_Log("Platform: %s", SDL_GetPlatform());

    for (i = 1; i < argc;) {
        int consumed;
        consumed = SDLTest_CommonArg(state, i);
        if (consumed == 0) {
           consumed = -1;
           if (SDL_strcasecmp(argv[i], "--test") == 0) {
              if (argv[i + 1]) {
                 test = SDL_atoi(argv[i + 1]);
                 consumed = 2;
               }
            }
        }
                 
           
        if (consumed < 0) {
            fprintf(stderr,
                    "Usage: %s %s [--test N]\n",
                    argv[0], SDLTest_CommonUsage(state));
            return 1;
        }
        i += consumed;
    }
    
    if (!SDLTest_CommonInit(state)) {
        return 2;
    }

    /* Create the windows and initialize the renderers */
    for (i = 0; i < state->num_windows; ++i) {
        SDL_Renderer *renderer = state->renderers[i];
        SDL_RendererInfo info;
        SDL_GetRendererInfo(state->renderers[i], &info);
        SDL_Log("Renderer %i: %s %s", i, info.name, (info.flags | SDL_RENDERER_ACCELERATED) ? "(Accelerated)" : "");
        SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
        SDL_RenderClear(renderer);
    }

    /* Main render loop */
    frames = 0;
    then = SDL_GetTicks();
    done = 0;
    drawn = 0;
    while (!done) {
        /* Check for events */
        ++frames;
        while (SDL_PollEvent(&event)) {
            SDLTest_CommonEvent(state, &event, &done);
			switch (event.type) {
				case SDL_KEYDOWN: {
					switch (event.key.keysym.sym) {
						case SDLK_SPACE: {
							/* Switch to next test */
							test++;
							drawn = 0;
							break;
						}
					}
					break;
				}
				case SDL_MOUSEBUTTONDOWN: {
					switch (event.button.button) {
						case SDL_BUTTON_LEFT: {
							/* Switch to next test */
							test++;
							drawn = 0;
							break;
						}
						case SDL_BUTTON_RIGHT: {
							/* Switch to prev test */
							test--;
							drawn = 0;
							break;
						}
					}
					break;
				}
			}
        }

		if (!drawn) {
			/* Set test range */
			numTests = 23;
			if (test < 0) { 
				test = (numTests - 1); 
			} else {
				test = test % (numTests + 1);
			}

			/* Create random points */
			InitRandomPoints(test);

			/* Draw */
			for (i = 0; i < state->num_windows; ++i) {
				SDL_Renderer *renderer = state->renderers[i];
               
				switch (test) {
					case 0: {
						ExecuteTest(renderer, TestPixel, test, "Pixel");
						break;
					}
					case 1: {
						ExecuteTest(renderer, TestHline, test, "Hline");
						break;
					}
					case 2: {
						ExecuteTest(renderer, TestVline, test, "Vline");
						break;
					}
					case 3: {
						ExecuteTest(renderer, TestRectangle, test, "Rectangle");
						break;
					}
					case 4: {
						ExecuteTest(renderer, TestRoundedRectangle, test, "RoundedRectangle");
						break;
					}
					case 5: {
						ExecuteTest(renderer, TestBox, test, "Box");
						break;
					}
					case 6: {
						ExecuteTest(renderer, TestLine, test, "Line");
						break;
					}
					case 7: {
						ExecuteTest(renderer, TestCircle, test, "Circle");
						break;
					}
					case 8: {
						ExecuteTest(renderer, TestAACircle, test, "AACircle");
						break;
					}
					case 9: {
						ExecuteTest(renderer, TestFilledCircle, test, "FilledCircle");
						break;
					}
					case 10: {
						ExecuteTest(renderer, TestEllipse, test, "Ellipse");
						break;
					}
					case 11: {
						ExecuteTest(renderer, TestAAEllipse, test, "AAEllipse");
						break;
					}
					case 12: {
						ExecuteTest(renderer, TestFilledEllipse, test, "FilledEllipse");
						break;
					}
					case 13: {
						ExecuteTest(renderer, TestBezier, test, "Bezier");
						break;
					}
					case 14: {
						ExecuteTest(renderer, TestPolygon, test, "Polygon");
						break;
					}
					case 15: {
						ExecuteTest(renderer, TestAAPolygon, test, "AAPolygon");
						break;
					}
					case 16: {
						ExecuteTest(renderer, TestFilledPolygon, test, "FilledPolygon");
						break;
					}
					case 17: {
						ExecuteTest(renderer, TestTrigon, test, "Trigon");
						break;
					}
					case 18: {
						ExecuteTest(renderer, TestArc, test, "Arc");
						break;
					}
					case 19: {
						ExecuteTest(renderer, TestPie, test, "Pie");
						break;
					}
					case 20: {
						ExecuteTest(renderer, TestFilledPie, test, "FilledPie");
						break;
					}
					case 21: {
						ExecuteTest(renderer, TestThickLine, test, "ThickLine");
						break;
					}
					case 22: {
						ExecuteTest(renderer, TestTexturedPolygon, test, "TexturedPolygon");
						break;
					}
					case 23: {
						ExecuteTest(renderer, TestRoundedBox, test, "RoundedBox");
						break;
					}					
					default: {
						ClearScreen(renderer, "Unknown Test");
						break;
					}
				}

				SDL_RenderPresent(renderer);
			}
			drawn = 1;
		}

		/* Adjust framerate */
		SDL_Delay(25);
    }

    SDLTest_CommonQuit(state);

    /* Print out some timing information */
    now = SDL_GetTicks();
    if (now > then) {
        double fps = ((double) frames * 1000) / (now - then);
        printf("%2.2f frames per second\n", fps);
    }
    return 0;
