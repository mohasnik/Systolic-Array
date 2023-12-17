# RT-Level Modeling of Google TPU Systolic Arrays using SystemC

In today's world, with the significant advancements in AI and Machine Learning applications, there is an increasing demand for faster and more complex computations. This demand has spurred the development of new hardware accelerators to cater to the needs of ML scientists.

Matrix multiplication is undeniably one of the most frequently employed calculations in Machine Learning, particularly in Neural Networks. Systolic Arrays offer a solution for accelerating matrix-matrix multiplication, and they are utilized in Google TPU Accelerators. In the following section, the RTL implementation of a 3*3 systolic array is described.

## Systolic Array nodes : Processing Elements (PE)

The Datapath of PE contains three registers, and a hardware capable of computing MAC operation. The constant matrix is received from Win bus. The result of the above calculation is received from Sin bus.
WReg is responsible for storing weights, while Dreg is used to get the matrix values and perform the MAC operation. By employing these simple PEs, it becomes feasible to compute matrix-matrix multiplications rapidly.

<br/>

<p align="center">
  <img src="https://github.com/mohasnik/Systolic-Array/assets/82777963/b5bab130-8773-4681-8d3a-60bcca43d261" alt="PE datapath" width="500"/>
  <br/>
  Figure 1.1 - The datapath Structure of Processing Element.
</p>
<br/>
<br/>


For this PE to perform the proper operation, a control unit is needed to manage calculations and weight loading:
<br/>
<br/>

<p align="center">
  <img src="https://github.com/mohasnik/Systolic-Array/assets/82777963/6705713a-289f-4c95-a65c-22d5764023f8" alt="PE control unit" width="500"/>
  <br/>
  Figure 1.2 - The Controller Diagram of Processing Element.
</p>


## Systolic Array Structure

By cascading multiple PEs, Systolic Arrays can be created. Note to the connections, as values in D move horizentally, but the values of S (result of MAC operation) move vertically in each 2 cycles.
<br/>
<br/>

<p align="center">
  <img src="https://github.com/mohasnik/Systolic-Array/assets/82777963/bfa978bc-a37e-49dd-81ea-070bb75d23e0" alt="Systolic array datapath" width="500"/>
  <br/>
  Figure 2.1 - The Datapath structure of Systolic Array.
</p>

<br/>
<br/>
<br/>

The Systolic Array also requires a control unit to execute the proper actions, given that the Processing Elements (PEs) are multicycle units, and the entire process necessitates multiple nodes to carry out the multiplication. The controller is also responsible for weight loading:
<br/>
<br/>

<p align="center">
  <img src="https://github.com/mohasnik/Systolic-Array/assets/82777963/88bccc06-1808-458a-91a5-d0446d6d8139" alt="Systolic array controller" width="500"/>
  <br/>
  Figure 2.2 - The Controller structure of Systolic Array.
</p>




## Refrences
- Understanding Matrix Multiplication on a Weight-Stationary Systolic Architecture : <a href="https://www.telesens.co/2018/07/30/systolic-architectures/">https://www.telesens.co/2018/07/30/systolic-architectures/ </a>


