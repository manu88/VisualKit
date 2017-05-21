//
//  VKTextInput.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKTextInput.hpp"
#include "VK.hpp"
#include "CLApplication.hpp"


VKTextInput::VKTextInput()
{
    
    setOpaque(false);
    
    _block.setBounds(GXRectMake(10, 10, 7, 15));
    _block.background = GXColorMake(0, 1., 0.35);
    
    
    
    tBlock.setInterval(800);
    tBlock.setCallback([this](GB::Timer &timer)
    {
        
        _block.setVisible( !_block.isVisible());
        _block.setNeedsDisplay();
    });
    
    setContent( "Les Iraniens ont voté massivement, vendredi 19 mai, pour reconduire le modéré Hassan Rohani à la présidence pendant quatre ans. Il a obtenu, dès le premier tour, la majorité absolue avec une confortable avance : 57 % des voix, selon les résultats officiels communiqués en fin de matinée par le ministère de l’intérieur.");
    
    _kbPos = 0;
}

void VKTextInput::focusChanged()
{
    if( hasFocus())
    {
        addChild(&_block);
        
        _block.setVisible(true);
        CLApplication::instance()->getRunLoop()->addSource(tBlock);
        setNeedsDisplay();
    }
    else
    {
        removeChild(&_block);
        CLApplication::instance()->getRunLoop()->removeSource(tBlock);
        setNeedsDisplay();
    }
}

bool VKTextInput::keyPressed(  const GXKey &key )
{
    
    if( key.key == GXKey_RIGHT)
    {
        _kbPos++;
        
        return true;
    }
    else if( key.key == GXKey_LEFT)
    {
        if( _kbPos > 0)
            _kbPos--;

        return true;
    }

    std::string c = getContent();
    
    if( key.key == GXKey_BACKSPACE)
    {
        if( !c.empty())
        {
            c.erase(c.begin() + _insertPoint-1);
            _insertPoint-=1;
            printf("Instert point %zi\n" , _insertPoint);
            //c.pop_back();
        }
    }
    else if( key.key == GXKey_ENTER)
    {
        c.insert(_insertPoint, "\n");
        //_insertPoint+=1;
    }
    else
    {
        c.insert(_insertPoint,  key.toStr() );
        //_insertPoint+=1;
    }
    setContent(c);
    setNeedsDisplay();
    
    return true;
}

bool VKTextInput::touchBegan( const GXTouch &t)
{
    _hit = true;
    _cursorPos = t.center;
    return VKView::touchBegan(t);
}

void VKTextInput::paint( GXContext* context , const GXRect& bounds)
{
    context->addRoundedRect(bounds, 5);
    context->setFillColor(GXColors::White);
    context->setStrokeColor( GXColors::Black);
    context->fill();
    context->stroke();

    /* **** **** **** **** **** **** **** **** **** **** */
    
    context->setFontSize(20);
    context->setFontId( context->getFontManager().getFont( VKDefaults::DefaultFont) );
    context->setFillColor( GXColors::Black);// GXColorMake(0, 1., 0.35) );
    
    
    const GXPoint textPos = GXPointMake(5, 10);

    _textContainer.setSize(bounds.size);
    //_textContainer.setContent(_content);
    context->setTextAlignement(GXTextAlign_LEFT | GXTextAlign_TOP);
    
    _textContainer.clearHitTests();
    _textContainer.addHitTest(_cursorPos);
    _textContainer.draw(context, textPos);

    for (const GXTextContainer::HitTest &retTest : _textContainer.getHitTestResults())
    {
        //printf("Got hit test result %i %i \n" , retTest.textPos.x , retTest.textPos.y);
        _block.setPos(GXPointMake( retTest.textPos.x, retTest.textPos.y));
    }    
}
