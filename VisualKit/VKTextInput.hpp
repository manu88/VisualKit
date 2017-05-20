//
//  VKTextInput.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKTextInput_hpp
#define VKTextInput_hpp

#include "VKView.hpp"



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
    void paint( GXContext* context , const GXRect& bounds) override;
    
    GXLayer _block;
    
    std::string _content;
};

#endif /* VKTextInput_hpp */
