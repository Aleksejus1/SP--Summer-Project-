#include "layer.h"
#include "libs.h"

layer::layer(){
	offset = { 0, 0 };
	from = { 0, 0, 0, 0 };
	to = { 0, 0, 0, 0 };
    setZoom(1);
    setWidthZoom(1);
    setHeightZoom(1);
}

void layer::updateSize(){
    if(surface!=NULL){
        w=(int)(surface->w*zoom*zoomWidth);
        h=(int)(surface->h*zoom*zoomHeight);
    }
}

void layer::setZoom(float number){
    zoom=number;
    updateSize();
}

void layer::setWidthZoom(float number){
    zoomWidth=number;
    updateSize();
}

void layer::setHeightZoom(float number){
    zoomHeight=number;
    updateSize();
}

void layer::free(){
    layer::freeSurface();
    layer::freeTexture();
}

void layer::freeSurface(){
    if(layer::surface!=NULL){
        SDL_FreeSurface(layer::surface);
		layer::surface = nullptr;
    }
}

void layer::freeTexture(){
    if(textureOpenGL!=0){
        glDeleteTextures(1,&textureOpenGL);
        textureOpenGL=0;
    }
}