cd ../../ && source ./get_submodule.sh && \
source ./set_env_var.sh && cd $EXERCISES_PATH/led_toggle_original_driver/ && \
source ./set_env_var.sh && cd Debug && make clean && make && \
st-flash write 0_led_toggle_addr.bin 0x08000000 && cd ..