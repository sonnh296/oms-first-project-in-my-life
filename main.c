#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
char function_choice();
void add_product();
void update_product();
void delete_product();
void order_product();
void sort_by_name();
void sort_by_price();
void search_by_id();

void clear (void){
    while (getchar() != '\n');
}

struct product{
    char id[7];
    int price;
    char name[30];
}pro[50], temppro[50], buffer[50];

struct top5{
    char id5[7];
    char name5[30];
    int soluong;
}id5[5];

struct getid{
    char ten[30];
    char diachi[50];
    char masoao[15];
    char sdt[12];
    float tongchi;
}orderid[50];

void getinfor(int *i)
{
    FILE *p, *ptr, *p5, *pid;
    p = fopen("oms.txt", "r");
    ptr = fopen("synthetic.txt", "r");
    p5 = fopen("top5.txt", "w");
    pid = fopen("saveorder.txt", "r");
    while(fscanf(p, "%10s%30[^\n]%10d", pro[*i].id, pro[*i].name, &pro[*i].price) != EOF){
	    *i += 1;
    }
    
    rewind(p);
    //=========++============++==========++============++==========+========++==//
    //lay thong tin tu file chuyen qua buffer de sap xep, lay thong tin tu tong hop so luong de tim top 5 sp//
    int t = 0;
    while(fscanf(p, "%10s%30[^\n]%10d", buffer[t].id, buffer[t].name, &buffer[t].price) != EOF){
	    t += 1;
    }
    
    int j, pos, count = 0, max;
    
    t = 0;
    while(fscanf(ptr, "%10s%30[^\n]%10d", temppro[t].id, temppro[t].name, &temppro[t].price) != EOF){
	    t += 1;
    }
    //==========//lay thong tin id//
    int e = 0;
    while(fscanf(pid, "%15s%25s%30s%10s%10f", orderid[e].masoao, orderid[e].ten, orderid[e].diachi, orderid[e].sdt, &orderid[e].tongchi) != EOF){
        e += 1;
    }
    //=========++============++==========++============++==========+========++==//
    //tim top 5 sp ban chay//
    int danhdau[50] = {0};
    
    do{
        max = -1;
        pos = -1;
        for(j = 0; j < *i; j++){
            if(temppro[j].price > max && danhdau[j] == 0){
                max = temppro[j].price;
                pos = j;
            }
        }
        
        danhdau[pos] = 1;
        strcpy(id5[count].id5, temppro[pos].id);
        strcpy(id5[count].name5, temppro[pos].name);
        id5[count].soluong = temppro[pos].price;
        count += 1;
    }while(count < 5);
    
    for(t = 0; t < 5; t++){
        fprintf(p5, "%10s%30s%10d\n", id5[t].id5, id5[t].name5, id5[t].soluong);
    }
    //=========++============++==========++============++==========+========++==//
    for(t = 0; t < *i; t++){
        fprintf(ptr, "%10s%30s%10d\n", pro[t].id, pro[t].name, temppro[t].price);
    }
    fclose(p);
    fclose(ptr);
    fclose(p5);
    fclose(pid);
}

void printtofile(int *i)
{
    FILE *p;
    p = fopen("oms.txt", "w");
    
    int j;
    for(j = 0; j < *i; j++){
        fprintf(p, "%10s%30s%10d\n", pro[j].id, pro[j].name, pro[j].price);
    }
    fclose(p);
}

int main()
{
    
    char choice;
    int i = 0;
	getinfor(&i);
	
	do
	{				
		choice = function_choice();						
		
		switch (choice)
		{
			case 'a':
				add_product(&i);
				break;
			case 'u':
				update_product(&i);	
				break;
			case 'd':
				delete_product(&i);	
				break;
			case 'o':
			    order_product(&i);
			    break;
			case 'n':
			    sort_by_name(&i);
			    break;
			case 's':
			    search_by_id(&i);
			    break;
			case 'p':
			    sort_by_price(&i);
			    break;
		}
		
	} while (choice != 'q'); 
	
	printtofile(&i);
	
}

char function_choice()
{	
	char choice;
	system("cls");
	printf("\nOrder Management System\n");
	printf("=======================\n");	
	
	printf("\na) Add new product\n");
	printf("\nu) Update a product\n");		
	printf("\nd) Delete a product\n");
	printf("\nn) Sort products by their name\n");
	printf("\np) Show products by increasing price\n");
	printf("\no) Order product\n");
	printf("\ns) Search an order by name\n");
	printf("\nq) Quit\n");
	
	printf("\n---\n");
	printf("Enter a letter (a, u, d, n, p, o, q) to select the corresponding function: ");
	
	fflush(stdin);
	scanf("%c%*c", &choice);
	system("cls");
	
	return choice;
}  

void add_product(int *i)
{	
    int flag, j, k;
    do{
        flag = 1;
	    printf("Add a new product:\n");
	    printf("==================\n\n");
	
	    printf("Enter product ID : ");
	    scanf("%s%*c", pro[*i].id);
	
	    printf("Enter price of product : ");
	    scanf("%d%*c", &pro[*i].price);
	
	    printf("Enter product name : ");
	    scanf("%[^\n]", pro[*i].name);
	
	    for(j = 0; j < *i && flag ==1; j++){
	        if(strcmp(pro[*i].id, pro[j].id) == 0){
	            printf("\nID ALREADY EXISTS\n");
	            flag = 0;
	        }
	    }
	
        if(pro[*i].id[0]<65 || pro[*i].id[0]>90 || pro[*i].id[1]<65 || pro[*i].id[1]>90 || pro[*i].id[2]<65 || pro[*i].id[2]>90){
	        printf("\n3 FIRST CHARACTERS MUST BE CAPITAL LETTERS\n");
	        flag = 0;
	        clear();
	   }
	   if(pro[*i].id[3]>57 || pro[*i].id[3]<48 || pro[*i].id[4]>57 || pro[*i].id[4]<48 || pro[*i].id[5]>57 || pro[*i].id[5]<48 ){
	        printf("\n3 LAST CHARACTERS MUST BE DIGITS\n");
	        flag = 0;
	        clear();
	   }
	   
	   for(k = 0; k < strlen(pro[*i].name); k++){
	       if(pro[*i].name[k] > 32 && pro[*i].name[k] < 40){
	           printf("\nDO NOT USE SPECIAL SYMBOLS\n");
	           flag = 0;
	       }
	   }
    }while (flag == 0);
    
    *i += 1;
	
}

void update_product(int *i)
{
    
    char maso[7];
	printf("Update a product:\n");
	printf("=================\n\n");
	
	printf("Enter product ID :");
	scanf("%s%*c", maso);
	
    int k, flag = 0;
	
	for(k = 0; k < *i && flag == 0; k++){
	    if(strcmp(maso, pro[k].id) == 0){
	        printf("Enter new price :");
	        scanf("%d%*c", &pro[k].price);
	        printf("Enter new name :");
	        scanf("%[^\n]", pro[k].name);
	        flag = 1;
	    }
	}
	
	if(flag == 0)
	    printf("\nPRODUCT DOES NOT EXIST!!! PLEASE TRY AGAIN\n");
	
}

void delete_product(int *i)
{
    
    char maso[7];
	printf("Delete a product:\n");
	printf("=================\n\n");
	
	printf("Enter product ID :");
	scanf("%s%*c", maso);
	
	int k, l, t, flag = 0;
	
	for(k = 0; k < *i && flag == 0; k++){
	    if(strcmp(maso, pro[k].id) == 0){
	        
	        for(l = k; l < *i - 1; l++){
	            strcpy(pro[l].id, pro[l  + 1].id);
	            pro[l].price = pro[l + 1].price;
	            strcpy(pro[l].name, pro[l + 1].name);
	        }
	        for(t = k; t < *i - 1; t++){
	            strcpy(temppro[t].id, temppro[t  + 1].id);
	            temppro[t].price = temppro[t + 1].price;
	            strcpy(temppro[t].name, temppro[t + 1].name);
	        }
	        
	        *i -= 1;
	        flag = 1;
	    }
	}
	if(flag == 0)
	    printf("\nPRODUCT DOES NOT EXIST!!! PLEASE TRY AGAIN\n");
}

void order_product(int *i)
{
    FILE *po;
    po = fopen("order.txt", "a");
    time_t rawtime;
    struct tm *info;
    char curtime[15];

    time( &rawtime );
    info = localtime( &rawtime );
    strftime(curtime,15,"%d%m%Y%H%M%S", info);
   
    int vn = (info->tm_hour + 7)%24;
    curtime[9] = vn%10 + 48;
    curtime[8] = (vn/10)%10 + 48;
    
    char cusname[40], phone[12], shipadd[50], masanpham[7];
    int listpro[100][2], discount = 10, j, k, flag, wanttoadd;
    float totalprice;

     //===========================================
     FILE *ptr;
    ptr = fopen("synthetic.txt", "r");
    
    int t = 0, r, haveswap;
    while(fscanf(ptr, "%10s%30[^\n]%10d", temppro[t].id, temppro[t].name, &temppro[t].price) != EOF){
	    t += 1;
    }
    
    do{
        flag = 0;
        printf("Enter ID of product: ");
        scanf("%s", masanpham);
        
        for(j = 0; j < *i; j++){
            if(strcmp(masanpham, pro[j].id) == 0){
                listpro[j][0] = 1;
                printf("Enter quantity: ");
                scanf("%d", &listpro[j][1]);
                flag = 1;
            }
        }
        if(flag == 0){
            printf("Product does not exists !");
            clear();
        }
        
        printf("Enter 1 to add more Product, 0 to stop.");
        scanf("%d%*c", &wanttoadd);
        
    }while(wanttoadd == 1);
    //===========================================
    
            for(t = 0; t < *i; t++){
                if(listpro[t][0] == 1)
                    temppro[t].price += listpro[t][1];
            }
    fclose(ptr);
    ptr = fopen("synthetic.txt", "w");
    t = 0;
    for(t = 0; t < *i; t++){
        fprintf(ptr, "%10s%30s%10d\n", pro[t].id, pro[t].name, temppro[t].price);
    }
    fclose(ptr);
    //==============================================
    printf("Enter customer name :");
    scanf("%[^\n]", cusname);
    printf("Enter phone number: ");
    scanf("%s%*c", phone);
    printf("Enter address: ");
    scanf("%[^\n]%*c", shipadd);
    
    float sum = 0;
    for(j = 0; j < *i; j++){
        if(listpro[j][0] ==1)
            sum += listpro[j][1] * pro[j].price;
    }
    totalprice = (float)(sum - sum/10);
    //================================================================================//
    //print to screen//
    printf("%s", "\n\n\n\t===============================================\n");
    printf("%s %s", "\tORDER INFORMATION\n\tOrder ID : ", curtime);
    printf("%s %s", "\n\t\tName: ", cusname);
    printf("%s %s", "\n\t\tPhone number: ", phone);
    printf("%s %s", "\n\t\tShipping address: ", shipadd);
    printf("%s", "\n\t-----------------------------------------------\n");
    for(k = 0; k < *i ; k++){
        if(listpro[k][0] == 1){
            printf("%s %s %s %d %s %d %s", "\n\t +) Product ID :", pro[k].id, "with quantity : ", listpro[k][1], "x", pro[k].price, "$\n");
        }
    }
    printf("%s", "\t-----------------------------------------------\n");
    printf("%s", "\tDiscount 10%\n");
    printf("%s %.2f %s", "\tTotal price :", totalprice, "$");
    printf("%s", "\n\t===============================================\n\n\n\n");
    //================================================================================//
    //print to file//
    fprintf(po, "%s %s", "ORDER INFORMATION\n\tOrder ID : ", curtime);
    fprintf(po, "%s %s", "\n\tName: ", cusname);
    fprintf(po, "%s %s", "\n\tPhone number: ", phone);
    fprintf(po, "%s %s", "\n\tShipping address: ", shipadd);
    fprintf(po, "%s", "\n-----------------------------------------------\n");
    for(k = 0; k <*i ; k++){
        if(listpro[k][0] == 1){
            fprintf(po, "%s %s %s %d %s %d %s", "\n +) Product ID :", pro[k].id, "with quantity : ", listpro[k][1], "x", pro[k].price, "$");
            fprintf(po, "%s", "\n");
        }
    }
    fprintf(po, "%s", "-----------------------------------------------\n");
    fprintf(po, "%s", "Discount 10%\n");
    fprintf(po, "%s %.2f %s", "Total price :", totalprice, "$");
    fprintf(po, "%s", "\n===============================================\n\n\n\n");
    fclose(po);
    //==================================================================================//
    //Save order//
    FILE *pto;
    pto = fopen("saveorder.txt", "a");
    fprintf(pto, "%15s%25s%30s%10s%10f", curtime, cusname, shipadd, phone, totalprice);
    fclose(pto);
}

void sort_by_name(int *i)
{
    char temp[30], tempid[7], tempname[30], tempid1[7];
    int j, haveswap, tempprice, tempsoluong;
    do{
        haveswap = 0;
        for(j = 0; j < *i - 1; j++){
            if(strcmp(pro[j].id, pro[j + 1].id) > 0){
                strcpy(temp, pro[j].name);
                strcpy(pro[j].name, pro[j + 1].name);
                strcpy(pro[j + 1].name, temp);
                
                strcpy(tempid, pro[j].id);
                strcpy(pro[j].id, pro[j + 1].id);
                strcpy(pro[j + 1].id, tempid);
                
                tempprice = pro[j].price;
                pro[j].price = pro[j + 1].price;
                pro[j + 1].price = tempprice;
                //=================================
                strcpy(tempname, temppro[j].name);
                strcpy(temppro[j].name, temppro[j + 1].name);
                strcpy(temppro[j + 1].name, tempname);
                
                strcpy(tempid1, temppro[j].id);
                strcpy(temppro[j].id, temppro[j + 1].id);
                strcpy(temppro[j + 1].id, tempid1);
                
                tempsoluong = temppro[j].price;
                temppro[j].price = temppro[j + 1].price;
                temppro[j + 1].price = tempsoluong;
                haveswap = 1;
            }
        }
    }while(haveswap == 1);
}

void sort_by_price(int *i)
{
    int j, haveswap, tempprice, tempsoluong;
    char temp[30], tempid[7], tempname[30], tempid1[30];
    
    do{
        haveswap = 0;
        for(j = 0; j < *i - 1; j++){
            if(buffer[j].price > buffer[j + 1].price){
                strcpy(temp, buffer[j].name);
                strcpy(buffer[j].name, buffer[j + 1].name);
                strcpy(buffer[j + 1].name, temp);
                
                strcpy(tempid, buffer[j].id);
                strcpy(buffer[j].id, buffer[j + 1].id);
                strcpy(buffer[j + 1].id, tempid);
                
                tempprice = buffer[j].price;
                buffer[j].price = buffer[j + 1].price;
                buffer[j + 1].price = tempprice;
                haveswap = 1;
            }
        }
    }while(haveswap == 1);
    
    printf("Products by ascending price\n");
    printf("        ID                  Product name     Price\n");
    printf("==================================================\n");
    int h;
    for(h = 0; h < *i; h++)
        printf("%10s%30s%10d\n", buffer[h].id, buffer[h].name, buffer[h].price);
    printf("==================================================\n");
}

void search_by_id(int *i)
{
    char timid[15];
    do{
        printf("Enter order ID :");
        scanf("%s%*c", timid);
        if(strlen(timid) != 14){
            printf("Error! Please enter again");
            clear();
        }
    }while(strlen(timid) != 14);
    
    int j, flag = 0;
    for(j = 0; j < 50 && orderid[j].tongchi != 0; j++){
        if(strcmp(timid, orderid[j].masoao) == 0){
            printf("\n\t=================================\n");
            printf("\tOrder information:\n");
            printf("\tName: %s\n", orderid[j].ten);
            printf("\tPhone number: %s\n", orderid[j].sdt);
            printf("\tAddress: %s\n", orderid[j].diachi);
            printf("\tTotal price: %.2f\n", orderid[j].tongchi);
            printf("=================================\n\n");
            flag = 1;
        }
    }
    if(flag == 0)
        printf("\n\nNot found\n\n");
}