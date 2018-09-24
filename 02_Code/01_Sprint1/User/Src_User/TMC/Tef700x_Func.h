/**********************************************************
 * @file        Tef700x_Func.h
 * @purpose    Definition of Tef700x Func
 * @version    0.01
 * @date        22.Aug. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        22.Aug.2012              v0.01        created
 *  
  **********************************************************/
#ifndef TEF700X_FUNC_H
#define TEF700X_FUNC_H


#ifdef TEF700X_FUNC_C
#define EXTERN 
#else
#define EXTERN extern 
#endif//TEF700X_FUNC_C


//-------------------------------------------------------
//2  Related Def: Start



//2  Related Def: End
//-------------------------------------------------------


//............................................................................................
//4  Control Enum : Start



//4  Control Enum : End
//............................................................................................


//--------------------------------------------------------------
//3  Declare :Start

EXTERN void Tef700x_InitVariable(void);
EXTERN uint8_t Tef700x_InitReg(void);
EXTERN uint8_t Tef700x_SetFreq(uint16_t Freq);

//3  Declare :End
//--------------------------------------------------------------


#undef EXTERN

#endif//TEF700X_FUNC_H



