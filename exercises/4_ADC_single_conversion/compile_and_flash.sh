cd ../../ && source ./get_submodule.sh && \
source ./set_env_var.sh && cd $EXERCISES_PATH/4_ADC_single_conversion/ && \
source ./set_env_var.sh && cd Debug && make clean && make && \
# st-flash write exercise.bin 0x08000000 && \
cd $THIS_EXERCISE; ec=$?  # grab the exit code into a variable so that it can
                          # be reused later, without the fear of being overwritten
                          # stolen from: <https://stackoverflow.com/a/56941605>
case $ec in
    0) ;;
    1) printf '%s\n' "Command exited with non-zero"; exit 1;;
    *) cd $THIS_EXERCISE;;
esac
