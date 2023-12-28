#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义货物结构体
typedef struct {
    char model[50];  // 型号
    int quantity;    // 数量
} Item;

// 定义库存结构体
typedef struct {
    Item items[100]; // 假设最多100种货物
    int size;        // 当前货物数量
} Inventory;

// 从文件中读取库存数据
void loadInventory(Inventory *inv, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件：%s\n", filename);
        return;
    }
    inv->size = 0;
    while (fscanf(file, "%s %d", inv->items[inv->size].model, &inv->items[inv->size].quantity) != EOF) {
        inv->size++;
    }
    fclose(file);
}

// 将库存数据保存到文件
void saveInventory(const Inventory *inv, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件：%s\n", filename);
        return;
    }
    for (int i = 0; i < inv->size; i++) {
        fprintf(file, "%s %d\n", inv->items[i].model, inv->items[i].quantity);
    }
    fclose(file);
}

// 显示存货列表
void showInventory(const Inventory *inv) {
    printf("存货列表：\n");
    for (int i = 0; i < inv->size; i++) {
        printf("%s: %d\n", inv->items[i].model, inv->items[i].quantity);
    }
}

// 入库操作
void addItem(Inventory *inv) {
    if (inv->size >= 100) {
        printf("库存已满，无法添加新货物。\n");
        return;
    }
    printf("请输入货物型号：");
    scanf("%s", inv->items[inv->size].model);
    printf("请输入货物数量：");
    scanf("%d", &inv->items[inv->size].quantity);
    inv->size++;
}

// 出库操作
void removeItem(Inventory *inv) {
    char model[50];
    printf("请输入要出库的货物型号：");
    scanf("%s", model);
    for (int i = 0; i < inv->size; i++) {
        if (strcmp(inv->items[i].model, model) == 0) {
            if (inv->items[i].quantity > 0) {
                inv->items[i].quantity--;
                printf("成功出库 %s 一件。\n", model);
                return;
            } else {
                printf("库存不足，无法出库 %s。\n", model);
                return;
            }
        }
    }
    printf("未找到货物：%s\n", model);
}

int main() {
    Inventory inv;
    loadInventory(&inv, "inventory.txt"); // 从文件读取库存数据，假设文件名为inventory.txt，格式为“型号 数量”每行一种货物。如果文件不存在，则创建一个空库存。
    int choice;
    do {
        printf("\n菜单：\n");
        printf("1. 显示存货列表\n");
        printf("2. 入库\n");
        printf("3. 出库\n");
        printf("4. 退出程序\n");
        printf("请选择菜单功能（1-4）：");
        scanf("%d", &choice);
        switch (choice) {
            case 1: // 显示存货列表。
