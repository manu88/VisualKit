//
//  VKDropDown.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 04/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKDropDown.hpp"
#include "VK.hpp"

VKDropDown::VKDropDown():
selectionDidChange(nullptr),
_selIndex(-1),
_isExtended(false),
_defaultSize( GXSizeMakeNull())
{
    
    identifier = "VKDropDown";
    background = GXColors::Blue;
    
    /*
    _items.push_back("1st Item");
    _items.push_back("2nd Item");
    _items.push_back("3d Item");
     */
}

void VKDropDown::setItems( const VKDropDown::Items &items) noexcept
{
    _items = items;
}

bool VKDropDown::touchBegan( const GXTouch &t)
{
    
    
    
    return true;
}

bool VKDropDown::touchEnded( const GXTouch &t)
{
    
    if( _isExtended)
    {
        const ssize_t index = floorf( _items.size() *   (float)t.center.y / (float)getSize().height );
        
        //printf("Touch at %zi (%i / %i ) \n" , ratio ,t.center.y , getSize().height );
        _selIndex = index;
        
        if( selectionDidChange)
        {
            selectionDidChange(this);
        }
    }
    
    _isExtended = !_isExtended;
    
    update();
    setNeedsRedraw();
    
    return true;
}

void VKDropDown::update()
{
    if( _isExtended)
    {
        _defaultSize = getSize();
        
        const size_t count = _items.size() == 0? 1 : _items.size();
        setSize( GXSizeMake(getSize().width, count  * _defaultSize.height));
        background = GXColors::Red;
    }
    else if( !_isExtended)
    {
        setSize(_defaultSize);
        background = GXColors::Blue;
    }
}



void VKDropDown::paint( GXContext* context , const GXRect& _bounds)
{
    context->beginPath();
    
    const GXFontHandle font =  context->getFontManager().getFont(VKDefaults::DefaultFont);// context->createFont( VKDefaults::DefaultFont );
    
    context->setFontId( font );
    context->setTextSize( 20 );
    context->setTextAlignement( GXTextAlign_LEFT | GXTextAlign_MIDDLE );
    
    
    context->setFillColor(GXColors::Black);

    
    if( _items.empty())
    {
        return;
    }
    
    
    if( _isExtended)
    {
        int pt = 10;
        for( const std::string &item : _items)
        {
            context->addText(GXPointMake( 10 ,pt),/* _bounds.size.width, */item );
            pt+= 20;
        }
    }
    else
    {
        const size_t idx = _selIndex >= 0? _selIndex : 0;
        
        context->addText(GXPointMake( 10 ,10),/* _bounds.size.width, */_items.at( idx ) );
    }

}
