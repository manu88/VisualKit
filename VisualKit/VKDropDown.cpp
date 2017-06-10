//
//  VKDropDown.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 04/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKDropDown.hpp"
#include "VK.hpp"
#include "VKWindow.hpp"


VKDropDown::VKDropDown():
selectionDidChange(nullptr),
_selIndex(-1),
_isExtended(false)
{
    
    identifier = "VKDropDown";
    background = GXColors::Gray;
    setOpaque(false);
    
    /*
    _items.push_back("1st Item");
    _items.push_back("2nd Item");
    _items.push_back("3d Item");
     */
}

void VKDropDown::setItems( const VKContextMenu::Items &items) noexcept
{
    _items = items;
}

void VKDropDown::contextMenuDidDismiss( VKContextMenu* menu)
{
    //printf("Context returned index %zi\n" , menu->getSelectedIndex());
    _isExtended = false;
    _selIndex = menu->getSelectedIndex();
    setNeedsRedraw();
    
    if( selectionDidChange)
    {
        selectionDidChange(this);
    }
    
    delete menu;
}

bool VKDropDown::touchBegan( const GXTouch &t)
{
    

    return true;
}

bool VKDropDown::touchEnded( const GXTouch &t)
{
    /*
    if( _isExtended)
    {
        const ssize_t index = floorf( _items.size() *   (float)t.center.y / (float)getSize().height );
        
        _selIndex = index;
        
        if( selectionDidChange)
        {
            selectionDidChange(this);
        }
    }
    */
    _isExtended = !_isExtended;
    
    if( _isExtended)
    {
        VKWindow* win = getWindow();
        assert( win );
        
        VKContextMenu* menu = new VKContextMenu();
        menu->setController( this );
        
        GXLayer* parent = const_cast< GXLayer*  >( getParent() );
        
        GXPoint c = getPos();
        while( parent)
        {
            
            VKWindow* win = dynamic_cast< VKWindow*>(parent);
            
            if( win)
            {
                break;
            }
            else
            {
                c+= parent->getPos();
            }
            parent = const_cast< GXLayer*  >( parent->getParent() );
        }

        menu->setSize(GXSizeMake(getSize().width, 200));
        
        menu->setItems( _items );
        menu->setPos( c  );
        
        win->pushContextMenu(menu);
    }
    else
    {
        VKWindow* win = getWindow();
        win->dismissCurrentContextMenu();
    }
    
    setNeedsRedraw();
    
    return true;
}





void VKDropDown::paint( GXContext* context , const GXRect& _bounds)
{
    context->addRoundedRect(_bounds , 5);
    context->setFillColor( GXColors::Gray);
    context->setStrokeColor(GXColors::Black);
    context->fill();
    context->stroke();
    
    context->beginPath();
    
    const GXFontHandle font =  context->getFontManager().getFont(VKDefaults::DefaultFont);
    context->setFontId( font );
    context->setTextSize( 20 );
    context->setTextAlignement( GXTextAlign_LEFT | GXTextAlign_MIDDLE );
    
    context->setFillColor(GXColors::Black);
    
    if( _items.empty())
    {
        return;
    }

    const size_t idx = _selIndex >= 0? _selIndex : 0;
        
    context->addText(GXPointMake( 10 ,10),/* _bounds.size.width, */_items.at( idx ) );


}
