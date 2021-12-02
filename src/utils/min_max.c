double getMin(double x, double y){
    if (x < y){
        return x;
    }else if (y < x){
        return y;
    }else{
        return x;
    }
}


double getMax(double x, double y){
    if (x > y){
        return x;
    }else if (x < y){
        return y;
    }else{
        return x;
    }
}
