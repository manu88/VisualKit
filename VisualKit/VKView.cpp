//
//  VKView.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//
#include <assert.h>
#include "VKView.hpp"
#include "VK.hpp"
#include "VKButton.hpp"

VKView::VKView():
_movingV( nullptr ),
_hasFocus(false)
{

    
}

VKView::~VKView()
{
    
}

void VKView::setFocus(bool focus) noexcept
{
    _hasFocus = focus;
    
    focusChanged();
}
bool VKView::hasFocus() const noexcept
{
    return _hasFocus;
}

bool VKView::handleFocus()
{
    return false;
}

void VKView::focusChanged()
{
    
}

void VKView::viewWillAppear()
{
    
}
void VKView::viewDidDismiss()
{
    
}

bool VKView::keyPressed(  const GXKey &key )
{
    for (GXLayer* l : getChildren())
    {
        VKView* view  = dynamic_cast<VKView*>(l);
        
        if( view->hasFocus())
        {
            view->keyPressed(key);
        }
    }
    
    return true;
}

bool VKView::touchBegan( const GXTouch &t)
{
    bool foundTouch = false;
    for (GXLayer* l : getChildren())
    {
        VKView* view  = dynamic_cast<VKView*>(l);
        if( view )
        {
            if( rectContainsPoint(l->getBounds(), t.center))
            {
                view->setFocus(true);

                if(!foundTouch && view->touchBegan({ t.center - l->getBounds().origin ,  GXTouch::Phase::Began }))
                {
                    foundTouch = true;
                    //return true;
                }
            }
            else
            {
                view->setFocus(false);
            }
        }   
    }
    return foundTouch;
}

bool VKView::touchMoved( const GXTouch &t)
{

    if( !_movingV)
    {
        for (GXLayer* l : getChildren())
        {
            VKView* view  = dynamic_cast<VKView*>(l);
            
            if( view)
            {
                if( rectContainsPoint(l->getBounds(), t.center))
                {
                    _movingV = view;
                    
                }
            }
        }
    }
    if( _movingV)
    {
        _movingV->setCenter(t.center);
    }
    
    return true;
}

bool VKView::touchEnded( const GXTouch &t)
{
    printf("Touch ended \n");
    if( _movingV)
    {
        _movingV = nullptr;
        
    }
     
    for (GXLayer* l : getChildren())
    {
        VKView* view  = dynamic_cast<VKView*>(l);
        
        if( view)
        {
            if( rectContainsPoint(l->getBounds(), t.center))
            {
                view->touchEnded({ t.center - l->getBounds().origin ,  GXTouch::Phase::Ended });
            }
        }
    }
    
    return true;
}
