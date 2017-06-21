//
//  VKContextMenu.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 09/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKContextMenu_hpp
#define VKContextMenu_hpp

#include <string>
#include <vector>

#include "VKView.hpp"


class VKContextMenu;

class VKContextMenuController
{
public:
    
    
    virtual void contextMenuDidDismiss( VKContextMenu* ) = 0;
};

class VKContextMenu : public VKView
{
public:
    
    typedef std::vector<std::string> Items;
    
    VKContextMenu();
    
    virtual ~VKContextMenu();
    
    void setController( VKContextMenuController* controller )
    {
        _controller = controller;
    }
    
    ssize_t getSelectedIndex() const noexcept
    {
        return _selIndex;
    }
    
    
    const std::string& getSelectedItem() const
    {
        return _items.at(_selIndex);
    }
    
    
    const Items& getItems() const noexcept
    {
        return _items;
    }
    
    void setItems( const Items &) noexcept;
    
    VKContextMenuController* _controller;
    
    bool touchEnded( const GXTouch &t) override;
    
private:
    void paint( GXContext*  , const GXRect& ) override;
    
    
    
    ssize_t _selIndex;
    Items _items;
};

#endif /* VKContextMenu_hpp */
