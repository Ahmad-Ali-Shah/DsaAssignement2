/*

brightness hold for all the points
so we shall change the pioints coordinatyes


Color as a Vector in a 3D Vector Space


every pixel is not just a point its a 3d colour 


The set of all possible displayable colors 
forms a bounded geometric 3D cube
 called the RGB Color Cube

 now the brightness adjusment is nothing but a 
 Affine Vector Translation along the Gray Diagonal Vector 


 so its like translation but for the 3x3 we shall take the rgb colours 
 and then apply translations 

*/

namespace MyBrightness{


    double clampValue(unsigned int orignalValue, double delta){

        double newVal = static_cast<double>(orignalValue) + delta;

        if(newVal > 255.0){
            newVal = 255.0;
        }
        else if(newVal < 0.0){
            newVal = 0.0;
        }

        return newVal;
    }

    void brightness(unsigned int &r , unsigned int &g  , unsigned int& b, double delta ){

        r = static_cast<unsigned int>(clampValue(r, delta));
        g = static_cast<unsigned int>(clampValue(g , delta));
        b = static_cast<unsigned int>(clampValue(b , delta));


        /////////////////////////////////////

        // i am treatijng each as coordinates and on the basis of that i shall update later on 


        //////////////////////////////////////

    }
}