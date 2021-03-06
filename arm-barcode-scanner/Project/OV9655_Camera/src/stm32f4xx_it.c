/**
 ******************************************************************************
 * @file    stm32fxxx_it.c
 * @author  MCD Application Team
 * @version V1.1.0
 * @date    19-March-2012
 * @brief   Main Interrupt Service Routines.
 *          This file provides all exceptions handler and peripherals interrupt
 *          service routine.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Portions COPYRIGHT 2012 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */
/**
 ******************************************************************************
 * <h2><center>&copy; Portions COPYRIGHT 2012 Embest Tech. Co., Ltd.</center></h2>
 * @file    stm32fxxx_it.c
 * @author  CMP Team
 * @version V1.0.0
 * @date    28-December-2012
 * @brief   Main Interrupt Service Routines.
 *          This file provides all exceptions handler and peripherals interrupt
 *          service routine.
 *          Modified to support the STM32F4DISCOVERY, STM32F4DIS-BB and
 *          STM32F4DIS-LCD modules.      
 ******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, Embest SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
 * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
 * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
 * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "usb_core.h"
#include "usbd_core.h"
//#include "usb_conf.h"
#include "usb_conf_com.h"
#include "stm32f4_discovery_sdio_sd.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//extern USB_OTG_CORE_HANDLE  USB_OTG_dev;
/* Private function prototypes -----------------------------------------------*/
//extern uint32_t USBD_OTG_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);
#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED 
//extern uint32_t USBD_OTG_EP1IN_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);
//extern uint32_t USBD_OTG_EP1OUT_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);
#endif

/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*             Cortex-M Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief   This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void) {
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void) {
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void) {
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void) {
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void) {
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void) {
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void) {
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void) {
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void) {
    TimingDelay_Decrement();
}

/**
 * @brief  This function handles OTG_HS Handler.
 * @param  None
 * @retval None
 */
#ifdef USE_USB_OTG_HS  
void OTG_HS_IRQHandler(void)
{
//  USBD_OTG_ISR_Handler (&USB_OTG_dev);
}
#endif

#ifdef USE_USB_OTG_FS  
void OTG_FS_IRQHandler(void)
{
//  USBD_OTG_ISR_Handler (&USB_OTG_dev);
}
#endif
#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED 
/**
 * @brief  This function handles EP1_IN Handler.
 * @param  None
 * @retval None
 */
void OTG_HS_EP1_IN_IRQHandler(void)
{
//  USBD_OTG_EP1IN_ISR_Handler (&USB_OTG_dev);
}

/**
 * @brief  This function handles EP1_OUT Handler.
 * @param  None
 * @retval None
 */
void OTG_HS_EP1_OUT_IRQHandler(void)
{
//  USBD_OTG_EP1OUT_ISR_Handler (&USB_OTG_dev);
}
#endif

/**
 * @brief  This function handles SDIO global interrupt request.
 * @param  None
 * @retval None
 */
void SDIO_IRQHandler(void) {
    /* Process All SDIO Interrupt Sources */
    SD_ProcessIRQSrc();
}

/**
 * @brief  This function handles DMA2 Stream3 or DMA2 Stream6 global interrupts
 *         requests.
 * @param  None
 * @retval None
 */
void SD_SDIO_DMA_IRQHANDLER(void) {
    /* Process DMA2 Stream3 or DMA2 Stream6 Interrupt Sources */
    SD_ProcessDMAIRQ();
}

/******************************************************************************/
/*                 STM32Fxxx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32fxxx.s).                                               */
/******************************************************************************/

/**
 * @brief  This function handles PPP interrupt request.
 * @param  None
 * @retval None
 */
/*void PPP_IRQHandler(void)
 {
 }*/

/********* Portions COPYRIGHT 2012 Embest Tech. Co., Ltd.*****END OF FILE******/
