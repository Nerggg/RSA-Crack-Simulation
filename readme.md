# RSA Brute Force Simulation

A simple RSA brute force simulation made with `C` in the purpose of fulfilling the **IF2120 Matematika Diskrit** paper assignment.

## How to Use

1. Clone the repository and navigate to the repository folder
```
git clone https://github.com/Nerggg/RSA-Crack-Simulation
cd RSA-Crack-Simulation
```
2. Compile both `primeToTxt.c` and `crackRSA.c` with the following command
```
gcc primeToTxt.c dinList.c -o <executeable_name> -lm
```
```
gcc crackRSA.c dinList.c -o <executeable_name>
```
3. Run the compiled `primeToTxt.c` and enter the maximum bit size of the number
4. Run the compiled `crackRSA.c` and wait for the result

## Improvement for the Future

Pull requests are open to optimize the `primeToTxt.c` because currently it is still have the time complexity of O(2<sup>n</sup>) to generate all the prime numbers.

## Demo
https://github.com/Nerggg/RSA-Crack-Simulation/assets/118040364/d4830584-c2cb-45b8-91fd-3ac3d8388948
