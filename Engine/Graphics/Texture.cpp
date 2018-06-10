#include "Texture.h"

Texture::Texture()
{
	id = -1;
}
Texture::Texture(int _id)
{
	id = _id;
	if (!getTextureparams())
	{
		cout << "Error Loading image with id: " << id << endl;
	}
}
Texture::Texture(string path)
{
	id = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y);
	if (!getTextureparams())
	{
		cout << "Error Loading image: " <<path<< endl;
	}
}


//GET functions
int Texture::GetID()
{
	return id;
}
int Texture::GetWidth()
{
	return width;
}
int Texture::GetHeight()
{
	return height;
}


//LOAD texture
bool Texture::getTextureparams()
{

	if (id > 0)
	{
		int miplevel = 0;
		glBindTexture(GL_TEXTURE_2D, id);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &height);
		return true;
	}

	return false;
}
