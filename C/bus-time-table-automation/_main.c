#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <io.h>

typedef struct routeId_head* routeId_pointer;
typedef struct folderpath_node* folderpath_pointer;
// routeId struct
typedef struct routeId_head {
	routeId_pointer next;
	folderpath_pointer down;
	int routeId;
	char rootpathStr[32];
}routeId_head;
// folderpath struct
typedef struct folderpath_node {
	char filepathStr[47];
	folderpath_pointer next;
}folderpath_node;

/* 
routeId function
*/
//routeId_pointer initRouteIdHeadptr(int routeId);
routeId_pointer initRouteIdHeadptr(int routeId) {
	routeId_pointer routeIdHeadPtr = malloc(sizeof(routeId_head));
	routeIdHeadPtr->next = NULL;
	routeIdHeadPtr->down = NULL;
	routeIdHeadPtr->routeId = routeId;
	return routeIdHeadPtr;
}
//void pushRouteId(routeId_pointer, int);
void pushRouteId(routeId_pointer routeIdList, int routeId) {
	// Stack ������ routeIdList�� �����մϴ�.
	// routeId_head�� �ʱ�ȭ �մϴ�.
	routeId_pointer routeIdPtr = initRouteIdHeadptr(routeId);

	// routeId_head�� 
	routeIdPtr->next = routeIdList->next;
	routeIdList->next = routeIdPtr;
}
//routeId_pointer getRouteIdList(char*);
routeId_pointer getRouteIdList(char* folderPath) {
	FILE* routeIdListTXT;
	routeIdListTXT = fopen(folderPath, "r");
	// routeId_pointer ������ ���� routeIdList�� �ʱ�ȭ �մϴ�.
	routeId_pointer routeIdList = initRouteIdHeadptr(NULL);

	int routeId;
	while (fscanf(routeIdListTXT, "%d", &routeId) != EOF) {
		//printf("%d\n", routeId);
		pushRouteId(routeIdList, routeId);
	}
	return routeIdList;
}
//void readRouteIdList(routeId_pointer routeIdList);
void readRouteIdList(routeId_pointer routeIdList) {
	routeId_pointer tempRouteId = routeIdList->next;
	if (tempRouteId == NULL) {
		printf("Stack UnderFlow");
		return;
	}
	while (tempRouteId != NULL) {
		int routeId = tempRouteId->routeId;
		int rootPath = tempRouteId->rootpathStr;
		printf("%d\t%s\n", routeId, rootPath);
		tempRouteId = tempRouteId->next;
	}
}
//void readAllRouteIdList(routeId_pointer routeIdList);
void readAllRouteIdList(routeId_pointer routeIdList) {
	routeId_pointer tempRouteId = routeIdList->next;
	if (tempRouteId == NULL) {
		printf("Stack UnderFlow");
		return;
	}
	while (tempRouteId != NULL) {
		int routeId = tempRouteId->routeId;
		printf("%d\n", routeId);
		folderpath_pointer tempRouteIdFolder = tempRouteId->down;
		while (tempRouteIdFolder != NULL) {
			char* filePath = tempRouteIdFolder->filepathStr;
			printf("%s\n", filePath);
			tempRouteIdFolder = tempRouteIdFolder->next;
		}
		tempRouteId = tempRouteId->next;
	}
}

/*
folderpath function
*/
//folderpath_pointer initFolderpathPtr();
folderpath_pointer initFolderpathPtr() {
	folderpath_pointer folderpathPtr = malloc(sizeof(folderpath_node));
	folderpathPtr->next = NULL;
	return folderpathPtr;
}
//void pushFolderpath(folderpath_pointer, char*);
void pushFolderpath(routeId_pointer tempRouteId, char* strRouteId) {
	folderpath_pointer tempStringPtr = initFolderpathPtr();
	strcpy(tempStringPtr->filepathStr, strRouteId);
	tempStringPtr->next = tempRouteId->down;
	tempRouteId->down = tempStringPtr;
}
//void readFolderpathList(folderpath_pointer filepathListPointer);
void readFolderpathList(folderpath_pointer filepathListPointer)
{
	folderpath_pointer tempString = filepathListPointer->next;
	if (tempString == NULL) {
		printf("Stack UnderFlow");
		return;
	}
	while (tempString != NULL) {
		char* filepath = tempString->filepathStr;
		printf("%s\n", filepath);
		tempString = tempString->next;
	}
}
//void getFolderpathList(routeId_pointer routeIdList);
void getFolderpathList(routeId_pointer routeIdList) {
	routeId_pointer tempRouteId = routeIdList->next;
	if (tempRouteId == NULL) {
		printf("RouteId�� ����ֽ��ϴ�. ������ �ٽ� Ȯ�����ּ���.");
		exit(0);
	}
	while (tempRouteId != NULL) {
		char inputRootPath[32] = { "DATA/daily-time-table/" };
		char routeIdStirng[10];
		_itoa(tempRouteId->routeId, routeIdStirng, 10);
		//printf("%s\n", routeIdStirng);
		strcat(inputRootPath, routeIdStirng);
		//printf("%s\n", inputRootPath);
		strcpy(tempRouteId->rootpathStr, inputRootPath);
		tempRouteId = tempRouteId->next;
	}
}
//folderpath_pointer listdir(char* filepathStr);
folderpath_pointer listdir(routeId_pointer tempRouteId) {
	char* filepathStr = tempRouteId->rootpathStr;
	folderpath_pointer routeIdPathHead = initFolderpathPtr();

	char* extension = "/*.txt*";
	char* slash = "/";
	char inputFolderPath[33];
	strcpy(inputFolderPath, filepathStr);
	strcat(inputFolderPath, slash);
	char pathFinder[39];
	strcpy(pathFinder, filepathStr);
	strcat(pathFinder, extension);
	//printf("%s", pathFinder);

	/* 	�ڵ���ó: [C] ���� ��� ��������, �ۼ���: ������, 2018.08.16, 	https://eehoeskrap.tistory.com/256 	*/
	struct _finddata_t findData;
	intptr_t handle;
	int fdResult = 1;

	handle = _findfirst(pathFinder, &findData);

	if (handle == -1) {
		return routeIdPathHead;
	}
	while (fdResult != -1) {
		//printf("���ϸ� : %s, ũ��:%d\n", findData.name, findData.size);
		char filePath[47];
		strcpy(filePath, inputFolderPath);
		strcat(filePath, findData.name);
		//printf("%s\n", filePath);
		pushFolderpath(tempRouteId, filePath);
		fdResult = _findnext(handle, &findData);
	}
	_findclose(handle);
	return routeIdPathHead;
}

int main(void) {

	char routeIdListPath[] = { "DATA/route-id-list/routeIdList.txt" };
	routeId_pointer routeIdList = getRouteIdList(routeIdListPath);
	//readRouteIdList(routeIdList);

	getFolderpathList(routeIdList);
	//readRouteIdList(routeIdList);

	routeId_pointer tempRouteId = routeIdList->next;
	while (tempRouteId != NULL) {
		listdir(tempRouteId);
		tempRouteId = tempRouteId->next;
	}
	readAllRouteIdList(routeIdList);

	return 0;
}