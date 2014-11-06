LIB_DIR = '/home/oggyiu/dev/rag-engine/libs'
SRC_IDIR = '/home/oggyiu/dev/rag-engine/src'

SDL2_DIR = LIB_DIR + '/linux/SDL2'
SDL2_IDIR = SDL2_DIR + '/include'
SDL2_LIB_DIR = SDL2_DIR + '/lib'
SDL2_LIB_NAME = 'SDL2'
SDL2GFX_LIB_NAME = 'SDL2_gfx'
SDL2TTF_LIB_NAME = 'SDL2_ttf'
SDL2IMAGE_LIB_NAME = 'SDL2_image'

LUA_DIR = LIB_DIR + '/linux/lua'
LUA_IDIR = LUA_DIR + '/include'
LUA_LIB_DIR = LUA_DIR + '/lib'
LUA_LIB_NAME = 'lua'

CLAW_DIR = LIB_DIR + '/claw'
CLAW_IDIR = CLAW_DIR + '/include'
CLAW_LIB_DIR = CLAW_DIR + '/lib'
CLAW_LIB_NAME = 'claw_tween'

EIGEN_DIR = LIB_DIR + '/all/eigen'
EIGEN_IDIR = EIGEN_DIR

FREETYPE_LIB_NAME = 'freetype'
DL_LIB_NAME = 'dl'

env = Environment( CC = 'g++',
	  			   CCFLAGS = '-std=c++11 -W -Wall -g3 -MD -MP' )

env.Append( CPPPATH = [ SRC_IDIR, SDL2_IDIR, EIGEN_IDIR, CLAW_IDIR, LUA_IDIR ] )

env.Append( LIBS = [ SDL2_LIB_NAME, SDL2GFX_LIB_NAME, SDL2TTF_LIB_NAME, SDL2IMAGE_LIB_NAME, LUA_LIB_NAME, CLAW_LIB_NAME, FREETYPE_LIB_NAME, DL_LIB_NAME ])

env.Append( LIBPATH = [ SDL2_LIB_DIR, LUA_LIB_DIR, CLAW_LIB_DIR ] )

SConscript( 'src/SConscript', variant_dir='build', duplicate=0, exports = 'env' )