//
//  VKWindow.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKWindow_hpp
#define VKWindow_hpp

#include "../../GX/include/GXLayer.hpp"

class VKWindow : public GXLayer
{
public:
    VKWindow();
    virtual ~VKWindow();
    
    
    void setWindowTitle( const std::string &) noexcept;
    const std::string &getWindowTitle() const noexcept
    {
        return _winTitle;
    }
    
protected:
    void paint( GXContext* context , const GXRect& bounds) override;
private:
    
    std::string _winTitle;
};

#endif /* VKWindow_hpp */
