//
//  VKView.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <iostream>


#include <assert.h>
#include "VKView.hpp"
#include "VK.hpp"
#include "VKButton.hpp"

VKView::VKView():
_type(VK_View),
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

       
    return true;
}

bool VKView::touchEnded( const GXTouch &t)
{

     
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


bool VKView::serialize( GB::VariantMap& obj) const
{
    
    obj.insert(std::make_pair("Type", getType() ));
    
    obj.insert(std::make_pair("Bounds", GB::Variant
                              ({ getBounds().origin.x ,getBounds().origin.y,getBounds().size.width , getBounds().size.height }))
               );
    
    obj.insert(std::make_pair("Z", getZPos()));
    
    if( hasChildren())
    {
        GB::VariantList children;
        for (const GXLayer* l : getChildren())
        {
            const VKView* v = dynamic_cast<const VKView*>(l);
            
            GB::VariantMap c;
            if( v->serialize(c))
            {
                children.push_back(c);
            }
        }
        
        obj.insert(std::make_pair("Children", children));
    }
    return true;
}
