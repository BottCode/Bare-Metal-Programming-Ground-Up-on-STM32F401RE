HAL_STM32_TAG="v1.26.2"

git submodule add git@github.com:STMicroelectronics/STM32CubeF4.git && \
cd STM32CubeF4/ && \
git checkout $HAL_STM32_TAG && \
cd .. && \
echo "##### STM32CubeF4/ version is" $HAL_STM32_TAG " #####"