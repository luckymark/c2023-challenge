//
// Created by 14212 on 2023/9/27.
//
#include "push_boxes.h"
double score(double all_time,int step_number,int dif){
    double s_time=0,s_step=0;
    if(dif==2)
    {
        s_time=(1-all_time/1200)*100.0;
        s_step=(1-step_number/7500.0)*100.0;
        return s_time*0.2+s_step*0.8;
    }
    else
    {
        s_time=(1-all_time/300.0)*100.0;
        s_step=(1-step_number/400.0)*100.0;
        return s_time*0.2+s_step*0.8;
    }
}
