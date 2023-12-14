# RT-Level Modeling of Google TPU Systolic Arrays using SystemC

In today's world, with the significant advancements in AI and Machine Learning applications, there is an increasing demand for faster and more complex computations. This demand has spurred the development of new hardware accelerators to cater to the needs of ML scientists.

Matrix multiplication is undeniably one of the most frequently employed calculations in Machine Learning, particularly in Neural Networks. Systolic Arrays offer a solution for accelerating matrix-matrix multiplication, and they are utilized in Google TPU Accelerators. In the following section, the RTL implementation of a 3*3 systolic array is described.

## Systolic Array nodes : Processing Elements

The Datapath of PE contains three registers, and a hardware capable of computing MAC operation. The constant matrix is received from Win bus. The result of the above calculation is received from Sin bus.
WReg is responsible for storing weights, while Dreg is used to get the matrix values and perform the MAC operation.
