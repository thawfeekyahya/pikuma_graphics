#pragma once

#include <stdint.h>
class SDL_Renderer;
class SDL_Texture;

class Example {
public:
    Example()=default;
    virtual ~Example() = default;
    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void process_input()=0;
    virtual void setWindowSize(int width,int height)=0;
    virtual void setSDLRenderer(SDL_Renderer* renderer)=0;
    virtual void setColorBuffer(uint32_t* buffer)= 0;
    virtual void setColorBufferTexture(SDL_Texture* texture)= 0;
};
