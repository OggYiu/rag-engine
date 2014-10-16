RDIR = ../
#IDIR = ../include
IDIR = ../src
ODIR = ../obj
LIBDIR = ../libs

SDLDIR = $(LIBDIR)/SDL2
SDLIDIR = $(SDLDIR)/include
SDLLIBDIR = ../libs/SDL2/lib

LUADIR = $(LIBDIR)/lua
LUAIDIR = $(LUADIR)/include
LUALIBDIR = $(LUADIR)/lib

CLAWDIR = $(LIBDIR)/claw
CLAWIDIR = $(CLAWDIR)/include
CLAWLIBDIR = $(CLAWDIR)/lib

FREETYPE_DIR = $(LIBDIR)/claw
FREETYPE_IDIR = $(FREETYPE_DIR)/include
FREETYPE_LDIR = $(FREETYPE_DIR)/lib

EIGEN_DIR = $(LIBDIR)/eigen
EIGEN_IDIR = $(EIGEN_DIR)

CC = g++
CFLAGS = -I$(IDIR) -I$(SDLIDIR) -I$(LUAIDIR) -I$(CLAWIDIR) -I$(FREETYPE_IDIR) -L$(LUALIBDIR) -L$(SDLLIBDIR) -L$(CLAWLIBDIR) -L$(FREETYPE_LDIR) -I$(EIGEN_IDIR) -std=c++11 -W -Wall -Werror -g3 -llua5.2 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -lclaw_tween -ldl -lfreetype -MD -MP

_OBJ = 	Demo.o \
		Object.o DisplayObjectBase.o DisplayObject.o DisplayObjectContainer.o Graphics.o \
		GUI_Base.o GUI_BaseContainer.o GUI_Image.o GUI_Button.o GUI_Label.o GUI_Window.o GUI_VBox.o GUI_VScrollBar.o GUI_ScrollVBox.o \
		MouseEvent.o Event.o EventListener.o EventDispatcher.o TransformEvent.o KeyboardEvent.o DragEvent.o ScrollBarEvent.o \
		Page_Gameplay.o	Page_GfxTest.o Page_LuaTest.o Page_Default.o Kernel.o Page.o Page_TestFont.o Page_TestUI.o Page_TestLinearAlgebra.o Page_TestDisplayObject.o Page_TestCO.o \
		Tweener.o DebugConsole.o GameGlobal.o Profiler.o FontMgr.o Timer.o Texture.o TextureMgr.o Transform.o Logger.o GradientRect.o \
		Entity.o Entity_Emitter.o Entity_Bot.o \
		Component_Base.o Component_Dragging.o Component_ClipContainer.o \

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

demo: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(RDIR)/demo

#$(ODIR)/Page_LuaTest.o: Page_LuaTest.cpp $(IDIR)/MouseEvent.h $(IDIR)/Kernel.h $(LUAIDIR)/lua.h $(LUAIDIR)/lualib.h $(LUAIDIR)/lauxlib.h
#	$(CC) -c -o $@ Page_LuaTest.cpp $(CFLAGS)

$(ODIR)/%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o

.PHONY: check-syntax

check-syntax: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS)
