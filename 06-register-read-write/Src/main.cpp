#include <stdint.h>

static constexpr int RCC_BASE_ADDR = 0x40023800UL;
static constexpr int RCC_AHB1ENR_REG_OFFSET = 0x30UL;
static constexpr int RCC_AHB1ENR_ADDR = RCC_BASE_ADDR + RCC_AHB1ENR_REG_OFFSET;

int main()
{
    auto pRccAhn1enrReg = reinterpret_cast<uint32_t*>(RCC_AHB1ENR_ADDR);

    // Enable GPIOA peripheral
    *pRccAhn1enrReg |= (1 << 0);

    // Disable GPIOA peripheral
    *pRccAhn1enrReg &= ~(1 << 0);
    
    while(1){}
}