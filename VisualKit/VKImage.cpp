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
_reload(false)
{
    
}

VKImage::~VKImage()
{
    
}

void VKImage::setFile( const std::string &imgFile)
{
    _filePath = imgFile;
    _reload = true;
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
        _imgHandle = context->createImage(_filePath, 0);
        
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
