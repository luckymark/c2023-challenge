#include<stdio.h>
#include"train_data.h"//训练的时候暂时将原点阵转化成input列向量，这个过程需要将二维数组中的数值进行转化并且存储到一维数组中
//但是可以将数值转化这一步直接忽略，一开始就设置好数组中的值。
#include"basical_parameter.h"
#include "functions.h"
#include<time.h>
#include<stdlib.h>
FILE * fp_input_hidden;
FILE * fp_hidden_output;
FILE * error_r;
FILE * fp_train_images;
FILE * fp_train_labels;
double input_data[INPUT_NUMBER]={0};//输出层
double hidden_data[HIDDEN_NUMBER]={0};//隐藏层
double output_data[OUTPUT_NUMBER]={0};//输出层
double w_in_hid[INPUT_NUMBER][HIDDEN_NUMBER]={0};//输入层和隐藏层的权值
double w_hid_out[HIDDEN_NUMBER][OUTPUT_NUMBER]={0};//隐藏层和输出层的权值
double e_output[OUTPUT_NUMBER]={0};//计算输出层误差
double e_hidden[HIDDEN_NUMBER]={0};//计算隐藏层误差
double MIN_E=-1;//记录最小误差，如果数值小于0，则说明是第一次，第一次不仅要存储误差，而且要更改权值
int main(){
    srand(time(0));
    fp_input_hidden=fopen("D:/githubdesktop/c2023-challenge/level2/NeuralNetworks/w_input_hidden.txt","w");
    fp_hidden_output=fopen("D:/githubdesktop/c2023-challenge/level2/NeuralNetworks/w_hidden_output.txt","w");
    error_r=fopen("D:/githubdesktop/c2023-challenge/level2/NeuralNetworks/error_r.txt","w");
    fp_train_images=fopen("D:/githubdesktop/c2023-challenge/level2/NeuralNetworks/MNIST_data/train-images.idx3-ubyte","rb");
    fp_train_labels=fopen("D:/githubdesktop/c2023-challenge/level2/NeuralNetworks/MNIST_data/train-labels.idx1-ubyte","rb");
    clear_images_data(fp_train_images);
    clear_label_data(fp_train_labels);
    creat_random_value(fp_input_hidden,INPUT_NUMBER,HIDDEN_NUMBER);
    creat_random_value(fp_hidden_output,HIDDEN_NUMBER,OUTPUT_NUMBER);//权值的范围是-5到5（试试）
    fclose(fp_input_hidden);
    fclose(fp_hidden_output);

    for(int times=1;times<=TRAIN_TIMES;times++) {
        fprintf(error_r,"%d:\n",times);
        for (int turn = 0; turn < TRAIN_DATA_CAPACITY; turn++) {
            printf("%d\n",turn);
            transform(fp_train_images, input_data);
            /*for(int i=0;i<INPUT_NUMBER;i++){
                    printf("%.5f ",input_data[i]);
            }*/
            fp_input_hidden = fopen("D:/githubdesktop/c2023-challenge/level2/NeuralNetworks/w_input_hidden.txt", "r+");
            fp_hidden_output = fopen("D:/githubdesktop/c2023-challenge/level2/NeuralNetworks/w_hidden_output.txt", "r+");//看看这个地方能不能修改，不用反复开关文件
            get_i_h_value(fp_input_hidden, w_in_hid);//取出输入层和隐藏层的权值
            get_h_o_value(fp_hidden_output, w_hid_out);//取出隐藏层和输出层的权值
            calculate_hidden_layer(input_data, hidden_data, w_in_hid);//根据输入层计算隐藏层
            calculate_output_layer(hidden_data, output_data, w_hid_out);//根据隐藏层计算输出层
            unsigned char num;
            fread(&num,sizeof(unsigned char),1,fp_train_labels);
            printf("%d\n",num);
            calculate_output_error(output_data, e_output, object_data,num);//计算输出层误差
            int test = calculate_all_error(e_output,&MIN_E);//计算总误差，总误差要和MIN_E比较，如果是第一次计算误差，则返回1，表示需要修改权值；
            //如果计算得到的误差比MIN_E小，则修改MIN_E,但是返回-1，表示不需要修改权值
            //如果计算得到的误差比MIN_E大，，则不修改MIN_E，返回1，表示需要修改权值
            fprintf(error_r,"%lf\n",MIN_E);
            if (test == -1){
                fclose(fp_input_hidden);
                fclose(fp_hidden_output);
                continue;
            }
            calculate_hidden_error(hidden_data, e_hidden,w_hid_out);//计算隐藏层误差
            //change_e_output(e_output,num);
            change_w_in_hid(w_in_hid,w_hid_out,input_data,hidden_data,output_data,object_data,num);//改变输入层和隐藏层的误差权值
            change_w_hid_out(w_hid_out,hidden_data,output_data,object_data,num);//改变隐藏层和输出层的权值
//            for(int i=0;i<HIDDEN_NUMBER;i++){
//                for(int j=0;j<OUTPUT_NUMBER;j++){
//                    printf("%.5lf ",w_hid_out[i][j]);
//                }
//                printf("\n");
//            }
            write_i_h_value(fp_input_hidden,w_in_hid);//写入输入层和隐藏层的权值
            write_h_o_value(fp_hidden_output,w_hid_out);//写入隐藏层和输出层的权值
            fclose(fp_input_hidden);
            fclose(fp_hidden_output);
        }
    }
    double proper_rate=test_work(w_in_hid,w_hid_out);//最后两个权值函数中存储的就是最终的权值。
    printf("%lf",proper_rate);
    fclose(fp_train_images);
    fclose(fp_train_labels);
    fclose(error_r);
    return 0;
}