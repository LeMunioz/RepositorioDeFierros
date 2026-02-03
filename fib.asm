; Serie de Fibonacci – HC12
; Guarda 10 valores en memoria

        ORG   $2000

FIB:    RMB   10          ; espacio para 10 números

        ORG   $1000

START:
        LDAA  #0
        STAA  FIB         ; fib[0] = 0

        LDAA  #1
        STAA  FIB+1       ; fib[1] = 1

        LDAB  #2          ; i = 2

LOOP:
        LDAA  FIB-1,B     ; fib[i-1]
        ADDA  FIB-2,B     ; fib[i-2]
        STAA  FIB,B       ; fib[i]

        INCB
        CMPB  #10
        BLO   LOOP

END:    BRA   END
