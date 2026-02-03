# Serie de Fibonacci
# Guarda los primeros 10 valores en una lista

fib = [0] * 10

fib[0] = 0
fib[1] = 1

i = 2

while i < 10:
    fib[i] = fib[i-1] + fib[i-2]
    i += 1

print(fib)
