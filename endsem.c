#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item{
    char name[100];
    int qty, price;
} item;

int main(){
    printf("Welcome To Our Store\n\n");
    char fname[20] = {"Items.txt"};
    FILE* file = fopen(fname, "a+");
    if(file == NULL){
        printf("Some Error Ocurred\n");
        return -1;
    }
    int x = -2;
    while(1){
        printf("(1) - for adding an item in the list\n");
        printf("(2) - for listing all items in the list\n");
        printf("(3) - for deleting an item in the list\n");
        printf("(-1) - to exit\n");
        scanf("%d", &x);
        if(x != -1 && x != -2) file = fopen(fname, "a+");
        if(x == -1) break;
        if(x == 1){
            item i;
            printf("Enter the name of the item: ");
            getchar();
            gets(i.name);
            printf("Enter the quantity: ");
            scanf("%d", &i.qty);
            printf("Enter the price: ");
            scanf("%d", &i.price);
            fprintf(file, "%s\n%d\n%d\n\n", i.name, i.qty, i.price);
        } else if(x == 2) {
            printf("\n");
            item i;
            char str[100];
            int a = 0, c = 0;
            while(fgets(str, 100, file)){
                if(str[0] == '\n'){
                    printf("---------- %d ----------\n", c + 1);
                    printf("Name : %sQuantity : %d\nPrice : %d\n", i.name, i.qty, i.price);
                    a = 0;
                    c++;
                    continue;
                }
                if(a == 0) strcpy(i.name, str); 
                else if(a == 1) i.qty = atoi(str);
                else i.price = atoi(str);
                a++;
            }
            printf("\n");
        } else {
            char name[100], str[100], e[100];
            printf("Enter the name of the item to remove: ");
            getchar();
            gets(name);
            FILE* temp = fopen("temp.txt", "w");
            int a = 0;
            while(fgets(str, 100, file)){
                strcpy(e, str);
                if(strcmp(name, e) == 0 || (sscanf(e, "%[^\n]%*c\n", e) && strcmp(name, e) == 0)){
                    printf("GOTIT\n");
                    a = 1;
                    continue;
                }
                if(a == 1 || a == 2 || a == 3){
                    a++;
                    continue;
                }
                fprintf(temp, "%s", str);
            }
            fclose(file);
            fclose(temp);
            temp = fopen("temp.txt", "r");
            file = fopen("Items.txt", "w");
            while(fgets(str, 100, temp)){
                fprintf(file, "%s", str);
            }
            fclose(temp);
            remove("temp.txt");
        }
        fclose(file);
    }
    printf("\nThanks\n");
    return 0;
}
