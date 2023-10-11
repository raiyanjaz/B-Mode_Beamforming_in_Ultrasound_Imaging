# B-Mode_Beamforming_in_Ultrasound_Imaging
A program that generates a B-mode image containing multiple scanlines from echoes received from an ultrasound transducer.

# Command line input to generate the image
g++ -g ImageDisplay.cpp EBO.cpp VAO.cpp VBO.cpp Texture.cpp shaderClass.cpp glew.c -Llib -lglfw3 -lopengl32 -lwinmm -lgdi32 -Iinclude -DGLEW_STATIC Bmode.cpp dataBuffer.cpp BmodeClass.cpp imageParam.cpp -o bmode
