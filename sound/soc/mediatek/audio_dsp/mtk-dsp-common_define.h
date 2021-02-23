// SPDX-License-Identifier: GPL-2.0
//
// mtk-dsp-common_define.h --  Mediatek ADSP common define
//
// Copyright (c) 2018 MediaTek Inc.
// Author: Chipeng <Chipeng.chang@mediatek.com>


#ifndef AUDIO_DSP_COMMON_DEFINE_H
#define AUDIO_DSP_COMMON_DEFINE_H

/* task command */
enum {
	AUDIO_DSP_TASK_OPEN = 0x1,
	AUDIO_DSP_TASK_CLOSE,
	AUDIO_DSP_TASK_PREPARE,
	AUDIO_DSP_TASK_HWPARAM,
	AUDIO_DSP_TASK_MSGA2DSHAREMEM,
	AUDIO_DSP_TASK_MSGD2ASHAREMEM,
	AUDIO_DSP_TASK_EINGBUFASHAREMEM,
	AUDIO_DSP_TASK_HWFREE,
	AUDIO_DSP_TASK_DLCOPY,
	AUDIO_DSP_TASK_ULCOPY,
	AUDIO_DSP_TASK_DATAREAD,
	AUDIO_DSP_TASK_CONSUMEDATA,
	AUDIO_DSP_TASK_START,
	AUDIO_DSP_TASK_STOP,
	AUDIO_DSP_TASK_SETPRAM,
	AUDIO_DSP_TASK_IRQDL,
	AUDIO_DSP_TASK_IRQUL,
	AUDIO_DSP_TASK_AURISYS_INIT,
	AUDIO_DSP_TASK_AURISYS_DEINIT,
	AUDIO_DSP_TASK_AURISYS_LIB_PARAM,
	AUDIO_DSP_TASK_PCMDUMP_ON = 0x100,
	AUDIO_DSP_TASK_PCMDUMP_DATA,
	AUDIO_DSP_TASK_PCMDUMP_OK,
	AUDIO_DSP_TASK_SHAREMEMORY_SET = 0x200,
	AUDIO_DSP_TASK_PCM_HWPARAM,
	AUDIO_DSP_TASK_PCM_HWFREE,
	AUDIO_DSP_TASK_PCM_PREPARE,
};

/* task command param1 */
enum {
	AUDIO_DSP_TASK_PCM_HWPARAM_DL = 0x1,
	AUDIO_DSP_TASK_PCM_HWPARAM_UL = 0x2,
	AUDIO_DSP_TASK_PCM_HWPARAM_REF = 0x4,
};

enum {
	AUDIO_TASK_VOIP_ID = 0,
	AUDIO_TASK_PRIMARY_ID,
	AUDIO_TASK_OFFLOAD_ID,
	AUDIO_TASK_DEEPBUFFER_ID,
	AUDIO_TASK_PLAYBACK_ID,
	AUDIO_TASK_CAPTURE_UL1_ID,
	AUDIO_TASK_A2DP_ID,
	AUDIO_TASK_DATAPROVIDER_ID,
	AUDIO_TASK_CALL_FINAL_ID,
	AUDIO_TASK_DAI_NUM,
};

enum {
	AUDIO_DSP_AFE_SHARE_MEM_ID = AUDIO_TASK_DAI_NUM,
	AUDIO_DSP_SHARE_MEM_NUM,
};

enum {
	MEMORY_AUDIO_SRAM,
	MEMORY_AUDIO_DRAM,
	MEMORY_SYSTEM_TCM,
};

enum{
	BUFFER_TYPE_SHARE_MEM,
	BUFFER_TYPE_HW_MEM
};

enum {
	ADSP_TASK_ATTR_DEFAULT,
	ADSP_TASK_ATTR_MEMDL,
	ADSP_TASK_ATTR_MEMUL,
	ADSP_TASK_ATTR_MEMREF,
	ADSP_TASK_ATTR_RUMTIME,
	ADSP_TASK_ATTR_FEATUREID,
	ADSP_TASK_ATTR_SMARTPA,
	ADSP_TASK_ATTR_NUM
};

#endif
