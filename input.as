mcr m1
prn #5
endmcr
MAIN: mov r3 ,LENGTH
m1
sub r1, r4
bne END
L1: inc K
END: stop
STR: .string “abcdef”
LENGTH: .data 6,9,15
K: .data 22