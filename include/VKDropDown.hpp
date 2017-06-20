//
//  VKDropDown.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 04/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKDropDown_hpp
#define VKDropDown_hpp


#include <string>
#include <vector>
#include "VKAction.hpp"
#include "VKView.hpp"
#include "VKContextMenu.hpp"

class VKDropDown:  public VKView , public VKSender , public VKContextMenuController
{
public:
    
    
    VKDropDown();

    ssize_t getSelectedIndex() const noexcept
    {
        return _selIndex;
    }
    
    const VKContextMenu::Items& getItems() const noexcept
    {
        return _items;
    }
    
    void setItems( const VKContextMenu::Items &) noexcept;
    
    VKAction::Action selectionDidChange;
    
    
    void contextMenuDidDismiss( VKContextMenu* menu) override;
private:
    bool serialize( GB::VariantMap& obj) const override;
    
    void paint( GXContext* context , const GXRect& _bounds) override;

    bool touchEnded( const GXTouch &t) override;
    
    void update();
    
    VKContextMenu::Items _items;
    ssize_t _selIndex;

    VKContextMenu* _menu;

    
};

#endif /* VKDropDown_hpp */
