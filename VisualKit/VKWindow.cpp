//
//  VKWindow.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKWindow.hpp"
#include "VK.hpp"
#include "CLApplication.hpp"

VKWindow::VKWindow():
_currentContextMenu(nullptr)
{
    background = GXColors::DarkGray;
}

VKWindow::~VKWindow()
{
    
}

void VKWindow::setWindowTitle( const std::string &title) noexcept
{
    if( _winTitle != title)
    {
        _winTitle = title;
    }
}

void VKWindow::paint( GXContext* context , const GXRect& bounds)
{
    const GXFontHandle font = context->getFontManager().getFont(VKDefaults::DefaultFont);//context->createFont(  VKDefaults::DefaultFont );
    
    context->setFontId( font );
    context->setTextSize( 20 );
    context->setTextAlignement( GXTextAlign_CENTER | GXTextAlign_MIDDLE );
    
    
    context->setFillColor(GXColors::White);
    
    
    context->addTextBox(GXPointMake(bounds.size.width /2 , 10), 200, _winTitle );
    
    context->setTextAlignement( GXTextAlign_RIGHT | GXTextAlign_MIDDLE );
    context->addTextBox(GXPointMake(bounds.size.width  - 130 , 10), 120, std::to_string(CLApplication::instance()->getFPS()) );
}


bool VKWindow::dismissCurrentContextMenu()
{
    if( !_currentContextMenu)
    {
        return false;
    }
    
    
    if(!removeChild( _currentContextMenu))
    {
        assert(false);
    }
    
    if( _currentContextMenu->_controller)
    {
        _currentContextMenu->_controller->contextMenuDidDismiss( _currentContextMenu );
    }
    printf("Remove previous context menu \n");
    _currentContextMenu = nullptr;
    setNeedsRedraw();
    return true;
}
bool VKWindow::pushContextMenu( VKContextMenu* v)
{
    assert(v);
    if (!v)
        return false;
    
    dismissCurrentContextMenu();
    assert( _currentContextMenu == nullptr);
    _currentContextMenu = v;
    _currentContextMenu->setZPos(180);
    addChild(_currentContextMenu);
    return true;
}


bool VKWindow::touchBegan( const GXTouch &t)
{
    if( _currentContextMenu)
    {
        GXTouch tt = t;
        tt.center  = t.center - _currentContextMenu->getPos();
        
        
        
        if(rectContainsPoint(_currentContextMenu->getBounds(), t.center))
        {
            return _currentContextMenu->touchBegan(tt);
        }
        
        dismissCurrentContextMenu();
        return true;
    }
    return VKView::touchBegan(t);
}

bool VKWindow::touchEnded( const GXTouch &t)
{
    if( _currentContextMenu)
    {
        GXTouch tt = t;
        tt.center  = t.center - _currentContextMenu->getPos();
        
        if(rectContainsPoint(_currentContextMenu->getBounds(), t.center))
        {
            if( _currentContextMenu->touchEnded(tt))
            {
                dismissCurrentContextMenu();
                return true;
            }
        }
        
        dismissCurrentContextMenu();
        return true;
    }
    return VKView::touchEnded(t);
}
bool VKWindow::touchMoved( const GXTouch &t)
{
    if( _currentContextMenu)
    {
        GXTouch tt = t;
        tt.center  = t.center - _currentContextMenu->getPos();
        
        if(rectContainsPoint(_currentContextMenu->getBounds(), tt.center))
        {
            return _currentContextMenu->touchMoved(tt);
        }
        
        dismissCurrentContextMenu();
        return true;
    }
    return VKView::touchMoved(t);
}
