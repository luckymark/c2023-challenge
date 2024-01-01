#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_NODES 784 // 28x28像素的图像(minist图片集给的尺寸是这个，8*8的貌似找不到合适的图片输入，除非手打）
#define HIDDEN_NODES 100
#define OUTPUT_NODES 10 // 对应0-9的数字
#define LEARNING_RATE 0.1

double inputLayer[INPUT_NODES];
double hiddenLayer[HIDDEN_NODES];
double outputLayer[OUTPUT_NODES];
double weightsIH[INPUT_NODES][HIDDEN_NODES];
double weightsHO[HIDDEN_NODES][OUTPUT_NODES];

// Sigmoid激活函数
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// 前馈网络
void feedForward(double input[INPUT_NODES], double target[OUTPUT_NODES], 
                     double hidden[HIDDEN_NODES], double output[OUTPUT_NODES], 
                     double weightsIH[INPUT_NODES][HIDDEN_NODES], double weightsHO[HIDDEN_NODES][OUTPUT_NODES]) {
    // 输入层到隐藏层
    for (int i = 0; i < HIDDEN_NODES; i++) {
        hiddenLayer[i] = 0.0;
        for (int j = 0; j < INPUT_NODES; j++) {
            hiddenLayer[i] += inputLayer[j] * weightsIH[j][i];
        }
        hiddenLayer[i] = sigmoid(hiddenLayer[i]);
    }

    // 隐藏层到输出层
    for (int i = 0; i < OUTPUT_NODES; i++) {
        outputLayer[i] = 0.0;
        for (int j = 0; j < HIDDEN_NODES; j++) {
            outputLayer[i] += hiddenLayer[j] * weightsHO[j][i];
        }
        outputLayer[i] = sigmoid(outputLayer[i]);
    }
}

// 反向传播和权重更新
void backpropagation(double input[INPUT_NODES], double target[OUTPUT_NODES], 
                     double hidden[HIDDEN_NODES], double output[OUTPUT_NODES], 
                     double weightsIH[INPUT_NODES][HIDDEN_NODES], double weightsHO[HIDDEN_NODES][OUTPUT_NODES]) {
    // 计算输出层的误差和梯度
    double outputErrors[OUTPUT_NODES];
    double gradientsHO[HIDDEN_NODES][OUTPUT_NODES];
    for (int i = 0; i < OUTPUT_NODES; i++) {
        outputErrors[i] = target[i] - output[i]; // 误差计算
        gradientsHO[i][i] = outputErrors[i] * sigmoid_derivative(output[i]); // 梯度计算
    }
    
    // 计算隐藏层的误差和梯度，并更新权重HO和权重IH
    double hiddenErrors[HIDDEN_NODES];
    double gradientsIH[INPUT_NODES][HIDDEN_NODES];
    for (int i = 0; i < HIDDEN_NODES; i++) {
        hiddenErrors[i] = 0;
        for (int j = 0; j < OUTPUT_NODES; j++) {
            hiddenErrors[i] += weightsHO[i][j] * outputErrors[j]; // 误差计算
        }
        gradientsIH[i][i] = hiddenErrors[i] * sigmoid_derivative(hidden[i]); // 梯度计算
        for (int j = 0; j < OUTPUT_NODES; j++) { // 更新权重HO
            weightsHO[i][j] += LEARNING_RATE * gradientsHO[i][j]; 
        }           
// 更新权重IH   
    }
}


int main() {
    // 初始化权重（此处使用随机值）
    for (int i = 0; i < INPUT_NODES; i++) {
        for (int j = 0; j < HIDDEN_NODES; j++) {
            weightsIH[i][j] = (rand() % 2000 - 1000) / 1000.0; // -1到1之间的随机数
        }
    }
    for (int i = 0; i < HIDDEN_NODES; i++) {
        for (int j = 0; j < OUTPUT_NODES; j++) {
            weightsHO[i][j] = (rand() % 2000 - 1000) / 1000.0; // -1到1之间的随机数
        }
    }

    // 假设我们有一个手写数字的图像数据存储在inputLayer数组中
    // ... 加载或处理输入数据的代码 ...
    feedForward(input[INPUT_NODES], target[OUTPUT_NODES], 
                    hidden[HIDDEN_NODES], output[OUTPUT_NODES], 
                     weightsIH[INPUT_NODES][HIDDEN_NODES], weightsHO[HIDDEN_NODES][OUTPUT_NODES]); // 前馈网络，得到输出结果在outputLayer数组中
    backpropagation(input[INPUT_NODES], target[OUTPUT_NODES], 
                    hidden[HIDDEN_NODES], output[OUTPUT_NODES], 
                     weightsIH[INPUT_NODES][HIDDEN_NODES], weightsHO[HIDDEN_NODES][OUTPUT_NODES]); // 根据输出结果进行反向传播和权重更新
    // ... 可以根据outputLayer数组中的值来判断识别的数字 ...
    return 0;
}




#define OUTPUT_ERROR_THRESHOLD 0.01 // 输出层误差阈值
#define HIDDEN_ERROR_THRESHOLD 0.01 // 隐藏层误差阈值
#define LEARNING_RATE 0.1 // 学习率

// Sigmoid函数的导数
double sigmoidDerivative(double x) {
    return x * (1.0 - x);
}

// 反向传播和权重更新
void backpropagation() {
    // 计算输出层的误差
    double outputErrors[OUTPUT_NODES];
    for (int i = 0; i < OUTPUT_NODES; i++) {
        double target = (i == targetLabel) ? 1.0 : 0.0; // 目标值为1或0，取决于当前样本的标签
        double error = target - outputLayer[i];
        outputErrors[i] = error;
    }

    // 计算隐藏层的误差
    double hiddenErrors[HIDDEN_NODES];
    for (int i = 0; i < HIDDEN_NODES; i++) {
        hiddenErrors[i] = 0.0;
        for (int j = 0; j < OUTPUT_NODES; j++) {
            hiddenErrors[i] += outputErrors[j] * weightsHO[i][j];
        }
        hiddenErrors[i] *= sigmoidDerivative(hiddenLayer[i]);
    }

    // 更新权重
    for (int i = 0; i < HIDDEN_NODES; i++) {
        for (int j = 0; j < OUTPUT_NODES; j++) {
            double gradient = outputErrors[j] * sigmoidDerivative(outputLayer[j]);
            weightsHO[i][j] += LEARNING_RATE * hiddenLayer[i] * gradient;
        }
    }
    for (int i = 0; i < INPUT_NODES; i++) {
        for (int j = 0; j < HIDDEN_NODES; j++) {
            double gradient = hiddenErrors[j] * sigmoidDerivative(hiddenLayer[j]);
            weightsIH[i][j] += LEARNING_RATE * inputLayer[i] * gradient;
        }
    }
}
