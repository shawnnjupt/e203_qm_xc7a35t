set gitee_path=D:\code\fpga\gitee\e203_qm_xc7a35t
copy %gitee_path%\e203_nuclei_studio\Debug\test_e203hbridv2.bin   %gitee_path%\e203_tools\riscv_toolschain\e203_hbirdv2_bin\
cd %gitee_path%\e203_tools\riscv_toolschain\tools\openocd\
openocd.exe -f openocd_hbirdv2.cfg
