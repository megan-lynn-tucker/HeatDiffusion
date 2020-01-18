/*********************************************************************
 ** Program filename: heat 
 ** Author: Megan Lynn Tucker
 ** Date: 03/17/2019
 ** Description: calculates the heat diffusion across a wire (1d) or a plate (2d);
 	uses finite difference method; 
	prints the current temperature distribution
 ** Input: floats: k, rho, c, wire length, time of simulation, initial temp, right/left/top/bottom temp
	ints: sections, time interval
 ** Output: 1d: row of floats representing different temperatures
 	2d: matrix of floats representing different temperatures
 *********************************************************************/ 
#include<iostream>
#include<string>
#include<stdlib.h>

using namespace std;


bool verify_integers(string, bool);
bool verify_enters(string, bool);
int check_integers();
int check_1_or_2();
bool verify_floats(string, bool);
float check_floats();
float calculate_delta(float, int);

float calculate_1d_stability(float, float, float, float);
float* create_1d_array(int, float, float, float);
void print_1d_array(float*, int);
void copy_1d_array(float*, float*, int);
void calculate_1d_u(int, int, float, float, float, float);
void one_dimension();

float calculate_2d_stability(float, float, float, float, float);
float** create_2d_array(int, float, float, float);
void print_2d_array(float**, int);
void copy_2d_array(float**, float**, int);
void delete_2d_array(float**, int);
void calculate_2d_u(int, int, float, float, float, float, float, float, float);
void two_dimensions();


int main(){}
   int again; 

   do{
      again = 0;

      int dimension;
      cout << "1D or 2D: ";
      dimension = check_1_or_2();

      if(dimension == 1){
	      one_dimension();
      }

      if(dimension == 2){
	      two_dimensions();
      }

      cout << "Enter 1 to calculate another temperature: ";
      again = check_integers();
   }while(again == 1);

   return 0;
}


/*********************************************************************
 ** Function: verify_integers
 ** Description: verifies the input only contains values 1 through 9
 ** Parameters: string, bool
 ** Returns: bool
 ** Pre-Conditions: input is a string 
 ** Post-Conditions: input was a string consisting only of the numbers 1 through 9
 *********************************************************************/ 
bool verify_integers (string s, bool error){
   for(int i = 0; i < s.size(); i++){
      if(!(s.at(i) >= '0' && s.at(i) <= '9')){
	      error = true;
      }
   }
   return error;
}

/*********************************************************************
 ** Function: verify_enters
 ** Description: verifies enter/return is an invalid value
 ** Parameters: string, bool
 ** Returns: bool
 ** Pre-Conditions: the input is a string
 ** Post-Conditions: the input is a string that did not just consist of enters
 *********************************************************************/ 
bool verify_enters(string s, bool error){
   if(s.length() == 0){
      error = true;
   } 
   return error;
}

/*********************************************************************
 ** Function: check_integers
 ** Description: converts string to integer
 ** Parameters: none
 ** Returns: int
 ** Pre-Conditions: the input is a string
 ** Post-Conditions: the input is a string of integers numbered 1 to 9
 *********************************************************************/ 
int check_integers(){
   string s;
   bool error; 

   do{ 
      getline(cin,s);

      // relies on short circuting to determine if the do while runs again
      // if any of the functions returns true or will short curcut
      // error will remain true until the end of the do while
      error = false;
      error = error || verify_integers(s, error);
      error = error || verify_enters(s, error);

      if (error == true){
	      cout << "That is not a valid input. Try again." << endl;
      }
   } while (error == true);

   int n = atoi(s.c_str());
   return n;
}

/*********************************************************************
 ** Function: check_1_or_2
 ** Description: verifies the input was either 1 or 2
 ** Parameters: none
 ** Returns: int
 ** Pre-Conditions: the input is a string that is verified by the function check integers
 ** Post-Conditions: the integer is either 1 or 2
 *********************************************************************/ 
int check_1_or_2(){
   bool error; 
   int number;

   do{
      error = false;
      number = check_integers();

      if(number < 1 || number > 2){
	      cout << "That is not a valid input. Try again." << endl;
	      error = true;
      }
   } while (error == true);

   return number;
}

/*********************************************************************
 ** Function: verify_floats
 ** Description: verifies there is only one '.' in a string
 ** Parameters: string, bool
 ** Returns: bool
 ** Pre-Conditions: the input is a string
 ** Post-Conditions: the string consists of the numbers 1 to 9 and at most one .
 *********************************************************************/ 
bool verify_floats (string s, bool error){
   int number_of_decimals = 0;

   for(int i = 0; i < s.size(); i++){
      if((s.at(i) < '0' || s.at(i) > '9') && s.at(i) != '.'){
	      return true;
      }
      if(s.at(i) == '.'){
	      number_of_decimals++;
      }
      if(!(number_of_decimals == 1 || number_of_decimals == 0)){
	      return true;
      }
   }
   return false;
}

/*********************************************************************
 ** Function: check_floats
 ** Description: verifies the inputs are floats
 ** Parameters: none
 ** Returns: float
 ** Pre-Conditions: the input is a string 
 ** Post-Conditions: the string consists of numbers 1 to 9 and at most one .
 *********************************************************************/ 
float check_floats(){
   string s;
   bool error; 

   do   {
      getline(cin,s);

      error = false;
      error = error || verify_floats(s, error);
      error = error || verify_enters(s, error);

      if (error == true)      {
	      cout << "That is not a valid input. Try again." << endl;
      }
   } while (error == true);

   float f = atof(s.c_str());
   return f;
}

/*********************************************************************
 ** Function: calculate_delta
 ** Description: calculates the change, i.e. delta
 ** Parameters: float length, int segments
 ** Returns: float delta
 ** Pre-Conditions: the inputs are one float and one int
 ** Post-Conditions: the delta is the length divided by the number of segments
 *********************************************************************/ 
float calculate_delta(float length, int segments){
   float delta;
   delta = length / segments;
   return delta;

   cout << "delta" << delta << endl;
}

/*********************************************************************
 ** Function: calculate_1d_stability
 ** Description: calculates the stability for one dimension
 ** Parameters: float k, float delta_t, float delta_x, float c, float rho
 ** Returns: float stability
 ** Pre-Conditions: valid inputs for parameters
 ** Post-Conditions: none
 *********************************************************************/ 
float calculate_1d_stability(float k, float delta_t, float delta_x, float c, float rho){
   float numerator;
   float denominator;
   float stability;

   stability = (k * delta_t) / (delta_x * delta_x * c * rho);

   return stability;
}

/*********************************************************************
 ** Function: create_1d_array
 ** Description: creates a 1d array with a number of elements equal to segments
 ** Parameters: int segments, float initial_temp, float left_temp, float right_temp
 ** Returns: float *wire
 ** Pre-Conditions: the inputs yield a valid stability
 ** Post-Conditions: space is allocated to fit an array of size segments
 *********************************************************************/ 
float* create_1d_array(int segments, float initial_temp, float left_temp, float right_temp){
   float *wire = new float[segments];
  
   for(int i = 0; i < segments; i++){
      if(i == 0){
	      wire[i] = left_temp;
      }
      else if(i == segments - 1){
	      wire[i] = right_temp;
      }
      else {
	      wire[i] = initial_temp;
      }
   }
   return wire;
}

/*********************************************************************
 ** Function: print_1d_array
 ** Description: prints the values of a one dimensional array
 ** Parameters: float *array, int rows
 ** Retruns: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/ 
void print_1d_array(float *array, int rows){
   for(int i = 0; i < rows; i++){
      cout << array[i] << " ";
   }
   cout << endl;
}

/*********************************************************************
 ** Function: copy_1d_array
 ** Description: copys the values of one array onto another
 ** Parameters: float *newarray, float *oldarray, int rows
 ** Retruns: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/ 
void copy_1d_array(float *newarray, float *oldarray, int rows){
   for(int i = 0; i < rows; i++)   {
      oldarray[i] = newarray[i]; 
   }
}

/*********************************************************************
 ** Function: calculate_1d_u
 ** Description: calculates the temperature of the wire for each time interval
 ** Parameters: int wire_segments, float initial_temp, float left_temp, int time_segments, float stability
 ** Returns: none
 ** Pre-Conditions: stability is valid
 ** Post-Conditions: none
 *********************************************************************/ 
void calculate_1d_u(int wire_segments, float initial_temp, float left_temp, float right_temp, int time_segments, float stability){
   float *newwire, *oldwire, A, B, C, D;
   // calculate the new values from the old value
   newwire = create_1d_array(wire_segments, initial_temp, left_temp, right_temp);
   oldwire = create_1d_array(wire_segments, initial_temp, left_temp, right_temp); 
   
   print_1d_array(oldwire, wire_segments);
   
   for(int i = 1; i < time_segments; i++){ // calculate the temperature for each time segment  
      for(int j = 1; j < wire_segments - 1; j++){
         // use floats here instead of newwire[j] to ensure no errors
         A = oldwire[j + 1];
         B = oldwire[j];
         C = oldwire[j - 1];
         D = (stability * (A - (2 * B) + C)) + B; // formula for the next temperature
         newwire[j] = D;
      }      
      print_1d_array(newwire, wire_segments);
      copy_1d_array(newwire, oldwire, wire_segments);
   }
   delete [] newwire;
   delete [] oldwire;
}

/*********************************************************************
 ** Function: one_dimension()
 ** Description: requests values for all inputs
 ** Parameters: none
 ** Retruns: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/ 
void one_dimension(){
   float rho, k, c, wire_length, time_length, initial_temp, left_temp, right_temp, delta_x, delta_t, stability;
   int wire_segments, time_segments;

   do{
      cout << "k: ";
      k = check_floats();
     
      cout << "rho: ";
      rho = check_floats();

      cout << "c: ";
      c = check_floats();

      cout << "wire length: ";
      wire_length = check_floats();

      cout << "wire segments: ";
      wire_segments = check_integers();

      cout << "time intervals: ";
      time_segments = check_integers();

      cout << "time of simulation: ";
      time_length = check_floats();

      cout << "right temperature: ";
      right_temp = check_floats();

      cout << "left temperature: ";
      left_temp = check_floats();

      cout << "initial temperature: ";
      initial_temp = check_floats();

      delta_x = calculate_delta(wire_length, wire_segments);
      delta_t = calculate_delta(time_length, time_segments);
      stability = calculate_1d_stability(k, delta_t, delta_x, c, rho);

      if(stability >= 0.5){
	      cout << "Unstable solution. Input new values:" << endl;
      }
   }while(stability >= 0.5);

   calculate_1d_u(wire_segments, initial_temp, left_temp, right_temp, time_segments, stability);   
}

/*********************************************************************
 ** Function: calculate_2d_stability
 ** Description: calculate the stability for the heat equatoin in second dimension 
 ** Parameters: float k, float delta_xy, float c, float rho
 ** Returns: float stability
 ** Pre-Conditions: the inputs are valid
 ** Post-Conditions: none
 *********************************************************************/ 
float calculate_2d_stability(float k, float delta_xy, float c, float rho){
   float stability;
   stability = (delta_xy * delta_xy * rho * c) / (4 * k);
   return stability;
}

/*********************************************************************
 ** Function: create_2d_array
 ** Description: creates a two dimensional nxn matrix of size segments
 ** Parameters: int segments, float initial_temp, float lr_temp, float tb_temp
 ** Returns: float **plate
 ** Pre-Conditions: the inputs yield a valid stability
 ** Post-Conditions: space is allocated to fit an array of size segments
 *********************************************************************/ 
float** create_2d_array(int segments, float initial_temp, float lr_temp, float tb_temp){
   // number of rows = number of columns = segments
   float **plate = new float* [segments]; // first create heap memory for row pointers
  
   for(int i = 0; i < segments; i++){
      plate[i] = new float[segments]; // for each row create memory for columns
      for(int j = 0; j < segments; j++){
         if(i == 0 || i == segments - 1){
	         plate[i][j] = lr_temp;
	      }
         // because the corner values don't matter, they will default to the top and bottom values of temperature	 
         else if(j == 0 || j == segments - 1){
            plate[i][j] = tb_temp;
         }
         else{
            plate[i][j] = initial_temp;
         }
      }
   }
   return plate;
}

/*********************************************************************
 ** Function: print_2d_array
 ** Description: prints a two dimensional array
 ** Parameters: float **array, int rows
 ** Retruns: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/ 
void print_2d_array(float **array, int rows){
   for(int i = 0; i < rows; i++){
      for(int j = 0; j < rows; j++){
	      cout << array[i][j] << " ";
      }
      cout << endl;
   }
   cout << endl;
}

/*********************************************************************
 ** Function: print_1d_array
 ** Description: print a two dimensional array of size rows x rows
 ** Parameters: float **newarray, float *oldarray, int rows
 ** Retruns: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/ 
void copy_2d_array(float **newarray, float **oldarray, int rows){
   for(int i = 0; i < rows; i++){
      for(int j = 0; j < rows; j++){
	      oldarray[i][j] = newarray[i][j]; 
      }
   }
}

/*********************************************************************
 ** Function: calculate_2d_u
 ** Description: delete the pointers allocated for the array
 ** Parameters: float **array, int rows
 ** Returns: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/ 
void delete_2d_array(float **array, int rows){
   // for each pointer, delete the array where the pointer is going to
   for(int i = 0; i < rows; i++){
      delete [] array[i];
   }
   delete [] array; // delete the array that the double pointer is pointing to
}

/*********************************************************************
 ** Function: calculate_2d_u
 ** Description: calculates the temperature of the plate for each time segment
 ** Parameters: int plate segments, int time_segments, float initial_temp, float lr_temp, float tb_temp, float delta_xy, float delta_t,
 	float k, float c, float rho
 ** Returns: none
 ** Pre-Conditions: stability is valid
 ** Post-Conditions: none
 *********************************************************************/ 
void calculate_2d_u(int plate_segments, int time_segments, float initial_temp, float lr_temp, float tb_temp, float delta_xy, float delta_t, float k, float c, float rho){
   float **newplate, **oldplate, A, B, C, D, E, F, G, H;
   newplate = create_2d_array(plate_segments, initial_temp, lr_temp, tb_temp);
   oldplate = create_2d_array(plate_segments, initial_temp, lr_temp, tb_temp);
   
   print_2d_array(oldplate, plate_segments);
   
   for(int i = 1; i < time_segments; i++){  
      for(int j = 1; j < plate_segments - 1; j++){
	      for(int k = 1; k < plate_segments - 1; k+){
            A = oldplate[j + 1][k];
            B = oldplate[j - 1][k];
            C = oldplate[j][k + 1];
            D = oldplate[j][k - 1];
            E = oldplate[j][k];
            
            // full equation written out to avoid errors  
            F = (((k * delta_t) / (c * rho)) * (((A - (2 * E) + B) / (delta_xy * delta_xy)) + ((C - (2 * E) + D) / (delta_xy * delta_xy)))) + E;

            newplate[j][k] = F;
	         }
         }      
      print_2d_array(newplate, plate_segments);
      copy_2d_array(newplate, oldplate, plate_segments);
   }
   delete_2d_array(newplate, plate_segments);
   delete_2d_array(oldplate, plate_segments);
}

/*********************************************************************
 ** Function: two_dimensions
 ** Description: requests input for plate
 ** Parameters: none
 ** Retruns: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/ 
void two_dimensions(){
   float k, rho, c, plate_size, time_length, initial_temp, lr_temp, tb_temp, delta_xy, delta_t, stability, a;
   int plate_segments, time_segments;

   do{
      cout << "k: ";
      k = check_floats();
     
      cout << "rho: ";
      rho = check_floats();

      cout << "c: ";
      c = check_floats();

      cout << "plate height and width: ";
      plate_size = check_floats();

      cout << "sections across height and width: ";
      plate_segments = check_integers();

      cout << "time intervals: ";
      time_segments = check_integers();

      cout << "time of simulation: ";
      time_length = check_floats();

      cout << "left and right column temperature: ";
      lr_temp = check_floats();

      cout << "top and bottom row temperature: ";
      tb_temp = check_floats();

      cout << "initial temperature: ";
      initial_temp = check_floats();

      delta_xy = calculate_delta(plate_size, plate_segments); // because we are using a square matrix, delta x and delta y are the same
      delta_t = calculate_delta(time_length, time_segments);

      stability = calculate_2d_stability(k, delta_xy, c, rho);

      if(stability > delta_t){
	      cout << "Unstable solution. Input new values:" << endl;
      }
   }while(stability > delta_t);
   calculate_2d_u(plate_segments, time_segments, initial_temp, lr_temp, tb_temp, delta_xy, delta_t, k, c, rho);
}
