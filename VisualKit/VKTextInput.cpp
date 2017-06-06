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


VKTextInput::VKTextInput():
textChanged(nullptr),
editingEnded(nullptr),

_fontSize(VKDefaults::DefautFontSize),
_textColor( GXColors::Black),
_textAlign( GXTextAlign_Default ),

_singleLine(false)
{
    
    identifier = "VKTextInput";
    setOpaque(false);
    
    _block.setBounds(GXRectMake(10, 10, 1, 15));
    _block.background = _textColor;
    _block.setPos(GXPointMake(20, 20));
    
    
    
    tBlock.setInterval(800);
    tBlock.setCallback([this](GB::Timer &timer)
    {
        
        _block.setVisible( !_block.isVisible());
        _block.setNeedsRedraw();
    });
    /*
    setContent( "Les Iraniens ont voté massivement, vendredi 19 mai, pour reconduire le modéré Hassan Rohani à la présidence pendant quatre ans. Il a obtenu, dès le premier tour, la majorité absolue avec une confortable avance : 57 % des voix, selon les résultats officiels communiqués en fin de matinée par le ministère de l’intérieur.");
    */
    _kbPos = 0;
}

void VKTextInput::focusChanged()
{
    if( hasFocus())
    {
        //addChild(&_block);
        
        _block.setVisible(true);
        //CLApplication::instance()->getRunLoop()->addSource(tBlock);
        setNeedsRedraw();
    }
    else
    {
        removeChild(&_block);
        //CLApplication::instance()->getRunLoop()->removeSource(tBlock);
        setNeedsRedraw();
    }
}

bool VKTextInput::keyPressed(  const GXKey &key )
{
    bool _textChanged = false;
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
            /*
            c.erase(c.begin() + _insertPoint-1);
            _insertPoint-=1;
            printf("Instert point %zi\n" , _insertPoint);
             */
            c.pop_back();
            _textChanged = true;
        }
    }
    else if( key.key == GXKey_ENTER)
    {
        if( _singleLine)
        {
            if( editingEnded)
                editingEnded(this);
        }
        else
        {
            //c.insert(_insertPoint, "\n");
            c.push_back('\n');
            //_insertPoint+=1;
            _textChanged = true;
        }
    }
    else
    {
        //c.insert(_insertPoint,  key.toStr() );
        c.append(key.toStr());
        //_insertPoint+=1;
        _textChanged = true;
    }
    setContent(c);
    setNeedsRedraw();
    
    if( _textChanged && textChanged)
    {
        textChanged(this);
    }
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
    
    context->setFontSize(_fontSize);
    context->setFontId( context->getFontManager().getFont( VKDefaults::DefaultFont) );
    context->setFillColor( _textColor);// GXColorMake(0, 1., 0.35) );
    
    
    const GXPoint textPos = GXPointMake(5, 5);

    _textContainer.setSize(bounds.size);
    //_textContainer.setContent(_content);
    context->setTextAlignement(  _textAlign );
    
    
    _textContainer.clearHitTests();
    _textContainer.addHitTest(_cursorPos);
    _textContainer.draw(context, textPos);

    for (const GXTextContainer::HitTest &retTest : _textContainer.getHitTestResults())
    {
//        printf("Got hit test result %i %i \n" , retTest.textPos.x , retTest.textPos.y);
//        _block.setPos(GXPointMake( retTest.textPos.x, retTest.textPos.y));
    }    
}


void VKTextInput::setTextColor( const GXColor& col) noexcept
{
    _textColor = col;
}
