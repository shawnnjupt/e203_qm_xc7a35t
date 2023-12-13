-makelib xcelium_lib/xpm -sv \
  "D:/vivado_22_2/Vivado/2022.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
-endlib
-makelib xcelium_lib/xpm \
  "D:/vivado_22_2/Vivado/2022.2/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../test_e203.gen/sources_1/ip/mmcm/mmcm_clk_wiz.v" \
  "../../../../test_e203.gen/sources_1/ip/mmcm/mmcm.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  glbl.v
-endlib

