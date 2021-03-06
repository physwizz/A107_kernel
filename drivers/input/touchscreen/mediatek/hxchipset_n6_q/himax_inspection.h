/* SPDX-License-Identifier: GPL-2.0 */
#include "himax_platform.h"
#include "himax_common.h"
#include "himax_ic_core.h"

/*#define HX_GAP_TEST*/
/*#define HX_INSPECT_LPWUG_TEST*/
/*#define HX_ACT_IDLE_TEST*/

#define HX_RSLT_OUT_PATH  "/data/vendor/fac_sources/"  // add by songbinbo.wt for himax tp open short  20190606
#define HX_RSLT_OUT_FILE "hx_test_result.txt"
#define PI(x...) pr_info(x)

#define BS_RAWDATANOISE	10
#define BS_OPENSHORT	0


#define	BS_LPWUG	1
#define	BS_LPWUG_dile	1



#define	BS_ACT_IDLE	1


/* skip notch & dummy */
#define SKIP_NOTCH_START	5
#define SKIP_NOTCH_END	10
/* TX+SKIP_NOTCH_START */
#define SKIP_DUMMY_START	23
/* TX+SKIP_NOTCH_END*/
#define SKIP_DUMMY_END	28


#define	NOISEFRAME	(BS_RAWDATANOISE+1)
#define NORMAL_IDLE_RAWDATA_NOISEFRAME	10
#define LPWUG_RAWDATAFRAME	1
#define LPWUG_NOISEFRAME     				1
#define LPWUG_IDLE_RAWDATAFRAME     		1
#define LPWUG_IDLE_NOISEFRAME     			1

#define OTHERSFRAME	2

#define	UNIFMAX	500


/*Himax MP Password*/
#define	PWD_OPEN_START	0x77
#define	PWD_OPEN_END	0x88
#define	PWD_SHORT_START	0x11
#define	PWD_SHORT_END	0x33
#define	PWD_RAWDATA_START	0x00
#define	PWD_RAWDATA_END	0x99
#define	PWD_NOISE_START	0x00
#define	PWD_NOISE_END	0x99
#define	PWD_SORTING_START	0xAA
#define	PWD_SORTING_END	0xCC


#define PWD_ACT_IDLE_START		0x22
#define PWD_ACT_IDLE_END		0x44



#define PWD_LPWUG_START	0x55
#define PWD_LPWUG_END	0x66

#define PWD_LPWUG_IDLE_START	0x50
#define PWD_LPWUG_IDLE_END	0x60


/*Himax DataType*/
#define DATA_SORTING	0x0A
#define DATA_OPEN	0x0B
#define DATA_MICRO_OPEN	0x0C
#define DATA_SHORT	0x0A
#define DATA_RAWDATA	0x0A
#define DATA_NOISE	0x0F
#define DATA_BACK_NORMAL	0x00
#define DATA_LPWUG_RAWDATA	0x0C
#define DATA_LPWUG_NOISE	0x0F
#define DATA_ACT_IDLE_RAWDATA	0x0A
#define DATA_ACT_IDLE_NOISE	0x0F
#define DATA_LPWUG_IDLE_RAWDATA	0x0A
#define DATA_LPWUG_IDLE_NOISE	0x0F

/*Himax Data Ready Password*/
#define	Data_PWD0	0xA5
#define	Data_PWD1	0x5A

/* ASCII format */
#define ASCII_LF	(0x0A)
#define ASCII_CR	(0x0D)
#define ASCII_COMMA	(0x2C)
#define ASCII_ZERO	(0x30)
#define CHAR_EL	'\0'
#define CHAR_NL	'\n'
#define ACSII_SPACE	(0x20)
/* INSOECTION Setting */
/*extern int HX_CRITERIA_ITEM;*/
/*extern int HX_CRITERIA_SIZE;*/
/*extern char *g_file_path;*/
/*extern char *g_rslt_data;*/
void himax_inspection_init(void);
extern int *g_inspt_crtra_flag;

typedef enum {
	HIMAX_INSPECTION_OPEN,
	HIMAX_INSPECTION_MICRO_OPEN,
	HIMAX_INSPECTION_SHORT,
	HIMAX_INSPECTION_RAWDATA,
	HIMAX_INSPECTION_BPN_RAWDATA,
	HIMAX_INSPECTION_NOISE,
	HIMAX_INSPECTION_SORTING,
	HIMAX_INSPECTION_BACK_NORMAL,

	HIMAX_INSPECTION_GAPTEST_RAW,

	HIMAX_INSPECTION_ACT_IDLE_RAWDATA,
	HIMAX_INSPECTION_ACT_IDLE_NOISE,

	HIMAX_INSPECTION_LPWUG_RAWDATA,
	HIMAX_INSPECTION_LPWUG_NOISE,
	HIMAX_INSPECTION_LPWUG_IDLE_RAWDATA,
	HIMAX_INSPECTION_LPWUG_IDLE_NOISE,

} THP_INSPECTION_ENUM;


typedef enum {
	IDX_RAWMIN		= 0,
	IDX_RAWMAX,
	IDX_BPN_RAWMIN,
	IDX_BPN_RAWMAX,
	IDX_SHORTMIN,
	IDX_SHORTMAX,
	IDX_OPENMIN,
	IDX_OPENMAX,
	IDX_M_OPENMIN,
	IDX_M_OPENMAX,
	IDX_NOISEMAX,
	IDX_SORTMIN,
	IDX_SORTMAX,

	IDX_GAP_HOR_RAWMAX,
	IDX_GAP_HOR_RAWMIN,
	IDX_GAP_VER_RAWMAX,
	IDX_GAP_VER_RAWMIN,

	IDX_ACT_IDLE_NOISE_MIN,
	IDX_ACT_IDLE_NOISE_MAX,
	IDX_ACT_IDLE_RAWDATA_MIN,
	IDX_ACT_IDLE_RAWDATA_MAX,

	IDX_LPWUG_NOISE_MIN,
	IDX_LPWUG_NOISE_MAX,
	IDX_LPWUG_RAWDATA_MIN,
	IDX_LPWUG_RAWDATA_MAX,

	IDX_LPWUG_IDLE_NOISE_MIN,
	IDX_LPWUG_IDLE_NOISE_MAX,
	IDX_LPWUG_IDLE_RAWDATA_MIN,
	IDX_LPWUG_IDLE_RAWDATA_MAX,

} HX_CRITERIA_ENUM;

/* Error code of Inspection */
typedef enum {
	HX_INSPECT_OK	= 0,               /* OK */
	HX_INSPECT_EFILE = 0x0001,					/*Criteria file error*/
	HX_INSPECT_ERAW = 0x0002,        /* Raw data error */
	HX_INSPECT_ENOISE = 0x0004,        /* Noise error */
	HX_INSPECT_EOPEN = 0x0008,        /* Sensor open error */
	HX_INSPECT_EMOPEN = 0x0010,        /* Sensor micro open error */
	HX_INSPECT_ESHORT = 0x0020,        /* Sensor short error */

	HX_INSPECT_EGAP_RAW = 0x0040,        /* Raw Data GAP  */

	HX_INSPECT_EACT_IDLE_RAW = 0x0080,		   /* ACT_IDLE RAW ERROR */
	HX_INSPECT_EACT_IDLE_NOISE = 0x0100,		   /* ACT_IDLE NOISE ERROR */

	HX_INSPECT_ELPWUG_RAW = 0x0200,		   /* LPWUG RAW ERROR */
	HX_INSPECT_ELPWUG_NOISE = 0x0400,		   /* LPWUG NOISE ERROR */
	HX_INSPECT_ELPWUG_IDLE_RAW = 0x0800,		   /* LPWUG IDLE RAW ERROR */
	HX_INSPECT_ELPWUG_IDLE_NOISE = 0x1000,		   /* LPWUG IDLE NOISE ERROR */

	HX_INSPECT_EGETRAW = 0x20000,	/* Get raw data errors */
	/*HX_INSPECT_ESPI = , */        /*SPI communication error,no use*/
} HX_INSPECT_ERR_ENUM;
