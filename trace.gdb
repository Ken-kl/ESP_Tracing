# GDB File for Tracing
set pagination off
set logging file instruction_trace.log
set logging enabled on
set print symbol off
set print address off
set startup-quietly on
set step-mode on
define start_trace
  # shell rm -f trace.bin

  while 1
    printf "PC: 0x%08x Instruction: 0x%08x\n", $pc, *(int*)$pc
    # append value trace.bin (unsigned long)$pc
    # append value trace.bin (unsigned int)*(int*)$pc
    stepi
  end
end

echo \nTrace script loaded. Type 'start_trace' to begin.\n