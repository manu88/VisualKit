//
//  VKTextInput.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKTextInput_hpp
#define VKTextInput_hpp

#include <GBTimer.hpp>
#include "VKView.hpp"
#include "VKKeyboard.hpp"


class VKTextInput : public VKView
{
public:
    VKTextInput();
    
    const std::string &getContent() const noexcept
    {
        return _content;
    }
    
    void setContent( const std::string &c) noexcept
    {
        _content = c;
    }
    
protected:
    bool keyPressed(  const GXKey &key ) override;
    bool touchBegan( const GXTouch &t) override;
    
    void paint( GXContext* context , const GXRect& bounds) override;
    void focusChanged() override;
    
    GXLayer _block;
    
    GB::Timer tBlock;
    
    std::string _content;
    size_t _insertPoint;
    size_t _kbPos;
    GXPoint _cursorPos;
    
    bool _hit;
};

#endif /* VKTextInput_hpp */
