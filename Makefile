CFLAGS = -Wno-deprecated -std=c++11 -Wall #-fsanitize=address -fno-omit-frame-pointer
LFLAGS = -O2 #-g -fsanitize=address
CXX = clang++
LIBS =
LIBS += -lSDL2 -lGL -lGLU -lSDL2_image -lGLEW
LIBS += -lovr -lpthread -lX11 -ludev -lXinerama -lXrandr
TARGET = main
INCLUDE = -I./Include


OVR_SDK = /home/gaultier/OculusSDK0.3.2/LibOVR



all: target

target: main.o Star.o Parser.o SceneOpenGL.o Shader.o Cube.o Crystal.o Input.o Texture.o Camera.o
	$(CXX) -o $(TARGET) $^ $(LIBS) $(LFLAGS) $(INCLUDE)

main.o: main.cpp
	$(CXX) -c $^ $(CFLAGS) $(INCLUDE)

Star.o: Star.cpp
	$(CXX) -c $^ $(CFLAGS) $(INCLUDE)

Parser.o: Parser.cpp
	$(CXX) -c $^ $(CFLAGS) $(INCLUDE)

SceneOpenGL.o: SceneOpenGL.cpp SceneOpenGL.h
	$(CXX) -c $^ $(CFLAGS) $(INCLUDE)

Shader.o: Shader.cpp Shader.h
	$(CXX) -c $^ $(CFLAGS) $(INCLUDE)

Cube.o: Cube.cpp Cube.h
	$(CXX) -c $^ $(CFLAGS) $(INCLUDE)

Crystal.o: Crystal.cpp Crystal.h
	$(CXX) -c $^ $(CFLAGS) $(INCLUDE)

Input.o: Input.cpp Input.h
	$(CXX) -c $^ $(CFLAGS) $(INCLUDE)

Texture.o: Texture.cpp Texture.h
	$(CXX) -c $^ $(CFLAGS) $(INCLUDE)

Camera.o: Camera.cpp Camera.h
	$(CXX) -c $^ $(CFLAGS) $(INCLUDE)

clean:
	rm -f *.o *.gch $(TARGET)
