//
//  VKBuilderMainView.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "BuilderMainView.hpp"
#include "BuilderToolBox.hpp"

BuilderMainView::BuilderMainView():
_selected(nullptr)
{
    background = GXColorMake( 0.96f ,0.96f ,0.96f);
    
    _toolBox = new BuilderToolBox( this);
    _toolBox->setBounds(GXRectMake(0, 0, 300, 400));
    addChild(_toolBox);
    
    
    _image.setBounds(GXRectMake(300, 500, 200, 100));
    _image.setFile("img.png");
    addChild(&_image);
}

void BuilderMainView::addButton(VKSender* sender)
{
    VKButton* bton = new VKButton;
    
    bton->setSize(GXSizeMake(60, 20));
    bton->setCenter(getCenter());
    addChild(bton);
    
}


bool BuilderMainView::touchBegan( const GXTouch &t)
{
    
    for( GXLayer *c : getChildren())
    {
        VKView* subV = dynamic_cast<VKView*>(c);
        if( subV == _toolBox)
            continue;
        if( subV && rectContainsPoint(subV->getBounds(), t.center))
        {
            _selected = subV;
            itemSelectionChanged();
            break;
        }
    }
    return VKView::touchBegan(t);
}

void BuilderMainView::itemSelectionChanged()
{
    VKButton* bt = dynamic_cast<VKButton*>(_selected);
    if( bt)
    {
        _toolBox->_text.setContent(bt->getText());
        _toolBox->_text.setNeedsDisplay();
        
        return;
    }
    
    VKImage* img = dynamic_cast<VKImage*>(_selected);
    if( img)
    {
        _toolBox->_text.setContent( img->getFile());
        _toolBox->_text.setNeedsDisplay();
    }
    
    _toolBox->_inWidth.setContent( std::to_string(_selected->getSize().width));
    _toolBox->_inHeight.setContent( std::to_string(_selected->getSize().height));
    
    _toolBox->_inHeight.setNeedsDisplay();
    _toolBox->_inWidth.setNeedsDisplay();
    
}

void BuilderMainView::widthContentChanged( VKSender* sender)
{
    if( _selected)
    {
        const int newW = std::stoi( _toolBox->_inWidth.getContent());
        printf("new width %i\n" , newW);
        _selected->setSize(GXSizeMake( newW, _selected->getSize().height) );
        
        _selected->setNeedsDisplay();
    }
}

void BuilderMainView::heightContentChanged( VKSender* sender)
{
    if( _selected)
    {
        const int newH = std::stoi( _toolBox->_inHeight.getContent());
        printf("new height %i\n" , newH);
        _selected->setSize(GXSizeMake( _selected->getSize().width,newH ));
        _selected->setNeedsDisplay();
    }
}

void BuilderMainView::textContentChanged( VKSender* sender)
{
    if( sender == &_toolBox->_text)
    {
        if( _selected)
        {
            VKButton* bt = dynamic_cast<VKButton*>(_selected);
            if( bt)
            {
                bt->setText(_toolBox->_text.getContent());
                bt->setNeedsDisplay();
                
                return;
            }
            
            VKImage* img = dynamic_cast<VKImage*>(_selected);
            if( img)
            {
                img->setFile(_toolBox->_text.getContent());
                img->setNeedsDisplay();
            }
        }
    }
}

bool BuilderMainView::keyPressed(  const GXKey &key )
{
    if( _selected && key.key == GXKey_UP)
    {

        _selected->setPos( _selected->getPos() - GXPointMake(0, 5));
        _selected->setNeedsDisplay();
    }
    else if( _selected && key.key == GXKey_DOWN)
    {
        
        _selected->setPos( _selected->getPos() + GXPointMake(0, 5));
        _selected->setNeedsDisplay();
    }
    else if( _selected && key.key == GXKey_LEFT)
    {
        
        _selected->setPos( _selected->getPos() - GXPointMake(5, 0));
        _selected->setNeedsDisplay();
    }
    else if( _selected && key.key == GXKey_RIGHT)
    {
        
        _selected->setPos( _selected->getPos() + GXPointMake(5, 0));
        _selected->setNeedsDisplay();
    }
    
    
    return VKView::keyPressed(key);
}
