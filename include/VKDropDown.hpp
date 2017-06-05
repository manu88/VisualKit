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


class VKDropDown:  public VKView , public VKSender
{
public:
    
    typedef std::vector<std::string> Items;
    VKDropDown();

    ssize_t getSelectedIndex() const noexcept
    {
        return _selIndex;
    }
    
    const Items& getItems() const noexcept
    {
        return _items;
    }
    
    void setItems( const Items &) noexcept;
    
    VKAction::Action selectionDidChange;
    
private:
    void paint( GXContext* context , const GXRect& _bounds) override;
    bool touchBegan( const GXTouch &t) override;
    bool touchEnded( const GXTouch &t) override;
    
    void update();
    
    Items _items;
    ssize_t _selIndex;
    bool _isExtended;
    GXSize _defaultSize;
    
};

#endif /* VKDropDown_hpp */
