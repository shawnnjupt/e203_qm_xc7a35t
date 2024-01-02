#### 采用IDE 

![image-20231228195117840](READMEmarkdown-img/README.assets/image-20231228195117840.png)

#### 工程设置里面添加

![image-20231228195208675](READMEmarkdown-img/README.assets/image-20231228195208675.png)



```c
riscv-nuclei-elf-objcopy -O binary test_e203hbridv2.elf   test_e203hbridv2.bin;riscv-nuclei-elf-objcopy -O verilog "${BuildArtifactFileBaseName}.elf" "${BuildArtifactFileBaseName}.verilog";sed -i 's/@800/@000/g' "${BuildArtifactFileBaseName}.verilog"; sed -i 's/@00002FB8/@00002000/g' "${BuildArtifactFileBaseName}.verilog";riscv-nuclei-elf-objdump -d  "${BuildArtifactFileBaseName}.elf" > "${BuildArtifactFileBaseName}.dasm";
```

