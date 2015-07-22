#include "Texolder.h"
#include "functions.h"
#include <algorithm>

Texolder::Texolder(functions* fp){
    f=fp;
}

void Texolder::setLocationX(TH& THRef, int coordinate){
	THRef.to->x = THRef.to->x - getLocationX(&THRef) + coordinate;
}
void Texolder::setLocationY(TH& THRef, int coordinate){
	THRef.to->y = THRef.to->y - getLocationY(&THRef) + coordinate;
}
int Texolder::getLocationX(TH* THRef){
	if (THRef->locationUpdateTimeStamp.x != f->timeStamp){
		THRef->locationUpdateTimeStamp.x = f->timeStamp;
		THRef->location.x = THRef->to->x;
		if (THRef->relativeTo != nullptr) THRef->location.x += getLocationX(THRef->relativeTo);
	}
	return THRef->location.x;
}
int Texolder::getLocationY(TH* THRef){
	if (THRef->locationUpdateTimeStamp.y != f->timeStamp){
		THRef->locationUpdateTimeStamp.y = f->timeStamp;
		THRef->location.y = THRef->to->y;
		if (THRef->relativeTo != nullptr) THRef->location.y += getLocationY(THRef->relativeTo);
	}
	return THRef->location.y;
}
void Texolder::renderTextures(){
	if (!sorted) sortTextures();
	for (int i = 0; i < (int)texture.size(); i++){
		if (texture[i].render){
			if (!texture[i].which){
				if (texture[i].relativeTo != nullptr){
					f->renderTexture(texture[i].layerp, *texture[i].from, getLocationX(&texture[i]), getLocationY(&texture[i]), texture[i].to->w, texture[i].to->h);
				}
				else f->renderTexture(texture[i].layerp, *texture[i].from, *texture[i].to);
			}
			else texture[i].texolderp->renderTextures();
        }
    }
}
void Texolder::sortTextures(){
    int i,j,texLength=texture.size(); TH temp; bool flag=true;
    for(i=1;(i<=texLength)&&flag;i++){
        flag=false;
        for(j=0;j<(texLength-1);j++){
            if(*texture[j+1].layerId<*texture[j].layerId){
                temp=texture[j];
                texture[j]=texture[j+1];
                texture[j+1]=temp;
                flag=true;
            }
        }
    }
	for (int i = 0; i < texLength; i++){
		if (texture[i].relativeToS != "") texture[i].relativeTo = &texture[findTexture(texture[i].relativeToS)];
		else texture[i].relativeTo = nullptr;
	}
    sorted=true;
}
int* Texolder::findLayer(std::string layerName){
    for(LH &n : layers){
        if(n.name==layerName){
            return &n.id;
        }
    }
    f->error("layer "+layerName+" does not exist. Fix the program!");
    return NULL;
}
int* Texolder::addLayer(std::string layerName){
	LH tempL;
	tempL.name = layerName;
	tempL.id = layers.size();
	layers.push_back(tempL);
	return &layers[layers.size()-1].id;
}
int Texolder::findTexture(std::string textureName){
    for(int i=0; i<(int)texture.size(); i++){
        if(texture[i].name==textureName){
            return i;
        }
    }
    f->error("texture "+textureName+" was not found. Fix the program!");
    return -1;
}
int Texolder::findTexture(int layerId){
    for(int i=0; i<(int)texture.size(); i++){
        if(*texture[i].layerId==layerId){
            return i;
        }
    }
    f->error("texture with layer Id "+f->toString(layerId)+" does not exist. Fix the program!");
    return -1;
}
void Texolder::addTexture(layer* l, int* layerId, std::string name, SDL_Rect &from, SDL_Rect &to, std::string relativeTo){
	TH tempTH; texture.push_back(tempTH); TH &cTexture = texture[texture.size() - 1];
	cTexture.layerp = l;
	cTexture.which = false;
	additionBase(layerId, name, from, to, relativeTo);
}
void Texolder::addTexture(Texolder* t, int* layerId, std::string name, SDL_Rect &from, SDL_Rect &to, std::string relativeTo){
	TH tempTH; texture.push_back(tempTH); TH &cTexture = texture[texture.size() - 1];
	cTexture.texolderp = t;
	cTexture.which = true;
	additionBase(layerId, name, from, to, relativeTo);
}
void Texolder::additionBase(int* layerId, std::string name, SDL_Rect &from, SDL_Rect &to, std::string relativeTo){
	sorted = false; TH &cTexture = texture[texture.size() - 1];
	cTexture.layerId = layerId;
	cTexture.name = name;
	cTexture.from = &from;
	cTexture.to = &to;
	cTexture.relativeToS = relativeTo;
}