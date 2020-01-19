# HeatDiffusion
Maps 1D and 2D heat diffusion across a wire or a plate.

## Motivation
Apply knowledge of arrays to gain an understanding of a heat transfer model over one and two dimensional objects. 
An explicit method of solving finite difference approximations was used to determine heat transfer for new time instances.

### Background
The one dimensional heat equation is given by
![equation](https://latex.codecogs.com/gif.latex?k%5Cfrac%7B%5Cdelta%5E2u%7D%7B%5Cdelta%20x%5E2%7D%20%3D%20c%5Crho%5Cfrac%7B%5Cdelta%20u%7D%7B%5Cdelta%20t%7D).
Likewise, the two dimensional heat equation is given by
![equation](https://latex.codecogs.com/gif.latex?k%5Cbigg%28%5Cfrac%7B%5Cdelta%5E2u%7D%7B%5Cdelta%20x%5E2%7D%20&plus;%20%5Cfrac%7B%5Cdelta%5E2u%7D%7B%5Cdelta%20y%5E2%7D%5Cbigg%29%20%3D%20c%5Crho%5Cfrac%7B%5Cdelta%20u%7D%7B%5Cdelta%20t%7D).
To solve these equations exactly would require solving differential equations by hand.
Therefore, the values for heat diffusion are approximated using the following functions:

1D: 
![equation](https://latex.codecogs.com/gif.latex?k%5Cfrac%7Bu%5Et_%7Bx%20&plus;%201%7D%20-%202u%5Et_x%20&plus;%20u%5Et_%7Bx%20-%201%7D%7D%7B%5CDelta%20x%5E2%7D%20%3D%20c%5Crho%5Cfrac%7Bu_x%5E%7Bt%20&plus;%20%5CDelta%20t%7D%20-%20u%5Et_x%7D%7B%5CDelta%20t%7D)

2D:
![equation](https://latex.codecogs.com/gif.latex?k%5Cbigg%28%5Cfrac%7Bu%5Et_%7Bi%20&plus;%201%2Cj%7D%20-%202u%5Et_%7Bi%2Cj%7D%20&plus;%20u%5Et_%7Bi%20-%201%2Cj%7D%7D%7B%5CDelta%20x%5E2%7D%20&plus;%20%5Cfrac%7Bu%5Et_%7Bi%2Cj%20&plus;%201%7D%20-%202u%5Et_%7Bi%2Cj%7D%20&plus;%20u%5Et_%7Bi%2C%20j-1%7D%7D%7B%5CDelta%20y%5E2%7D%5Cbigg%29%3D%20c%5Crho%5Cfrac%7Bu_%7Bi%2Cj%7D%5E%7Bt%20&plus;%20%5CDelta%20t%7D%20-%20u%5Et_%7Bi%2Cj%7D%7D%7B%5CDelta%20t%7D)

Note that **Δ** represents the change in a variable, **k** is thermal conductivity, **ρ** (rho) is material density, 
**c** is the specific heat capacity of material, **u** is the object, and **x** is the location on u.

## Class
CS 161: Introduction to Computer Scienc
