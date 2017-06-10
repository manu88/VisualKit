//
//  VKImage.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKImage_hpp
#define VKImage_hpp

#include "VKView.hpp"

class VKImage : public VKView
{
public:
    VKImage();
    ~VKImage();
    
    void setFile( const std::string &imgFile);
    void setBuffer( const char* buffer , size_t size);
    const std::string &getFile() const noexcept
    {
        return _filePath;
    }
protected:
    void paint( GXContext* context , const GXRect& bounds) override;
    
    bool serialize( GB::VariantMap& obj) const override;
    
private:
    GXImageHandle _imgHandle;
    
    std::string _filePath;
    char* _datas;
    size_t _dataSize;
    
    bool _reload;

};

#endif /* VKImage_hpp */
