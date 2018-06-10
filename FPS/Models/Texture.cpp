#include "Texture.h"

GLuint Texture::readTexture(const char * filename)
{
	GLuint tex = 1;

	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pami�ci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do kt�rych wczytamy wymiary obrazka
							  //Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);
	
	//Import do pami�ci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
									   //Wczytaj obrazek do pami�ci KG skojarzonej z uchwytem
	//glfwLoadTexture2D(filename, 0);
	
	//glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
	//	GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
	//core profile:
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	return tex;

}

Texture::Texture(const char * filename)
{
	tex = readTexture(filename);
}

Texture::~Texture()
{
	glDeleteTextures(1, &tex);
}

GLuint Texture::getTexture()
{
	return tex;
}

