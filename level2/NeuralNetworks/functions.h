//
// Created by 14212 on 2023/12/10.
//
#include "basical_parameter.h"
#ifndef C2023_CHALLENGE_FUNCTIONS_H
#define C2023_CHALLENGE_FUNCTIONS_H
void clear_images_data(FILE * fp);
void clear_label_data(FILE * fp);
void transform(FILE *,double * input);
void creat_random_value(FILE *,int start,int end);
void get_i_h_value(FILE *,double (* w)[HIDDEN_NUMBER]);
void get_h_o_value(FILE *,double (* w)[OUTPUT_NUMBER]);
void calculate_hidden_layer(double * input_data,double * hidden_data,double (* w_in_hid)[HIDDEN_NUMBER]);
void calculate_output_layer(double * hidden_data,double * output_data,double (* w_hid_out)[OUTPUT_NUMBER]);
double sigmoid(double x);
void calculate_output_error(double * output_data,double * e_output,double (* object_data)[OUTPUT_NUMBER],unsigned char);
void calculate_hidden_error(double * hidden_data,double * e_hidden,double (* w_hid_out)[OUTPUT_NUMBER]);
int calculate_all_error(double * e_output,double * MIN_E);
void change_w_hid_out(double (* w_hid_out)[OUTPUT_NUMBER],double * hidden_data,double * output_data,double (* object_data)[10],unsigned char num);//改变隐藏层和输出层的误差
void change_w_in_hid(double (* w_in_hid)[HIDDEN_NUMBER],double (* w_hid_out)[OUTPUT_NUMBER],double * input_data,double * hidden_data,double * output_data,double (* object_data)[OUTPUT_NUMBER],unsigned char num);//改变输入层和隐藏层的误差
void write_i_h_value(FILE * fp_input_hidden,double (* w_in_hid)[HIDDEN_NUMBER]);
void write_h_o_value(FILE * fp_hidden_output,double (* w_hid_out)[OUTPUT_NUMBER]);
double test_work(double (* w_in_hid)[HIDDEN_NUMBER],double (* w_hid_out)[OUTPUT_NUMBER]);
void change_e_output(double * e_output,unsigned char num);
#endif //C2023_CHALLENGE_FUNCTIONS_H
