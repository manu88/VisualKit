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
_hasFocus(false),
_minSize( GXSizeInvalid),
_maxSize( GXSizeInvalid)
{

    
}

VKView::~VKView()
{
    
}


void VKView::setFocus(bool focus) noexcept
{
    if( _hasFocus != focus)
    {
        _hasFocus = focus;
        focusChanged();
    }
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
{}

void VKView::setBounds( const GXRect& b) noexcept
{
    if(   ( _minSize != GXSizeInvalid && b.size < _minSize)
       || ( _maxSize != GXSizeInvalid && b.size > _maxSize))
    {
        return ;
    }
    
    GXLayer::setBounds( b );
}

void VKView::setMinSize( const GXSize &s) noexcept
{
    if( _minSize != s)
    {
        _minSize = s;
    }
}

void VKView::setMaxSize( const GXSize &s) noexcept
{
    if( _maxSize != s)
    {
        _maxSize = s;
    }
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


bool VKView::onScroll( const GXScroll &scr)
{
    
    
    for (GXLayer* l : getChildren())
    {
        VKView* view  = dynamic_cast<VKView*>(l);
        if( view )
        {
            if( rectContainsPoint(l->getBounds(), scr.center))
            {
                GXScroll newScroll = scr;
                newScroll.center = scr.center - l->getPos();
                if(view->onScroll(newScroll))
                {
                    return  true;
                }
                //printf("On scroll at %i %i mov %i %i \n" ,scr.center.x , scr.center.y , scr.movement.width  , scr.movement.height );
            }
        }
    }
    
    return false;
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
    for (GXLayer* l : getChildren())
    {
        VKView* view  = dynamic_cast<VKView*>(l);
        
        if( view)
        {
            if( rectContainsPoint(l->getBounds(), t.center))
            {
                if(view->touchMoved({ t.center - l->getBounds().origin ,  GXTouch::Phase::Ended }))
                {
                    return true;
                }
            }
        }
    }
    
    return false;
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

VKWindow* VKView::getWindow() const noexcept
{
    GXLayer* parent = const_cast< GXLayer*  >( getParent() );
    
    while( parent)
    {
        
        VKWindow* win = dynamic_cast< VKWindow*>(parent);
        
        if( win)
        {
            return win;
        }
        parent = const_cast< GXLayer*  >( parent->getParent() );
    }
    
    return nullptr;
}


bool VKView::serialize( GB::VariantMap& obj) const
{
    
    obj.insert(std::make_pair("Class", getClassName() ));
    
    obj.insert(std::make_pair("Bounds", GB::Variant
                              ({ getBounds().origin.x ,getBounds().origin.y,getBounds().size.width , getBounds().size.height }))
               );
    
    obj.insert(std::make_pair("Z", getZPos()));
    obj.insert(std::make_pair("Opaque", isOpaque() ));
    
    if( !identifier.empty())
    {
        obj.insert(std::make_pair("Identifier", identifier));
    }
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
