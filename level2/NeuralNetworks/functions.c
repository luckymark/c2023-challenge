#include "basical_parameter.h"
#include<stdlib.h>
#include<math.h>
void clear_images_data(FILE * fp){
    unsigned int drop;
    for(int i=1;i<=4;i++)
        fread(&drop,sizeof(unsigned int),1,fp);
}
void clear_label_data(FILE * fp){
    unsigned int drop;
    for(int i=1;i<=2;i++)
        fread(&drop,sizeof(unsigned int),1,fp);
}
void transform(FILE * fp_train_images,double * input){
    unsigned char data;
    for(int i=0;i<PHOTO_SIZE;i++){
        for(int j=0;j<PHOTO_SIZE;j++){//input也是从0开始记录的
            int num=i*PHOTO_SIZE+j;
            fread(&data,sizeof(unsigned char),1,fp_train_images);
            input[num]=((double)data)/255.0;//将像素矩阵压缩到0至1之间
            if(input[num]==0)
                input[num]=0.01;
        }
    }
}
void creat_random_value(FILE * fp,int start,int end){//本程序所有的数组存储均从0开始,创建初始权值矩阵
    double range=sqrt(6.0/(start+end));
    for(int i=0;i<start;i++){
        for(int j=0;j<end;j++){
            double random=(double)((rand()%1000))*0.001*2*range-range;
            fprintf(fp,"%10.5lf",random);
        }
        fprintf(fp,"\n");
    }
}
void get_i_h_value(FILE * fp,double (* w)[HIDDEN_NUMBER]){//取出输入层和隐藏层的权值矩阵
    for(int i=0;i<INPUT_NUMBER;i++){
        for(int j=0;j<HIDDEN_NUMBER;j++){
            fscanf(fp,"%lf",&w[i][j]);
        }
    }
}
void get_h_o_value(FILE * fp,double (* w)[OUTPUT_NUMBER]){//取出隐藏层和输出层的权值矩阵
    for(int i=0;i<HIDDEN_NUMBER;i++){
        for(int j=0;j<OUTPUT_NUMBER;j++){
            fscanf(fp,"%lf",&w[i][j]);
        }
    }
}
double sigmoid(double x){
    return 1/(1+exp((-1)*x));
}
void calculate_hidden_layer(double * input_data,double * hidden_data,double (* w_in_hid)[HIDDEN_NUMBER]){//计算隐藏层的sigmoid值
    for(int i=0;i<HIDDEN_NUMBER;i++){
        for(int j=0;j<INPUT_NUMBER;j++){
            hidden_data[i]+=input_data[j]*w_in_hid[j][i];
        }
        hidden_data[i]=sigmoid(hidden_data[i]);
    }
}
void calculate_output_layer(double * hidden_data,double * output_data,double (* w_hid_out)[OUTPUT_NUMBER]){//计算输出层的sigmoid值
    for(int i=0;i<OUTPUT_NUMBER;i++){
        for(int j=0;j<HIDDEN_NUMBER;j++){
            output_data[i]+=hidden_data[j]*w_hid_out[j][i];
        }
        output_data[i]=sigmoid(output_data[i]);
    }
    printf("output: ");
    for(int i=0;i<OUTPUT_NUMBER;i++){
        printf("%.5lf ",output_data[i]);
    }
    printf("\n");
}
void calculate_output_error(double * output_data,double * e_output,double (* object_data)[OUTPUT_NUMBER],unsigned char num){
    for(int i=0;i<OUTPUT_NUMBER;i++){
        if(object_data[num][i]==1&&output_data[i]<0.01)
            output_data[i]=0.01;
        if(object_data[num][i]==0&&output_data[i]>0.99)
            output_data[i]=0.99;
        e_output[i]=-(object_data[num][i]*log(output_data[i])+(1-object_data[num][i])* log((1-output_data[i])));
    }
//    printf("\n\n");
//    for(int i=0;i<OUTPUT_NUMBER;i++){
//        printf("%.5lf ",e_output[i]);
//    }
//    printf("\n\n");
}
int calculate_all_error(double * e_output,double * MIN_E){
    double E=0;
    for(int i=0;i<OUTPUT_NUMBER;i++){
        E+=e_output[i];
    }
    E/=OUTPUT_NUMBER;
    if(*MIN_E<0){
        *MIN_E=E;
        return 1;
    }
    if(E<*MIN_E){
        *MIN_E=E;
        return -1;
    }
    else{
        return 1;
    }

}
void change_e_output(double * e_output,unsigned char num){
    for(int i=0;i<OUTPUT_NUMBER;i++){
        if(i!=num)
            e_output[i]=(-1)*e_output[i];
    }
}
void calculate_hidden_error(double * out_put_data,double * e_hidden,double (* w_hid_out)[OUTPUT_NUMBER]){
    for(int j=0;j<OUTPUT_NUMBER;j++){
        double all_w=0;
        for(int i=0;i<HIDDEN_NUMBER;i++){
            all_w+=w_hid_out[i][j];
        }
        for(int i=0;i<HIDDEN_NUMBER;i++){
            e_hidden[i]+=w_hid_out[i][j]*out_put_data[j]/all_w;
        }
    }
}
void change_w_hid_out(double (* w_hid_out)[OUTPUT_NUMBER],double * hidden_data,double * output_data,double (* object_data)[10],unsigned char num){
    for(int i=0;i<HIDDEN_NUMBER;i++){
        for(int j=0;j<OUTPUT_NUMBER;j++){
            w_hid_out[i][j]=w_hid_out[i][j]+ALPHA*(object_data[num][j]-output_data[j])*hidden_data[i];
        }
    }
}
void change_w_in_hid(double (* w_in_hid)[HIDDEN_NUMBER],double (* w_hid_out)[OUTPUT_NUMBER],double * input_data,double * hidden_data,double * output_data,double (* object_data)[OUTPUT_NUMBER],unsigned char num){
    for(int i=0;i<INPUT_NUMBER;i++){
        for(int j=0;j<HIDDEN_NUMBER;j++){
            double temp=0;
            for(int k=0;k<OUTPUT_NUMBER;k++){
                temp+=(-1.0)/OUTPUT_NUMBER*(object_data[num][k]-output_data[k])*w_hid_out[j][k];
            }
            w_in_hid[i][j]=w_in_hid[i][j]-ALPHA*hidden_data[j]*(1-hidden_data[j])*input_data[i]*temp;
        }
    }
}
void write_i_h_value(FILE * fp_input_hidden,double (* w_in_hid)[HIDDEN_NUMBER]){
    rewind(fp_input_hidden);
    for(int i=0;i<INPUT_NUMBER;i++){
        for(int j=0;j<HIDDEN_NUMBER;j++){
            fprintf(fp_input_hidden,"%10.5f",w_in_hid[i][j]);
        }
        fprintf(fp_input_hidden,"\n");
    }
}
void write_h_o_value(FILE * fp_hidden_output,double (* w_hid_out)[OUTPUT_NUMBER]){
    rewind(fp_hidden_output);
    for(int i=0;i<HIDDEN_NUMBER;i++){
        for(int j=0;j<OUTPUT_NUMBER;j++){
            fprintf(fp_hidden_output,"%10.5f",w_hid_out[i][j]);
        }
        fprintf(fp_hidden_output,"\n");
    }
}
double test_work(double (* w_in_hid)[HIDDEN_NUMBER],double (* w_hid_out)[OUTPUT_NUMBER]){
    int correct=0;
    int whole=0;
    double rate=0;
    double input_data[INPUT_NUMBER]={0};//输出层
    double hidden_data[HIDDEN_NUMBER]={0};//隐藏层
    double output_data[OUTPUT_NUMBER]={0};//输出层
    FILE * fp_train_images=fopen("D:/githubdesktop/c2023-challenge/level2/NeuralNetworks/MNIST_data/t10k-images.idx3-ubyte","rb");
    FILE * fp_train_labels=fopen("D:/githubdesktop/c2023-challenge/level2/NeuralNetworks/MNIST_data/t10k-labels.idx1-ubyte","rb");
    clear_images_data(fp_train_images);
    clear_label_data(fp_train_labels);
    FILE * fp_test_data=fopen("D:/githubdesktop/c2023-challenge/level2/NeuralNetworks/test_data.txt","w");
    FILE * fp_given_data=fopen("D:/githubdesktop/c2023-challenge/level2/NeuralNetworks/given_data.txt","w");
    for(int i=1;i<=TEST_DATA_CAPACITY;i++){
        transform(fp_train_images, input_data);
        calculate_hidden_layer(input_data, hidden_data, w_in_hid);//根据输入层计算隐藏层
        calculate_output_layer(hidden_data, output_data, w_hid_out);//根据隐藏层计算输出层
        double max=-1;
        int answer=0;
        for(int j=0;j<OUTPUT_NUMBER;j++){
            if(output_data[j]>max){
                answer=j;
                max=output_data[j];
            }
        }
        unsigned char num;
        fread(&num,sizeof(unsigned char),1,fp_train_labels);
        if(num==answer){
            correct++;
        }
        fprintf(fp_test_data,"%3d",num);
        fprintf(fp_given_data,"%3d",answer);
    }
    fclose(fp_train_labels);
    fclose(fp_train_images);
    fclose(fp_given_data);
    fclose(fp_test_data);
    whole=TEST_DATA_CAPACITY;
    rate=(double)correct/(double)whole;
    return rate;
}