//
//  PaoPao.cpp
//  pop
//
//  Created by long shenghua on 13-9-5.
//
//

#include "PaoPao.h"

PaoPao::PaoPao(){


}
PaoPao::~PaoPao(){}
NormalPaoPao::NormalPaoPao(){


}
NormalPaoPao::~NormalPaoPao(){}
NormalPaoPao* NormalPaoPao::createPaoPao(int PaoPaoType,int rowNum,int colNum,CCTexture2D* m_pSpriteTexture){
    NormalPaoPao* _paopao = new NormalPaoPao();
    int idx = PaoPaoType;
    int idy = 0;
    if (_paopao->initWithTexture(m_pSpriteTexture, CCRectMake(64 * idx,64 * idy,64,64))) {
        _paopao->PaoPaoType = PaoPaoType;
        _paopao->rowNum = rowNum;
        _paopao->colNum = colNum;
        _paopao->checkStat = 0;
    }
    return _paopao;
}