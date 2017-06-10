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
#include "VKAction.hpp"
#include "VKView.hpp"
#include "VKKeyboard.hpp"
#include "../../GX/include/GXTextContainer.hpp"
#include "VKAction.hpp"
#include "VKLabel.hpp" // for VKSimpleTextTrait



class VKTextInput : public VKView , public VKSimpleTextTrait , public VKSender
{
public:
    VKTextInput();
    
    const std::string &getContent() const noexcept
    {
        return _textContainer.getContent();
    }
    
    void setContent( const std::string &c) noexcept
    {
        _textContainer.setContent(c);
    }
    
    void setSingleLine( bool single) noexcept
    {
        _singleLine = single;
    }
    
    bool isSingleLine() const noexcept
    {
        return _singleLine;
    }
    
    VKAction::Action textChanged;
    VKAction::Action editingEnded;
    
    
    
    

protected:
    bool keyPressed(  const GXKey &key ) override;
    bool touchBegan( const GXTouch &t) override;
    
    
    bool onScroll( const GXScroll &scr) override;
    void paint( GXContext* context , const GXRect& bounds) override;
    void focusChanged() override;
    
    GXPoint _offset;
    GXTextContainer _textContainer;

    /**/
    
    GXLayer _block;
    
    GB::Timer tBlock;
    bool _singleLine;
    //std::string _content;
    size_t _insertPoint;
    size_t _kbPos;
    GXPoint _cursorPos;
    
    bool _hit;
};

#endif /* VKTextInput_hpp */
