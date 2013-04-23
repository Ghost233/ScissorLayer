//
//  ScissorLayer.cpp
//
//  Created by Ghost.
//
//

#include "ScissorLayer.h"

ScissorLayer* ScissorLayer::create()
{
    ScissorLayer* temp = new ScissorLayer();
    temp->autorelease();
    return temp;
}

ScissorLayer::ScissorLayer()
{
    clipToBounds = true;
    cocos2d::CCSize tmp = cocos2d::CCDirector::sharedDirector()->getWinSize();
    this->setViewRect(cocos2d::CCRectMake(0, 0, tmp.width, tmp.height));
}

ScissorLayer::~ScissorLayer()
{
    
}

void ScissorLayer::setViewRect(cocos2d::CCRect var)
{
    viewRect = var;
    viewSize = var.size;
    locationPoint = var.origin;
}

cocos2d::CCRect ScissorLayer::getViewRect()
{
    return viewRect;
}

void ScissorLayer::setViewSize(cocos2d::CCSize var)
{
    viewSize = var;
    viewRect.size = var;
}

cocos2d::CCSize ScissorLayer::getViewSize()
{
    return viewSize;
}

void ScissorLayer::setLocationPoint(cocos2d::CCPoint var)
{
    locationPoint = var;
    viewRect.origin = var;
}

cocos2d::CCPoint ScissorLayer::getLocationPoint()
{
    return locationPoint;
}

void ScissorLayer::beforeDraw()
{
    if (clipToBounds)
    {
#ifdef OpenGLES_2_0
        cocos2d::CCPoint screenPos = this->convertToWorldSpace(this->getParent()->getPosition());
        
        glEnable(GL_SCISSOR_TEST);
        float s = this->getScale();
        
        cocos2d::CCDirector *director = cocos2d::CCDirector::sharedDirector();
        s *= director->getContentScaleFactor();
        
        glScissor((GLint)viewRect.origin.x, (GLint)viewRect.origin.y,
                  (GLsizei)viewRect.size.width*s, (GLsizei)viewRect.size.height*s);
#else
        GLfloat planeTop[]    = {0.0f, -1.0f, 0.0f, viewRect.origin.y + viewSize.height * s};
        GLfloat planeBottom[] = {0.0f, 1.0f, 0.0f, -viewRect.origin.y};
        GLfloat planeLeft[]   = {1.0f, 0.0f, 0.0f, -viewRect.origin.x};
        GLfloat planeRight[]  = {-1.0f, 0.0f, 0.0f, viewRect.origin.x + viewSize.width * s};
        
        glClipPlanef(GL_CLIP_PLANE0, planeTop);
        glClipPlanef(GL_CLIP_PLANE1, planeBottom);
        glClipPlanef(GL_CLIP_PLANE2, planeLeft);
        glClipPlanef(GL_CLIP_PLANE3, planeRight);
        glEnable(GL_CLIP_PLANE0);
        glEnable(GL_CLIP_PLANE1);
        glEnable(GL_CLIP_PLANE2);
        glEnable(GL_CLIP_PLANE3);
#endif
    }
}

void ScissorLayer::afterDraw()
{
    if (clipToBounds)
    {
#ifdef OpenGLES_2_0
        glDisable(GL_SCISSOR_TEST);
#else
        glDisable(GL_CLIP_PLANE0);
        glDisable(GL_CLIP_PLANE1);
        glDisable(GL_CLIP_PLANE2);
        glDisable(GL_CLIP_PLANE3);
#endif
    }
}

void ScissorLayer::visit()
{
    this->beforeDraw();
    this->CCNode::visit();
    this->afterDraw();
}