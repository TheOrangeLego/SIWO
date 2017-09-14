onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -divider {Top View}
add wave -noupdate -radix hexadecimal /SIWO_tb/_CLK
add wave -noupdate -radix hexadecimal /SIWO_tb/_start
add wave -noupdate -radix hexadecimal /SIWO_tb/halt
add wave -noupdate -divider {Instruction Fetch}
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/instructionFetch_module/_CLK
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/instructionFetch_module/_branchJump
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/instructionFetch_module/_destBranchJump
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/instructionFetch_module/_halt
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/instructionFetch_module/_relative
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/instructionFetch_module/_reset
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/instructionFetch_module/_run
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/instructionFetch_module/instruction
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/instructionFetch_module/instructionROM
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/instructionFetch_module/programCounter
add wave -noupdate -divider {Control Unit}
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/_instruction
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/branch
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/compare
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/destBranchJump
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/funcCode
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/halt
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/immediateValue
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/jump
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/memoryRead
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/memoryWrite
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/muxMA
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/muxRI
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/overflow
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/regA
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/regB
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/regWrite
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/controlUnit_module/relative
add wave -noupdate -divider {Register File}
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/registerFile_module/_CLK
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/registerFile_module/_regDest
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/registerFile_module/_regSrcA
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/registerFile_module/_regSrcB
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/registerFile_module/_regWrite
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/registerFile_module/_writeVal
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/registerFile_module/registers
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/registerFile_module/valueA
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/registerFile_module/valueB
add wave -noupdate -divider ALU
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/arithmeticLogicUnit_module/_funcCode
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/arithmeticLogicUnit_module/_valA
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/arithmeticLogicUnit_module/_valB
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/arithmeticLogicUnit_module/compareBit
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/arithmeticLogicUnit_module/overflow
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/arithmeticLogicUnit_module/result
add wave -noupdate -divider {Data Memory}
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/dataMemory_module/_CLK
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/dataMemory_module/_address
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/dataMemory_module/_read
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/dataMemory_module/_valueIn
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/dataMemory_module/_write
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/dataMemory_module/data
add wave -noupdate -radix hexadecimal /SIWO_tb/uut/dataMemory_module/valueOut
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ps} 0}
quietly wave cursor active 0
configure wave -namecolwidth 316
configure wave -valuecolwidth 78
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ps
update
WaveRestoreZoom {0 ps} {7966 ps}
