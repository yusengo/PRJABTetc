################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
CMD/28335_RAM_lnk.exe: ../CMD/28335_RAM_lnk.cmd $(GEN_CMDS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Linker'
	"D:/TICCS/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --large_memory_model --float_support=fpu32 -z -m"../CMD/Debug/lab-FFT.map" --stack_size=1000 --heap_size=1000 --warn_sections -i"D:/TICCS/ccsv6/tools/compiler/c2000_6.2.5/lib" -i"D:/TICCS/ccsv6/tools/compiler/c2000_6.2.5/include" -i"F:/DSPprj/lab47-FFT" --reread_libs --xml_link_info="lab-FFT_linkInfo.xml" --rom_model -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMD/DSP2833x_Headers_nonBIOS.exe: ../CMD/DSP2833x_Headers_nonBIOS.cmd $(GEN_CMDS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Linker'
	"D:/TICCS/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --large_memory_model --float_support=fpu32 -z -m"../CMD/Debug/lab-FFT.map" --stack_size=1000 --heap_size=1000 --warn_sections -i"D:/TICCS/ccsv6/tools/compiler/c2000_6.2.5/lib" -i"D:/TICCS/ccsv6/tools/compiler/c2000_6.2.5/include" -i"F:/DSPprj/lab47-FFT" --reread_libs --xml_link_info="lab-FFT_linkInfo.xml" --rom_model -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


