/**
 * @file disp.c
 * 
 */

/*********************
 *      INCLUDES
 *********************/
#include <string.h>

#include "tft.h"
#include <lvgl.h>
#include "stm32f4xx.h"
#include "stm32f429i_discovery_lcd.h"
#include "ili9341.h"

/*********************
 *      DEFINES
 *********************/

#define SDRAM_BANK_ADDR ((uint32_t)0xD0000000)

#define LV_BUFFER_SIZE  (TFT_HOR_RES * TFT_VER_RES / 8 * (LV_COLOR_DEPTH / 8))

#define DMA_STREAM DMA2_Stream0
#define DMA_CHANNEL DMA_CHANNEL_0
#define DMA_STREAM_IRQ DMA2_Stream0_IRQn
#define DMA_STREAM_IRQHANDLER DMA2_Stream0_IRQHandler

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void tft_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);

/**********************
 *  STATIC VARIABLES
 **********************/
extern LTDC_HandleTypeDef  LtdcHandler;

#if TFT_USE_GPU != 0
static DMA2D_HandleTypeDef Dma2dHandle;
#endif

#if TFT_EXT_FB != 0
static __IO uint16_t *my_fb = (__IO uint16_t *)(SDRAM_BANK_ADDR);
#else
static uint16_t my_fb[TFT_HOR_RES * TFT_VER_RES];
#endif

/*DMA to flush to frame buffer*/
static void DMA_Config(void);
static void DMA_TransferComplete(DMA_HandleTypeDef *han);
static void DMA_TransferError(DMA_HandleTypeDef *han);

DMA_HandleTypeDef DmaHandle;
static lv_display_t * lvDisplay;

static uint8_t lvBuffer[LV_BUFFER_SIZE];
static int32_t x1_flush;
static int32_t y1_flush;
static int32_t x2_flush;
static int32_t y2_fill;
static int32_t y_fill_act;
static const uint8_t *buf_to_flush;

/**********************
 *      MACROS
 **********************/



/**********************
 *   GLOBAL FUNCTIONS
 **********************/
/**
 * Initialize your display here
 */
void tft_init(void)
{
  #if LV_USE_LOG != 0
    lv_log_register_print_cb(lv_log_print_g_cb);
  #endif

  lvDisplay = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
  if (lvDisplay)
  {
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(0, (uint32_t)my_fb);
    HAL_LTDC_SetPixelFormat(&LtdcHandler, LTDC_PIXEL_FORMAT_RGB565, 0);
    DMA_Config();

    lv_display_set_color_format(lvDisplay, LV_COLOR_FORMAT_RGB565);
    lv_display_set_flush_cb(lvDisplay, tft_flush);
    lv_display_set_buffers(lvDisplay, lvBuffer, NULL, LV_BUFFER_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);
    
  #if TFT_USE_GPU != 0
    DMA2D_Config();
    disp_drv.gpu_blend_cb = gpu_mem_blend;
    disp_drv.gpu_fill_cb = gpu_mem_fill;
  #endif
  }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * LVGL Log print callback
 * @param level log message level
 * @param buf string to print 
 */
#if LV_USE_LOG != 0
static void lv_log_print_g_cb(lv_log_level_t level, const char * buf)
{
  LV_UNUSED(level);
  LV_UNUSED(buf);
}
#endif

/**
 * Flush a color buffer
 * @param x1 left coordinate of the rectangle
 * @param x2 right coordinate of the rectangle
 * @param y1 top coordinate of the rectangle
 * @param y2 bottom coordinate of the rectangle
 * @param color_p pointer to an array of colors
 */
static void tft_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map)
{
  /*Return if the area is out the screen*/
  if (area->x2 < 0)
    return;
  if (area->y2 < 0)
    return;
  if (area->x1 > TFT_HOR_RES - 1)
    return;
  if (area->y1 > TFT_VER_RES - 1)
    return;

  /*Truncate the area to the screen*/
  int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
  int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
  int32_t act_x2 = area->x2 > TFT_HOR_RES - 1 ? TFT_HOR_RES - 1 : area->x2;
  int32_t act_y2 = area->y2 > TFT_VER_RES - 1 ? TFT_VER_RES - 1 : area->y2;

  x1_flush = act_x1;
  y1_flush = act_y1;
  x2_flush = act_x2;
  y2_fill = act_y2;
  y_fill_act = act_y1;
  buf_to_flush = px_map;

  /*##-7- Start the DMA transfer using the interrupt mode #*/
  /* Configure the source, destination and buffer size DMA fields and Start DMA Stream transfer */
  /* Enable All the DMA interrupts */
  HAL_StatusTypeDef err;
  err = HAL_DMA_Start_IT(&DmaHandle, (uint32_t)buf_to_flush, (uint32_t)&my_fb[y_fill_act * TFT_HOR_RES + x1_flush],
                         (x2_flush - x1_flush + 1));
  if (err != HAL_OK)
  {
    while (1)
      ; /*Halt on error*/
  }
}

static void DMA_Config(void)
{
  /*## -1- Enable DMA2 clock #################################################*/
  __HAL_RCC_DMA2_CLK_ENABLE();

  /*##-2- Select the DMA functional Parameters ###############################*/
  DmaHandle.Init.Channel = DMA_CHANNEL;                           /* DMA_CHANNEL_0                    */
  DmaHandle.Init.Direction = DMA_MEMORY_TO_MEMORY;                /* M2M transfer mode                */
  DmaHandle.Init.PeriphInc = DMA_PINC_ENABLE;                     /* Peripheral increment mode Enable */
  DmaHandle.Init.MemInc = DMA_MINC_ENABLE;                        /* Memory increment mode Enable     */
  DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;   /* Peripheral data alignment : 16bit */
  DmaHandle.Init.MemDataAlignment = DMA_PDATAALIGN_HALFWORD;      /* memory data alignment : 16bit     */
  DmaHandle.Init.Mode = DMA_NORMAL;                               /* Normal DMA mode                  */
  DmaHandle.Init.Priority = DMA_PRIORITY_HIGH;                    /* priority level : high            */
  DmaHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;                  /* FIFO mode enabled                */
  DmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL; /* FIFO threshold: 1/4 full   */
  DmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;                    /* Memory burst                     */
  DmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;                 /* Peripheral burst                 */

  /*##-3- Select the DMA instance to be used for the transfer : DMA2_Stream0 #*/
  DmaHandle.Instance = DMA_STREAM;

  /*##-4- Initialize the DMA stream ##########################################*/
  if (HAL_DMA_Init(&DmaHandle) != HAL_OK)
  {
    while (1)
      ;
  }

  /*##-5- Select Callbacks functions called after Transfer complete and Transfer error */
  HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_CPLT_CB_ID, DMA_TransferComplete);
  HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_ERROR_CB_ID, DMA_TransferError);

  /*##-6- Configure NVIC for DMA transfer complete/error interrupts ##########*/
  HAL_NVIC_SetPriority(DMA_STREAM_IRQ, 0, 0);
  HAL_NVIC_EnableIRQ(DMA_STREAM_IRQ);
}

/**
  * @brief  DMA conversion complete callback
  * @note   This function is executed when the transfer complete interrupt
  *         is generated
  * @retval None
  */
static void DMA_TransferComplete(DMA_HandleTypeDef *han)
{
  y_fill_act++;

  if (y_fill_act > y2_fill)
  {
    lv_disp_flush_ready(lvDisplay);
  }
  else
  {
    buf_to_flush += x2_flush - x1_flush + 1;
    /*##-7- Start the DMA transfer using the interrupt mode ####################*/
    /* Configure the source, destination and buffer size DMA fields and Start DMA Stream transfer */
    /* Enable All the DMA interrupts */
    if (HAL_DMA_Start_IT(han, (uint32_t)buf_to_flush, (uint32_t)&my_fb[y_fill_act * TFT_HOR_RES + x1_flush],
                         (x2_flush - x1_flush + 1)) != HAL_OK)
    {
      while (1)
        ; /*Halt on error*/
    }
  }
}

/**
  * @brief  DMA conversion error callback
  * @note   This function is executed when the transfer error interrupt
  *         is generated during DMA transfer
  * @retval None
  */
static void DMA_TransferError(DMA_HandleTypeDef *han)
{
}

/**
  * @brief  This function handles DMA Stream interrupt request.
  * @param  None
  * @retval None
  */
void DMA_STREAM_IRQHANDLER(void)
{
  /* Check the interrupt and clear flag */
  HAL_DMA_IRQHandler(&DmaHandle);
}