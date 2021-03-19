#pragma once
#include "../glut/include/GL/freeglut.h"
#include <map>
#include <vector>
#include <string>

#include "vec2.h"
#include "vec4.h"
#include "Component.h"


class GameObject;
class Transform;


class Sprite : public Component
{
public:
    // fileName: File must be a 32 bit BMP format (A8 R8 G8 B8). The alpha channel can be used to mask out the sprite.
    // nColumns and nRows defines the number of frames in the sprite page. 
    Sprite(GameObject* gameObject, Transform* transform, const char* fileName, size_t nColumns = 1, size_t nRows = 1);
    // Update, call from your game update function.
    void Update(float deltaTime);
    // Draw, call from your game draw function.
    void Draw();

    // Sets and Gets for the various attributes of the sprite.
    void SetFrame(size_t f);

    float GetWidth()  const { return _width; }
    float GetHeight() const { return _height; }
    size_t GetFrame()  const { return _frame; }

    // Set the sprite color. r,g,b for color and a= the alpha value (Fade).
    void SetColor(float r, float g, float b, float a = 1.0f) 
    { 
        _colour.r = r; _colour.g = g; _colour.b = b; _colour.a = a; 
    }


    // Create an animation. 
    // ID, Gives this animation a unique id.
    // speed, Set the movement speed for this sprite.
    // frames, provide a vector of sprite frame indices. Indices into your sprite page.
    void CreateAnimation(size_t id, float speed, const std::vector<int32_t>& frames);;
    // Set the current animation to play.
    // Note -1 will stop the animation.
    void SetAnimation(int32_t id);


    //------------------------------------------------------------
    // Advanced:
    //------------------------------------------------------------
    // Directly set the local coordinates of the sprite.
    // Use only if you want non uniform sprites. Skewing or perspective can be achieved using this.
    void SetVertex(size_t i, const vec2& v) 
    { 
        if (i < 4)
        {
            _vertices[i] = v;
        }
    }

    vec2 GetVertex(size_t i)
    { 
        if (i >= 4)
        {
            i = 0;
        }

        return _vertices[i]; 
    }

private:
    void CalculateUVs();
    GLuint _texture;

    float _width = 0.0F;
    float _height = 0.0F;
    size_t _texWidth = 0;
    size_t _texHeight = 0;
    vec2 _vertices[4];
    vec2 _uvCoords[4];
    vec4 _colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);

    size_t _frame;
    size_t _numColumns;
    size_t _numRows;
    int32_t _currentAnim = -1;
    float _animTime = 0.0F;


    struct sAnimation
    {
        size_t _id;
        float _speed;
        std::vector<int32_t> _frames;
    };
    std::vector<sAnimation> _animations;


    // Texture management.
    struct sTextureDef
    {
        size_t _width;
        size_t _height;
        GLuint _textureID;
    };
    bool LoadTexture(const char*);
    static std::map<std::string, sTextureDef > _textures;

};