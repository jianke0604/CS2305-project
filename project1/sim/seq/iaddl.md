# description of the computations for iaddl

## fetch:

- icode:ifun $\leftarrow$ M1[PC]
- rA:rB       $\leftarrow$ M1[PC+1]
- valC         $\leftarrow$ M4[PC+2]
- valP         $\leftarrow$ PC+6

## decode:

- valB $\leftarrow$ R[rB]

## execute:

- valE $\leftarrow$ valC + valB
- Set CC

## memory:

- None

## writeback:

- R[rB] $\leftarrow$ valE

## pc-update:

- PC $\leftarrow$ valP