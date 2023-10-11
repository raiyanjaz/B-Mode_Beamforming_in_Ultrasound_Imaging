# B-Mode Ultrasound Imaging Project Summary

In this project, I successfully developed a program to generate B-mode ultrasound images using C++. The project was an exciting exploration of ultrasound imaging, and was divided into five distinct parts, each with its own set of goals. Here's a concise summary of what I accomplished in each part:

## Part 1 – Creating the RFData Class [DataBuffer]

I designed and implemented the `dataBuffer` class, which functions as a linked list to store ultrasound data efficiently. I crafted member functions to initialize the class, allocate memory for data, load ultrasound data from files, and access the real and imaginary parts of the data. This part laid the foundation for data management in the project.

## Part 2 – Creating the imageParam Class [Image Parameters]

To ensure accurate imaging, I developed the `imageParam` class, which held crucial imaging parameters such as the number of elements, samples, scanlines, and pixel depth. I created methods to initialize the class, generate element positions based on pitch, and calculate scanline positions based on the desired imaging depth and pixel count. This part was crucial in setting up the imaging parameters.

## Part 3 – B-mode Beamforming

The core of the project involved implementing the B-mode beamforming algorithm, which is an extension of A-mode with lateral positions for different scanlines. I computed time of flight for each element, matched samples based on time, and generated the real and imaginary parts of the beamformed signal for each scanline. This step brought the actual ultrasound imaging to life.

## Part 4 – Interpretation of Main Function

I thoroughly examined the main function to understand its role in the project. I identified how imaging parameters were accessed and how data was managed within the linked list, gaining a deep understanding of the project structure and flow.

## Part 5 – Completing the Linked List Operation in Main Function

In this critical part of the project, I completed the missing section of the main function, which involved building a linked list of B-mode scanlines. I iteratively created `BmodeClass` objects, linking them together to form the scanline list. This step ensured the seamless generation of the B-mode ultrasound image.

The culmination of this project was the successful execution of the program, which displayed the B-mode ultrasound image. I provided the desired imaging depth and pixel count, and the program generated the image,

## Additional Notes

**Command line input to generate image:**
g++ -g ImageDisplay.cpp EBO.cpp VAO.cpp VBO.cpp Texture.cpp shaderClass.cpp glew.c -Llib -lglfw3 -lopengl32 -lwinmm -lgdi32 -Iinclude -DGLEW_STATIC Bmode.cpp dataBuffer.cpp BmodeClass.cpp imageParam.cpp -o bmode

_Note: Real and imaginary datasets not included due to large size._


