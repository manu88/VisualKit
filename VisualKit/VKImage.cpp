//
//  VKImage.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include "VKImage.hpp"


VKImage::VKImage():
_imgHandle(GXImageInvalid),
_datas(nullptr),
_dataSize(0),
_reload(false)
{
    _type = VK_Image;
}

VKImage::~VKImage()
{
    
}

void VKImage::setFile( const std::string &imgFile)
{
    _filePath = imgFile;
    _reload = true;
}

void VKImage::setBuffer( const char* buffer , size_t size)
{
    if( buffer && size)
    {
        if( _datas )
        {
            free(_datas);
            _dataSize = 0;
            _datas = nullptr;
        }
        _dataSize = size;
        
        _datas = (char*) malloc( size);
        if( _datas)
        {
            memcpy(_datas, buffer, size);
            _reload = true;
        }
    }
}

void VKImage::paint( GXContext* context , const GXRect& bounds)
{
    if( _reload )
    {
        if( _imgHandle != GXImageInvalid)
        {
            context->deleteImage(_imgHandle);
            _imgHandle = GXImageInvalid;
        }
        assert( _imgHandle == GXImageInvalid);
        
        if( _datas && _dataSize)
        {
            _imgHandle = context->createImage(_datas, _dataSize, GXimageFlags_None);
        }
        else
        {
            _imgHandle = context->createImage(_filePath, GXimageFlags_PREMULTIPLIED);
        }
        
        _reload = false;
    }
    
    context->addRect(GXRectMake(GXPointMakeNull(), bounds.size) );
    
    if( _imgHandle != GXImageInvalid)
    {
        GXPaint imgPaint = context->imagePattern(GXPointMakeNull(), bounds.size, 0, _imgHandle, 1.f);
        
        
        
        context->setFillPainter( imgPaint);
        
        
    }
    else
    {
        //context->addRect(GXRectMake(GXPointMakeNull(), bounds.size) );
        context->setFillColor(GXColors::Black);
        
    }
    context->fill();
}

bool VKImage::serialize( GB::VariantMap& obj) const
{
    obj.insert(std::make_pair("Res", getFile()));
    return VKView::serialize(obj);
}
