//
//  VKContextMenu.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 09/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKContextMenu.hpp"
#include "VK.hpp"

VKContextMenu::VKContextMenu() :
_controller(nullptr),
_selIndex(-1)
{
    
    setOpaque(false);
    
    
}

VKContextMenu::~VKContextMenu()
{
    
}

void VKContextMenu::setItems( const VKContextMenu::Items &items) noexcept
{
    if( _items.size() != items.size())
    {
        const size_t count = items.size() == 0? 1 : items.size();
        setSize( GXSizeMake(getSize().width, count  * 20 ));
    }
    _items = items;
    
}


void VKContextMenu::paint( GXContext*  context , const GXRect& rect )
{
    context->addRoundedRect(rect , 5);
    context->setFillColor( GXColors::Gray);
    context->setStrokeColor(GXColors::Black);
    context->fill();
    context->stroke();
    
    context->beginPath();
    
    const GXFontHandle font =  context->getFontManager().getFont(VKDefaults::DefaultFont);// context->createFont( VKDefaults::DefaultFont );
    
    context->setFontId( font );
    context->setTextSize( 20 );
    context->setTextAlignement( GXTextAlign_LEFT | GXTextAlign_MIDDLE );
    
    context->beginPath();
    context->setFillColor(GXColors::Black);
    
    
    if( _items.empty())
    {
        return;
    }
    
    
    
    int pt = 10;
    for( const std::string &item : _items)
    {
        context->addText(GXPointMake( 10 ,pt),/* _bounds.size.width, */item );
        pt+= 20;
    }

    
}


bool VKContextMenu::touchEnded( const GXTouch &t)
{
    const ssize_t index = floorf( _items.size() *   (float)t.center.y / (float)getSize().height );
    
    _selIndex = index;
    
    //printf("Sel index %zi\n")
    return VKView::touchEnded(t);
}
