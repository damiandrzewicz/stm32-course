#include <stdint.h>

static constexpr int RCC_BASE_ADDR = 0x40023800UL;
static constexpr int RCC_AHB1ENR_REG_OFFSET = 0x30UL;
static constexpr int RCC_AHB1ENR_ADDR = RCC_BASE_ADDR + RCC_AHB1ENR_REG_OFFSET;
static constexpr int RCC_CFGR_REG_OFFSET = 0x08UL;
static constexpr int RCC_CFGR_ADDR = RCC_BASE_ADDR + RCC_CFGR_REG_OFFSET;

static constexpr int GPIOA_BASE_ADDR = 0x40020000UL;
static constexpr int GPIOA_MODER_REG_OFFSET = 0x00UL;
static constexpr int GPIOA_MODER_ADDR = GPIOA_BASE_ADDR + GPIOA_MODER_REG_OFFSET;
static constexpr int GPIOA_AFHR_REG_OFFSET = 0x24UL;
static constexpr int GPIOA_AFHR_ADDR = GPIOA_BASE_ADDR + GPIOA_AFHR_REG_OFFSET;

int main()
{
    // 1. Configure RCC_CFGR register bits MCO1 to select HSI as clock source:
    auto pRccCfgrReg = reinterpret_cast<uint32_t*>(RCC_CFGR_ADDR);
    *pRccCfgrReg &= ~((1 << 21) | (1 << 22));  // Clear bits 21 & 22 (MCO1 as HSI clock source)

    // 2. Configure PA8 to AF0 mode to behave as MCO1 signal:
    // 2.1 Enable GPIOA clock source
    auto pRccAhn1enrReg = reinterpret_cast<uint32_t*>(RCC_AHB1ENR_ADDR);
    *pRccAhn1enrReg |= (1 << 0);    // Enable GPIOA peripheral

    // 2.2 Configure GPIOA pin 8 as alternate function mode
    auto pGPIOAModeReg = reinterpret_cast<uint32_t*>(GPIOA_MODER_ADDR);
    *pGPIOAModeReg &= ~((1 << 16) | (1 << 17)); // Clear MODER8[1:0] bits
    *pGPIOAModeReg |= (1 << 17); // Set MODER8[1:0] bits to alternate function (10)

    // 2.3 Configure alternate function register to set mode 0 for PA8
    auto pGPIOAAltFunHighReg = reinterpret_cast<uint32_t*>(GPIOA_AFHR_ADDR);
    *pGPIOAAltFunHighReg &= ~(1 <<0 | 1 << 1 | 1 << 2 | 1 << 3);    // Set AFHR8[3:0] to 0000 (AF0)

    while(1){}
}