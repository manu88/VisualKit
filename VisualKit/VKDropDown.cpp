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
_menu(nullptr)
{
    
    setClassName( "VKDropDown");
    background = GXColors::Gray;
    setOpaque(false);

}

void VKDropDown::setItems( const VKContextMenu::Items &items) noexcept
{
    _items = items;
}

void VKDropDown::contextMenuDidDismiss( VKContextMenu* menu)
{
    assert( _menu && _menu == menu);

    _selIndex = _menu->getSelectedIndex();
    setNeedsRedraw();
    
    if( selectionDidChange)
    {
        selectionDidChange(this);
    }
    
    delete _menu;
    _menu = nullptr;
}


bool VKDropDown::touchEnded( const GXTouch &t)
{
    if( !_menu)
    {
        VKWindow* win = getWindow();
        assert( win );
        
        _menu = new VKContextMenu();
        _menu->setController( this );
        
        
        const GXPoint c = getCoordsInParent(win);
        
        _menu->setSize(GXSizeMake(getSize().width, 200));
        _menu->setPos( c  );
        _menu->setItems( _items );
        win->pushContextMenu(_menu);
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

bool VKDropDown::serialize( GB::VariantMap& obj) const
{
    GB::VariantList l;
    for( const auto &i : getItems())
    {
        l.push_back(i);
        
    }
    
    obj.insert(std::make_pair("Items", l ));
    
    return VKView::serialize(obj);
    
}
