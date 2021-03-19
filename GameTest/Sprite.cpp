#include "stdafx.h"
#include "Sprite.h"

#include <windows.h>
#include <stdio.h>
#include <assert.h>
//-----------------------------------------------------------------------------

#include "App/app.h"
#include "App/AppSettings.h"
#include "App/TextureLoader.h"

#include "../glut/include/GL/freeglut_ext.h"


#include "Transform.h"


std::map<std::string, Sprite::sTextureDef > Sprite::_textures;

//-----------------------------------------------------------------------------
Sprite::Sprite(GameObject* gameObject, Transform* _transform, const char* fileName, size_t nColumns, size_t nRows)
    : Component(gameObject, _transform), _numColumns(nColumns), _numRows(nRows)
{
    if (LoadTexture(fileName))
    {
        CalculateUVs();
        _vertices[0] = vec2(-(_width / 2.0f), -(_height / 2.0f));
        _vertices[1] = vec2(_width / 2.0f, -(_height / 2.0f));
        _vertices[2] = vec2(_width / 2.0f, _height / 2.0f);
        _vertices[3] = vec2(-(_width / 2.0f), _height / 2.0f);
    }
}

void Sprite::Update(float deltaTime)
{
    if (_currentAnim >= 0)
    {
        _animTime += deltaTime / 1000.0f;

        sAnimation& anim = _animations[_currentAnim];
        float duration = anim._speed * anim._frames.size();

        if (_animTime > duration)
        {
            _animTime = _animTime - duration;
        }

        int frame = (int)(_animTime / anim._speed);
        frame %= anim._frames.size();
        SetFrame(anim._frames[frame]);
    }
}

void Sprite::setTexture(const char* fileName)
{
    if (LoadTexture(fileName))
    {
        CalculateUVs();
        _vertices[0] = vec2(-(_width / 2.0f), -(_height / 2.0f));
        _vertices[1] = vec2(_width / 2.0f, -(_height / 2.0f));
        _vertices[2] = vec2(_width / 2.0f, _height / 2.0f);
        _vertices[3] = vec2(-(_width / 2.0f), _height / 2.0f);
    }
}

void Sprite::CalculateUVs()
{
    float u = 1.0f / _numColumns;
    float v = 1.0f / _numRows;
    int row = _frame / _numColumns;
    int column = _frame % _numColumns;

    _width = _texWidth * u;
    _height = _texHeight * v;
    _uvCoords[0] = vec2(u * column, v * (float)(row + 1));
    _uvCoords[1] = vec2(u * (float)(column + 1), v * (float)(row + 1));
    _uvCoords[2] = vec2(u * (float)(column + 1), v * row);
    _uvCoords[3] = vec2(u * column, v * row);
}

void Sprite::Draw()
{
//#if APP_USE_VIRTUAL_RES
//    float scalex = m_scale / APP_VIRTUAL_WIDTH;
//    float scaley = m_scale / APP_VIRTUAL_HEIGHT;
//#else
//    float scalex = m_scale;
//    float scaley = m_scale;
//#endif
//    float x = m_xpos;
//    float y = m_ypos;
//#if APP_USE_VIRTUAL_RES
//    APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
//#endif


    glPushMatrix();
    //glTranslatef(x, y, 0.0f);
    //glScalef(scalex, scaley, 0.1f);
    //glRotatef(m_angle * 180 / PI, 0.0f, 0.0f, 1.0f);
#if APP_USE_VIRTUAL_RES
    glOrtho(0.0f, APP_VIRTUAL_WIDTH, 0.0f, APP_VIRTUAL_HEIGHT, 0.0f, 1.0f);
#else
    glOrtho(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
#endif
    glMultMatrixf(transform->getLocalToWorldMatrix()._data);
    glColor4f(_colour.r, _colour.g, _colour.b, _colour.a);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glBegin(GL_QUADS);
    for (size_t i = 0; i < 4; ++i)
    {
        glTexCoord2f(_uvCoords[i].u, _uvCoords[i].v);
        glVertex2f(_vertices[i].x, _vertices[i].y);
    }
    glEnd();

    glPopMatrix();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void Sprite::SetFrame(size_t f)
{
    _frame = f;
    if (_frame > _numRows * _numColumns)
    {
        _frame = 0;
    }
    CalculateUVs();
}

void Sprite::SetAnimation(int32_t id)
{
    for (int32_t i = 0; i < _animations.size(); i++)
    {
        if (_animations[i]._id == id)
        {
            _currentAnim = i;
            return;
        }
    }
    _currentAnim = -1;
}

void Sprite::CreateAnimation(size_t id, float speed, const std::vector<int32_t>& frames)
{
    sAnimation anim;
    anim._id = id;
    anim._speed = speed;
    anim._frames = frames;
    _animations.push_back(anim);
}

bool Sprite::LoadTexture(const char* filename)
{
    if (_textures.find(filename) != _textures.end())
    {
        sTextureDef& texDef = _textures[filename];
        _texture = texDef._textureID;
        _texWidth = texDef._width;
        _texHeight = texDef._height;
        return true;
    }

    unsigned char* imageData = loadBMPRaw(filename, reinterpret_cast<unsigned int&>(_texWidth), reinterpret_cast<unsigned int&>(_texHeight), true);

    GLuint texture = 0;
    if (imageData)
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 4, _texWidth, _texHeight, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        free(imageData);
        sTextureDef textureDef = { _texWidth, _texHeight, texture };
        _textures[filename] = textureDef;
        _texture = texture;
        return true;
    }
    return false;
}