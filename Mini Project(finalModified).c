#include <stdio.h>
#include <string.h>

//function declaration //declaration of pointer
void getDiscount(char*, int*, float*, char[5], char [10]);
float getTicket(char *[15], char *[15], int* ,char*, char*, float, char [20], char [30]);
float getRoomPrice(int*, int*, float, char [30]);
float getTotalTicketPrice(float, int);
float getTotalAccommodationPrice(float, int, int);
void getTotalPayment(float *, float *, float *, float *, float *, float *);
void getUpdate(char*, int*, float*, char[5], char[10], int, int, int, char[30], char[15], char[15], int, char, int, float, char[20], char[30], float *, float *, float *, float *, float *, int);
void getOutput(char [][20], char [][12], char [][15], char [][30], int, char[15], char[15], int, char[20], char [30], char[30], int, char[5], char [10], float, float, float, float);

int main()
{   //variable declaration
    char membership, destination, returnDate[15], departDate[15], Mmem[5], MCate[10], MDest[20], Mtrans[30], Maccom[30];
    int i, category, transportation, accommodation, room, duration, numOfPerson, update;
    float discount, ticket, roomPrice, tTicketPrice, tAccomPrice, tBfrDisc, tAftDisc, tPayment;

    printf("----------WELCOME TO CUTI-CUTI MALAYSIA TRAVEL AGENCY!!----------");
    printf("\nEnter number of person: ");
    scanf(" %d", &numOfPerson); //numOfPerson = array size

    char name[numOfPerson][20], phoneNum[numOfPerson][12], ICNum[numOfPerson][15], email[numOfPerson][30];

    FILE *fpointer;//file declaration

    fpointer = fopen("travel.txt","w");//open write file

    if(fpointer == NULL)
        {
        printf("Oppss... file opening error");
    }

    //store information in array by looping
    for(i=0; i<numOfPerson; i++)
        {
    fflush(stdin);
    printf("Enter name %d: ", i+1);
    gets(name[i]);
    printf("Enter phone number: ");
    scanf(" %s", &phoneNum[i]);
    printf("Enter IC number: ");
    scanf(" %s", &ICNum[i]);
    printf("Enter email address: ");
    scanf(" %s", &email[i]);

    fprintf(fpointer,"%s\t%s\t%s\t%s\n",name[i],phoneNum[i],ICNum[i],email[i]);//write in file
    }

    fclose(fpointer);//close write file

    fpointer = fopen("travel.txt","r"); //open read file

    if(fpointer == NULL)
        {
        printf("Oppss... file opening error");
    }

    printf("Name\tPhone Number\tIC Number\tEmail Address\n");
    for(i=0;i<numOfPerson;i++)
        {
        fscanf(fpointer,"%s\t%s\t%s\t%s\n",name[i], &phoneNum[i], &ICNum[i], &email[i]);
        printf("%s\t%s\t%s\t%s\n",name[i],phoneNum[i],ICNum[i],email[i]);
    }
    fclose(fpointer);//close read file

    //calling function
    getDiscount(&membership, &category, &discount, Mmem, MCate);
    ticket = getTicket(&departDate, &returnDate, &duration, &destination, &transportation, ticket,MDest, Mtrans);
    roomPrice = getRoomPrice(&accommodation, &room, roomPrice, Maccom);
    tTicketPrice = getTotalTicketPrice(ticket, numOfPerson);
    tAccomPrice = getTotalAccommodationPrice(roomPrice, room, duration);
    getTotalPayment(&tBfrDisc, &tTicketPrice, &tAccomPrice, &tAftDisc, &discount, &tPayment);
    getUpdate(&membership, &category, &discount, Mmem, MCate, accommodation, room, roomPrice, Maccom, departDate, returnDate, duration, destination, transportation, ticket, MDest, Mtrans, &tBfrDisc, &tTicketPrice, &tAccomPrice, &tAftDisc, &tPayment, numOfPerson);
    getOutput(name, phoneNum, ICNum, email, numOfPerson, departDate, returnDate, duration, MDest, Mtrans, Maccom, room, Mmem, MCate, discount, tBfrDisc, tAftDisc, tPayment);

    return 0;
}

//function definition

void getDiscount(char *member, int *cate, float *disc, char mem[5], char MsgCate[10]){

    printf("Do you have a membership [Y=Yes N=No]: ");
    scanf(" %c", member);

    //get discount for membership using Nested if-else Statement
    if (*member == 'Y'|| *member == 'y'){
        strcpy(mem, "YES");
        printf("Enter category [Press 1 for Gold membership and any integer for Silver membership]: ");
        scanf(" %d", cate);

        if (*cate == 1){
            strcpy(MsgCate, "GOLD");
            *disc = 0.08;
        }
        else {
            strcpy(MsgCate, "SILVER");
            *disc = 0.05;
        }
    }
    else{
        strcpy(mem, "NO");
        strcpy(MsgCate, "NULL");
        *disc = 0.0;
    }

}float getTicket(char *Depart[15], char *Return[15], int *Dura, char *dest, char *trans, float Ticket,char Mdest[20], char Mtrans[30]){
    printf("Enter Departure Date[DD/MM/YYYY]:");
    scanf(" %s", Depart);
    printf("Enter Return Date[DD/MM/YYYY]:");
    scanf(" %s", Return);
    printf("Enter Duration[day]:");
    scanf(" %d", Dura);

    //display travel package provided to users
    printf("--------------------TRAVEL PACKAGE--------------------");
    printf("\nDestination    [A] : George Town");
    printf("\nTransportation [1] - Flight (RM 156.00)");
    printf("\n               [2] - Bus (RM 71.60)");
    printf("\n               [3] - Train + Ferry (RM 171.20)");
    printf("\n\nDestination    [B] : Pulau Tioman");
    printf("\nTransportation [1] - Bus + Ferry (RM 100.00)");
    printf("\n\nDestination    [C] : Perhentian Islands");
    printf("\nTransportation [1] - Bus + Ferry (RM 140.00)");
    printf("\n               [2] - Flight + Bus + Ferry (RM 358.00)");
    printf("\n\nDestination    [D] : Kota Kinabalu");
    printf("\nTransportation [1] - Flight (RM 388.00)");
    printf("\n               [2] - Train + Flight (RM 324.40)");
    printf("\n\nDestination    [E] : Teluk Cempedak");
    printf("\nTransportation [1] - Train + Flight (RM 380.00)");
    printf("\n               [2] - Bus (RM 134.00)");
    printf("\n------------------------------------------------------");

    printf("\nEnter destination: ");
    scanf(" %c", dest);
    printf("\nEnter transportation: ");
    scanf(" %d", trans);
    //nested if-else statement //get ticket price of transportation
    if (*dest == 'A'|| *dest == 'a'){
        strcpy(Mdest, "George Town");
        if (*trans == 1){
        strcpy(Mtrans, "Flight");
            Ticket = 156.00;
        }
        else if (*trans == 2){
        strcpy(Mtrans, "Bus");
            Ticket = 71.60;
        }
        else{
        strcpy(Mtrans, "Train + Ferry");
            Ticket = 171.20;
        }
    }
    else if (*dest == 'B'|| *dest == 'b'){
        strcpy(Mdest, "Pulau Tioman");
        strcpy(Mtrans, "Bus + Ferry");
        Ticket = 100.00;
    }
    else if (*dest == 'C'|| *dest == 'c'){
        strcpy(Mdest, "Perhentian Islands");
        if (*trans == 1){
            strcpy(Mtrans, "Bus + Ferry");
            Ticket = 140.00;
        }
        else{
            strcpy(Mtrans, "Flight + Bus + Ferry");
            Ticket = 358.00;
        }
    }
    else if (*dest == 'D'|| *dest == 'd'){
        strcpy(Mdest, "Kota Kinabalu");
        if (*trans == 1){
            strcpy(Mtrans, "Flight");
            Ticket = 388.00;
        }
        else {
            strcpy(Mtrans, "Train + Flight");
            Ticket = 324.40;
        }
    }
    else if (*dest == 'E'|| *dest == 'e'){
        strcpy(Mdest, "Teluk Cempedak");
        if (*trans == 1){
            strcpy(Mtrans, "Train + Flight");
            Ticket = 380.00;
        }
        else {
            strcpy(Mtrans, "Bus");
            Ticket = 134.00;
        }
    }
    else {
        strcpy(Mdest, "-");
        printf("Invalid input");
    }
    return Ticket;
}

float getRoomPrice(int *accom, int *numOfRoom, float rPrice, char Maccom[30]){
    //display accommodation provided
    printf("--------------------ACCOMMODATION --------------------");
    printf("\nOption [1] : Hotel (1-2 pax)");
    printf("\nRoom Price per night : RM130.00");
    printf("\n\nOption [2] : Hotel (3-4 pax)");
    printf("\nRoom Price per night : RM180.00");
    printf("\n\nOption [3] : Homestay (5-8 pax)");
    printf("\nRoom Price per night : RM450.00");
    printf("\n\nOption [4] : Resort (2-4 pax)");
    printf("\nRoom Price per night : RM460.00");
    printf("\n------------------------------------------------------");
    printf("\nEnter accommodation: ");
    scanf(" %d", accom);
    printf("\nEnter number of room: ");
    scanf(" %d", numOfRoom);
    //get accommodation and roomPrice using if-else statement
    if (*accom == 1){
        strcpy(Maccom, "Hotel (1-2 pax)");
        rPrice = 130.00;
    }
    else if(*accom == 2){
        strcpy(Maccom, "Hotel (3-4 pax)");
        rPrice = 180.00;
    }
    else if(*accom == 3){
        strcpy(Maccom, "Homestay (5-8 pax)");
        rPrice = 450.00;
    }
    else {
        strcpy(Maccom, "Resort (2-4 pax)");
        rPrice = 460.00;
    }
    return rPrice;
}

float getTotalTicketPrice(float tic, int person){
    float totalTicket;

    totalTicket = tic * person;//calculate total price ticket

    return totalTicket;
}

float getTotalAccommodationPrice(float rPrice, int room, int Duration){
    float totalAccom;

    totalAccom = rPrice * room * Duration;//calculate total price for accommodation

    return totalAccom;
}

void getTotalPayment(float *totalBfrDisc, float *totalTic, float *tAccomP, float *totalAftDisc, float *Disc, float *totalPay){
//calculate total price before discount,after discount and total amount
    *totalBfrDisc = *totalTic + *tAccomP;
    *totalAftDisc = *totalBfrDisc * *Disc;
    *totalPay = *totalBfrDisc - *totalAftDisc;
}

//function for update
void getUpdate(char *memb, int *ctgr, float *disct, char MsgMem[5], char MsgCate[10], int Accom, int roomNum, int roomP, char MAccom[], char DepartDate[15], char ReturnDate[15], int DuratioN, char Dest, int transport, float Tic, char MsgDest[20], char MsgTrans[30], float *tB4Disc, float *tTicPrice, float *tAccPrice, float *totalADisc, float *ttlPay, int personNo){
    char ans;
    int choice;
    printf("\nDo you want to update the information[Y=Yes N=No]?");
    scanf(" %c", &ans);//decision for update
    if(ans == 'Y'|| ans =='y') //if statement
        {
        do{
            printf("\nWhat element do you wish to update?");
            //display information provided that can be updated by users
            printf("\n1. Membership");
            printf("\n2. Accommodation");
            printf("\n3. Destination & Transportation");
            printf("\n4. Exit");

            printf("\nPlease select your choice (1-4): ");
            scanf("%d",&choice);
            switch (choice)
            {
                case 1:
                    getDiscount(memb, ctgr, disct, MsgMem, MsgCate);
                    getTotalPayment(tB4Disc, tTicPrice, tAccPrice, totalADisc, disct, ttlPay);
                    break;

                case 2:
                    roomP = getRoomPrice(&Accom, &roomNum, roomP, MAccom);
                    *tAccPrice = getTotalAccommodationPrice(roomP, roomNum, DuratioN);
                    getTotalPayment(tB4Disc, tTicPrice, tAccPrice, totalADisc, disct, ttlPay);
                    break;

                case 3:
                    Tic = getTicket(&DepartDate, &ReturnDate, &DuratioN, &Dest, &transport, Tic, MsgDest, MsgTrans);
                    *tTicPrice = getTotalTicketPrice(Tic, personNo);
                    *tAccPrice = getTotalAccommodationPrice(roomP, roomNum, DuratioN);
                    getTotalPayment(tB4Disc, tTicPrice, tAccPrice, totalADisc, disct, ttlPay);
                    break;

            }
        }while (choice != 4);//loop for update
    }
}

//function print output
void getOutput(char Name[][20], char phone[][12], char ICNo[][15], char emailAdd[][30], int num, char depdate[15], char retdate[15], int dur, char mdest[20], char mtrans[30], char maccom[30], int Room, char msgMember[5], char msgCate[10], float discnt, float TBfrD, float TAftD, float TPay){
    int j;
    printf("Name\tPhone Number\tIC Number\t\tEmail Address");
    for (j=0; j<num; j++){
        printf("\n%s\t%s\t%s\t\t%s", Name[j], phone[j], ICNo[j], emailAdd[j]); //display output using array
    }
    printf("\n\n Departure Date: %s", depdate);
    printf("\n\n Return Date: %s", retdate);
    printf("\n\n Duration(day): %d", dur);
    printf("\n\n Destination: %s", mdest);
    printf("\n\n Transportation: %s", mtrans);
    printf("\n\n Accommodation: %s", maccom);
    printf("\n\n Number of Room: %d", Room);
    printf("\n\n Membership: %s", msgMember);
    printf("\n\n Category: %s", msgCate);
    printf("\n\n Discount: %.2f", discnt);
    printf("\n\n Total Before Discount: RM%.2f", TBfrD);
    printf("\n\n Total After Discount: RM%.2f", TAftD);
    printf("\n\n Total Payment: RM%.2f", TPay);
}
