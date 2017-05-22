//
//  VKLabel.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKLabel_hpp
#define VKLabel_hpp

#include "VKView.hpp"
#include "../../GX/include/GXTextContainer.hpp"

class VKLabel : public VKView
{
public:
    VKLabel();
    
    void setContent(const std::string &text) noexcept
    {
        _text.setContent( text);
    }
    
    const std::string &getContent() const noexcept
    {
        return _text.getContent();
    }
    
protected:
    void paint( GXContext* context , const GXRect& bounds) override;
    
    bool serialize( GB::VariantMap& obj) const override;
private:
    GXTextContainer _text;
};

#endif /* VKLabel_hpp */
