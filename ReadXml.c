#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 1000
#define TOTAL_BUS 100

typedef struct listNode* listPointer;
typedef struct {
    int time;
    int busName;
    int station;
    listPointer link;
} listNode;

typedef struct {
    int dataTime;
    int busName;
    int station;
} data;
listNode* head[TOTAL_BUS];
listNode* tail[TOTAL_BUS];

int main() {
    int i, j, k, a;
    int listNum = 0;
    int count = 0;
    int nth = 1;
    FILE* fp;
    data temp;

    //head �����
    //listNode** head = (listNode**)malloc(sizeof(listNode*) * TOTAL_BUS);
    //listNode** tail = (listNode**)malloc(sizeof(listNode*) * TOTAL_BUS);
   
    for (i = 0; i < TOTAL_BUS; i++) {
    
        head[i] = malloc(sizeof(listNode));
    
        head[i]->station = 0; //expectation�� 0���� �ʱ�ȭ
        tail[i] = malloc(sizeof(listNode));
    }

    fp = fopen("A.txt", "r");
    if (fp == NULL) {
        printf("Could not open file");
    }



    while (!feof(fp)) {
        fscanf(fp, "%d %d %d", &temp.dataTime, &temp.busName, &temp.station);

        if (listNum == 0) {/*ù ������*/
            tail[listNum] = head[listNum];
            head[listNum]->busName = temp.busName;
            head[listNum]->station = temp.station;//exp�� ������Ʈ
            head[listNum]->time = listNum + 1;
            /*list�� �߰�*/
            listNode* tempNode = (listNode*)malloc(sizeof(listNode));
            tempNode->station = temp.station;
            tempNode->time = temp.dataTime;
            tempNode->busName = temp.busName;
            tail[listNum]->link = tempNode;
            tail[listNum] = tail[listNum]->link;
            printf("%d\n%d\n%d", head[listNum]->time, head[listNum]->busName, head[listNum]->station);
            printf("\n");
            listNum++;
        }
        else {
            j = 0;
            for (i = 0; i < listNum; i++) {
                if (head[i]->busName != temp.busName) {
                    j++;
                    continue;
                }

                else if (head[i]->busName == temp.busName) {/*���� ��ȣ ����*/
                    if (head[i]->station < temp.station) {/*���� ����Ʈ�� �߰�(exp���� Ŭ ���)*/
                        head[i]->station = temp.station;
                        listNode* tempNode = (listNode*)malloc(sizeof(listNode));
                        tempNode->station = temp.station;
                        tempNode->time = temp.dataTime;
                        tempNode->busName = temp.busName;
                        tail[i]->link = tempNode;
                        tail[i] = tail[i]->link;
                        
                    }
                    else if (head[j]->station == temp.station) {
                        break;/*���� data �Ѿ����*/
                    }

                    else {/*���ο� list ����� �߰�(exp���� ���� ���)*/
                        j++;
                    }
                }
            }
            if (j == listNum) {
               
                
                tail[listNum] = head[listNum];
                head[listNum]->busName = temp.busName;
                head[listNum]->station = temp.station;//exp�� ������Ʈ
                head[listNum]->time = listNum + 1;
                /*list�� �߰�*/
                listNode* tempNode = (listNode*)malloc(sizeof(listNode));
                tempNode->station = temp.station;
                tempNode->time = temp.dataTime;
                tempNode->busName = temp.busName;
                tail[listNum]->link = tempNode;
                tail[listNum] = tail[listNum]->link;
                listNum++;
            }
        }
    }
    head[0] = head[0]->link;
    head[1] = head[1]->link;
    head[2] = head[2]->link;
    head[0] = head[0]->link;
    head[1] = head[1]->link;
    head[2] = head[2]->link;
    head[0] = head[0]->link;
    head[1] = head[1]->link;
    head[2] = head[2]->link;

    printf("%d %d %d\n", head[0]->time, head[0]->busName, head[0]->station);
    printf("%d %d %d\n", head[1]->time, head[1]->busName, head[1]->station);
    printf("%d %d %d\n", head[2]->time, head[2]->busName, head[2]->station);
}


