//
//  ScissorLayer.h
//
//  Created by Ghost.
//
//

#ifndef __ScissorLayer__
#define __ScissorLayer__

#include "cocos2d.h"

#define OpenGLES_2_0 1

class ScissorLayer : public cocos2d::CCNode
{
private:
    ScissorLayer();
    ~ScissorLayer();
    
/**
 *	@brief 在进入visit之后开启GL_SCISSOR_TEST,修改状态机状态
 */
virtual void beforeDraw();

/**
 *	@brief 在退出visit之前关闭GL_SCISSOR_TEST,恢复状态机
 */
virtual void afterDraw();

/**
 *	@brief 重载visit函数,插入GL_SCISSOR_TEST效果,获得自定义的剪切矩形
 */
virtual void visit();

    
public:
    static ScissorLayer* create();
    
    CC_PROPERTY(cocos2d::CCSize, viewSize, ViewSize);
    CC_PROPERTY(cocos2d::CCRect, viewRect, ViewRect);
    CC_PROPERTY(cocos2d::CCPoint, locationPoint, LocationPoint);
    CC_SYNTHESIZE(bool, clipToBounds, ClipToBounds);
};

#endif /* defined(__ScissorLayer__) */
