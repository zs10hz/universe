INC=include
DEF=-I$(INC) -c -g
OUT=out

all: $(OUT)/universe

./$(OUT):
	mkdir ./$(OUT)

$(OUT)/universe: ./$(OUT) $(OUT)/common.a $(OUT)/common_gl_window_X.o $(OUT)/common_gl_vector3.o $(OUT)/common_gl_camera.o $(OUT)/common_gl_texture.o $(OUT)/common_gl_ftfont.o $(OUT)/common_gl_fttext.o $(OUT)/main.o
	g++ $(OUT)/common_gl_window_X.o $(OUT)/common_gl_vector3.o $(OUT)/common_gl_camera.o $(OUT)/common_gl_texture.o $(OUT)/common_gl_ftfont.o $(OUT)/common_gl_fttext.o $(OUT)/main.o $(OUT)/common.a -g -lpthread -lglut -lX11 -lXtst `freetype-config --libs` -o $(OUT)/universe

$(OUT)/common.a: common/* common/*/*
	make -f common.makefile -e "OUT=$(OUT)" -e "DEF=$(DEF)"

$(OUT)/main.o: main.cpp
	g++ -I$(INC) -g `freetype-config --cflags` -c main.cpp -o $(OUT)/main.o

$(OUT)/common_gl_ftfont.o: common_gl/common_gl_ftfont/common_gl_ftfont.cpp include/common_gl_ftfont.h include/common_gl_texture.h
	g++ -I$(INC) -g `freetype-config --cflags` -c common_gl/common_gl_ftfont/common_gl_ftfont.cpp -o $(OUT)/common_gl_ftfont.o

$(OUT)/common_gl_texture.o: common_gl/common_gl_texture/common_gl_texture.cpp include/common_gl_texture.h
	g++ -I$(INC) -g -c common_gl/common_gl_texture/common_gl_texture.cpp -o $(OUT)/common_gl_texture.o

$(OUT)/common_gl_fttext.o: common_gl/common_gl_fttext/common_gl_fttext.cpp include/common_gl_fttext.h include/common_gl_ftfont.h
	g++ -I$(INC) -g `freetype-config --cflags` -c common_gl/common_gl_fttext/common_gl_fttext.cpp -o $(OUT)/common_gl_fttext.o

$(OUT)/common_gl_camera.o: common_gl/common_gl_camera/common_gl_camera.cpp include/common_gl_camera.h include/common_gl_vector3.h
	g++ -I$(INC) -g common_gl/common_gl_camera/common_gl_camera.cpp -c -o $(OUT)/common_gl_camera.o

$(OUT)/common_gl_vector3.o: common_gl/common_gl_vector3/common_gl_vector3.cpp include/common_gl_vector3.h
	g++ -I$(INC) -g common_gl/common_gl_vector3/common_gl_vector3.cpp -c -o $(OUT)/common_gl_vector3.o

$(OUT)/common_gl_window_X.o: common_gl/common_gl_window/common_gl_window_X.cpp include/common_gl_window_X.h include/common_gl_window.i
	g++ -I$(INC) -g common_gl/common_gl_window/common_gl_window_X.cpp -c -o $(OUT)/common_gl_window_X.o

clean:
	rm -f $(OUT)/universe $(OUT)/*.o *.~* *.*~
