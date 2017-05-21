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
#include "../../GX/src/nanovg/nanovg.h"
#include "../../GX/include/GXTextContainer.hpp"
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
    
    _content = "Les Iraniens ont voté massivement, vendredi 19 mai, pour reconduire le modéré Hassan Rohani à la présidence pendant quatre ans. Il a obtenu, dès le premier tour, la majorité absolue avec une confortable avance : 57 % des voix, selon les résultats officiels communiqués en fin de matinée par le ministère de l’intérieur.";
    
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

    std::string c = _content;
    
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
    /*
    context->setFontSize(20);
    context->setFontId( context->getFontManager().getFont( VKDefaults::DefaultFont) );
    context->setFillColor( GXColors::Black);// GXColorMake(0, 1., 0.35) );
    */
    
    const GXPoint textPos = GXPointMake(5, 10);
    


    
    
    GXTextContainer text( context);
    text.setSize(bounds.size);
    text.setFontSize(20);
    text.setFontId(context->getFontManager().getFont( VKDefaults::DefaultFont) );
    text.setTextColor(GXColors::Black);
    text.setContent(_content);
    context->setTextAlignement(GXTextAlign_LEFT | GXTextAlign_TOP);
    
    text.addHitTest(_cursorPos);
    text.draw( textPos);
    //context->addText(textPos, text);
    
    
    for (const GXTextContainer::HitTest &retTest : text.getHitTestResults())
    {
        printf("Got hit test result %i %i \n" , retTest.textPos.x , retTest.textPos.y);
        _block.setPos(GXPointMake( retTest.textPos.x, retTest.textPos.y));
    }
    
    
    return;
    /* **** **** **** **** **** **** **** **** **** **** */
    /*
    GXText::HitTest hitTest;
    hitTest.point = _cursorPos;
    
    const char* c = _content.c_str();

    int totalRows = 0;
    int nrows =0;
    const char* start = c;
    const char* end = c + strlen(c);
    
    float lineh;
    context->getTextMetrics(nullptr , nullptr , &lineh);
    
    int x = textPos.x;
    int y = textPos.y;
    
    int lnum = 0;
    
    //float caretx;
    float px;
    int nglyphs = 0;
    
    
    NVGtextRow rows[3];
    int currentRow = 0;
    while((nrows = context->textBreakLines( start, end, bounds.size.width , rows, 1)))
    {

        currentRow++;
        for (int i = 0; i < nrows; i++)
        {
            NVGtextRow* row = &rows[i];

            int hit = hitTest.point.x > x && hitTest.point.x < (x+bounds.size.width) && hitTest.point.y >= y && hitTest.point.y < (y+lineh);

            context->addText(GXPointMake(x, y), row->start, row->end);
            
            if (hit && _hit)
            {
                _hit = false;
                hitTest.textPos.x = (hitTest.point.x < x+row->width/2) ? x : x+row->width;
                px = x;
                
                assert(row->end > row->start);
                const size_t numG = row->end - row->start;
                
                
                NVGglyphPosition glyphs[ numG];
                
                nglyphs = nvgTextGlyphPositions(static_cast<NVGcontext*>( context->getImpl() ),
                                                x, y, row->start, row->end, glyphs, (int)numG);
                
                for (int j = 0; j < nglyphs; j++)
                {
                    float x0 = glyphs[j].x;
                    float x1 = (j+1 < nglyphs) ? glyphs[j+1].x : x+row->width;
                    float gx = x0 * 0.3f + x1 * 0.7f;
                    if (hitTest.point.x >= px && hitTest.point.x < gx)
                    {
                        const char*p = glyphs[j].str;
                        hitTest.textOffset  = p-c;
                        
                        
                        hitTest.textPos.x = glyphs[j].x;
                        
                        hitTest.textPos.y = y;
                    }
                    px = gx;
                }
                
                
            }
            
            lnum++;
            y += lineh;
        }
        
        totalRows += nrows;
        start = rows[nrows-1].next;
    }
    
    _insertPoint = hitTest.textOffset;
    printf("At pos %zi \n" , _insertPoint);
    _block.setPos(GXPointMake(hitTest.textPos.x, hitTest.textPos.y));
    */
    /* **** **** **** **** **** **** **** **** **** **** */
    
    
}
