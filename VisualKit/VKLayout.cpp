//
//  VKLayout.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 30/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include "VKLayout.hpp"


VKLayout::VKLayout( VKLayout::Direction direction ):
_dir( direction ),
_spacing(DefaultSpacing)
{
    setClassName( "VKLayout");
    
    setOpaque(false);
}
/*
void VKLayout::paint( GXContext* context , const GXRect& bounds)
{
    context->addRect(bounds);
    context->setStrokeColor(GXColors::Red);
    context->stroke();
}
*/
bool VKLayout::addChild( GXLayer* component)
{
    assert( component );
    
    GXSize currentSize = getSize();
    
    if( _dir == Horizontal)
    {
        component->setPos(GXPointMake(currentSize.width, 0));
        currentSize.width += component->getSize().width + _spacing;
        
        if( component->getSize().height > currentSize.height)
        {
            currentSize.height = component->getSize().height;
        }
    }
    else if( _dir == Vertical)
    {
        component->setPos(GXPointMake( 0 ,currentSize.height ));
        currentSize.height += component->getSize().height + _spacing;
        
        if( component->getSize().width > currentSize.width)
        {
            currentSize.width = component->getSize().width;
        }   
    }
    
    setSize(currentSize);
    
    return GXLayer::addChild(component);
}

void VKLayout::setSpacing( float val) noexcept
{
    if( _spacing != val)
    {
        _spacing = val;
        buildConstrains();
    }
}

void VKLayout::setDirection( VKLayout::Direction dir ) noexcept
{
    if( dir != _dir)
    {
        _dir = dir ;
        buildConstrains();
    }
    
}

void VKLayout::buildConstrains()
{
    
}


