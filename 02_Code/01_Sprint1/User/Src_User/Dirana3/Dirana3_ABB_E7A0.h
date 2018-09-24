/******************************************************************************/
/*                                                                            */
/*  (c) 2011 NXP B.V., All rights reserved                                    */
/*                                                                            */
/*  This source code and any compilation or derivative thereof is the         */
/*  proprietary information of NXP B.V. and is confidential in nature.        */
/*  Under no circumstances is this software to be exposed to or placed        */
/*  under an Open Source License of any type without the expressed            */
/*  written permission of NXP B.V..                                           */
/*                                                                            */
/******************************************************************************/

/******************************************************************************
 *  C-Header file for Dirana3 SRC Software 5.0                                *
 ******************************************************************************
 *
 *  %instance:     %
 *  %version:      %
 *
 *  %date_created: %
 *
 *
 *  File name:     Dirana3_ABB_E7A0.h
 *
 *  Purpose:       This file contains defines for all handles that are
 *                 mentioned in the audio user manual version TBD
 *                 The addresses are only valid for Dirana3 Audio Software
 *                 version 5.0
 *
 ******************************************************************************/

#ifndef DIRANA3_ABB_E7A0_H


/* Memory offsets of ADSP */
#define SDSP_X_OFFSET                                0xF30000UL
#define SDSP_Y_OFFSET                                0xF34000UL


/* SDSP X memory */
#define SDSP_X_SRC_CtrlTS0                           0xF30382UL
#define SDSP_X_SRC_CtrlTS1                           0xF30385UL
#define SDSP_X_SRC_CtrlTS2                           0xF30386UL
#define SDSP_X_SRC_CtrlTS3                           0xF30387UL
#define SDSP_X_SRC_CtrlTS4                           0xF30388UL
#define SDSP_X_SRC_CtrlTS5                           0xF30389UL

/* SDSP X memory relative addresses */
#define SDSP_X_SRC_CtrlTS0_REL                       0x000382UL
#define SDSP_X_SRC_CtrlTS1_REL                       0x000385UL
#define SDSP_X_SRC_CtrlTS2_REL                       0x000386UL
#define SDSP_X_SRC_CtrlTS3_REL                       0x000387UL
#define SDSP_X_SRC_CtrlTS4_REL                       0x000388UL
#define SDSP_X_SRC_CtrlTS5_REL                       0x000389UL


#define DIRANA3_ABB_E7A0_H
#endif//DIRANA3_ABB_E7A0_H

