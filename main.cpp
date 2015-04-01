////这是一个实验ß
////
////  main.cpp
////  C++ Project
////
////  Created by 赵闻一 on 1/9/15.
////  Copyright (c) 2015 David Zhao Studio. All rights reserved.
////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <malloc/malloc.h>
#define LEN sizeof(struct PatriciaTrieNode)
#define LENint sizeof(int)
#define SIZE sizeof(char)
#define LINE 1024
//char *ReadData(FILE *fp, char *buf)
//{
//    return fgets(buf, LINE, fp);
//}
using namespace std;
//struct PatriciaTrieNode {
//    char* key;
//    int No;
//    int node_flag;
//    int childnodenum;
//    int childNodeListSize;
//    PatriciaTrieNode** childNodes;
//    char bitmap[255/(8*SIZE)+1];
//    int* childNodeListp;
//    vector<int> childNodeList;
//};
//
//
////global variable
//int nodeNo=0;
//
////unsigned char *g_bitmap = NULL;
////int g_size = 0;
////int g_base = 0;
//
//
//char* bitmap_init(char* g_bitmap)
//{
//    g_bitmap = (char *)malloc((255/(8*SIZE)+1)*sizeof(char));
//    if(g_bitmap == NULL)
//        return 0;
//    int g_size = 255/(8*SIZE)+1;
//    memset(g_bitmap, 0x0, g_size);
//    return g_bitmap;
//}
//
//
//struct PatriciaTrieNode* initPatriciaNode(int flag)
//{
//    //    struct PatriciaTrieNode* a=new PatriciaTrieNode;
//    struct PatriciaTrieNode* a=(struct PatriciaTrieNode *)malloc(sizeof(struct PatriciaTrieNode));
//    a->key=(char* )"";
//    //a->No=nodeNo++;
//    a->childNodes=(struct PatriciaTrieNode**)malloc(LEN);
//    a->node_flag=flag;
//    //    a->childNodeListp=(int*)malloc(LENint);
//    a->childnodenum=0;
//    bitmap_init(a->bitmap);
//    return a;
//}
//
//int PatriciaTrieNode_free(struct PatriciaTrieNode* node)  ////这个函数不知道需不需要，不会释放二重指针
//{
//    free(node->bitmap);
//    return 0;
//}
//
//
////the operations on the bitmap
//
//int bitmap_get(int index,char* bitmap)  //return 1 means the value in the position index is 1,return 0......is 0,return -1 means the index is out of the range
//{
//    int subscript = index/(SIZE*8) ;
//    int remainder = (index)%(SIZE*8);
//    unsigned char x = (0x1<<remainder);
//    unsigned char res;
//    if( subscript > 255/(8*SIZE))
//        return -1;
//    res=bitmap[subscript] & x;
//    return res > 0 ? 1 : 0;
//}
//
//int bitmap_setTo1(int index, char* bitmap)  //change the value on the position index from 0 to 1
//{
//    int subscript=index/(SIZE*8) ;
//    int remainder = index%(SIZE*8);
//    unsigned char x = (0x1<<remainder);
//    if( subscript >255/(8*SIZE))
//        return 0;
//    bitmap[subscript] |= x;
//    return 1;
//}
//
//int bitmap_setTo0(int index, char* bitmap)  //change the value on the position index from 1 to 0
//{
//    int subscript=index/(SIZE*8) ;
//    int remainder = index%(SIZE*8);
//    unsigned char x = (0x1<<remainder);
//    if( subscript >255/(8*SIZE))
//        return 0;
//    bitmap[subscript] ^= x;
//    return 1;
//}
//
//int bitmap_count1(int index, char* bitmap)
//{
//    int sum=0,i=0;
//    while (i<index) {
//        sum+=bitmap_get(i, bitmap);
//        i++;
//    }
//    return sum;
//}
//
////int bitmap_data(int index)
////{
////    return (index + g_base);
////}
//
//int bitmap_free(char* bitmap)
//{
//    free(bitmap);
//    return 0;
//}
//
//
//
//int insertNodeToNode(PatriciaTrieNode node,PatriciaTrieNode* nodeToInsert,int index)
//{
//    if(node.childnodenum+1>node.childNodeListSize)
//        node.childNodes=(PatriciaTrieNode**)realloc(node.childNodes, node.childNodeListSize + 1);
//    int i=0;
//    for(i = node.childnodenum; i >  index; )
//    {
//        node.childNodes[i] = node.childNodes[i - 1];
//        i--;
//    }
//    node.childNodes[index] = nodeToInsert;
//    node.childnodenum++;
//    return 1;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
////字符串相关处理
////cut a string inside the string
//char * strcutmid(char *src, int startpos  ,int endpos)
//{
//    int n=endpos-startpos;
//    int m=startpos;
//    int len = (int)strlen(src);
//    char* dst=(char*)malloc(n+1);
//    if (dst==NULL) {
//        printf("malloc error!");
//        return NULL;
//    }
//    char *p = src;
//    char *q = dst;
//    if(n>len)
//        n = len-m;
//    if(m<0)
//        m=0;
//    if(m>len)
//        return NULL;
//    p += m;
//    while(n--)
//        *(q++) = *(p++);
//    *(q++)='\0';
//    return dst;
//}
////cut a string after one pos
//char* strcutright(char* src,int startpos)
//{
//    return strcutmid(src, startpos, (int)strlen(src));
//}
//char *strcopy(char *src)
//{
//    char* dst;
//    dst=strcutright(src, 0);
//    return dst;
//}
////longest prefix of 2 string
//char* longestprefix(char* str1,char* str2)
//{
//    char* p=str1;
//    char* q=str2;
//    char* buffer;
//    int i=0;
//    while (*p++==*q++) {
//        i++;
//    }
//    buffer=strcutmid(str1, 0, i);
//    return buffer;
//}
//
//
//
//
//
//PatriciaTrieNode** findFinalNode(PatriciaTrieNode** childNodes)
//{
//    PatriciaTrieNode** b=childNodes;
//    while (*b!=NULL) {
//        b++;
//    }
//    return b;
//}
//
//
//
//int** findFinalNodeNum(int** childNodes)
//{
//    int** b=childNodes;
//    while (*b!=NULL) {
//        b++;
//    }
//    return b;
//}
//int** findFirstNodeNum(int** childNodes)
//{
//    int** b=childNodes;
//    while (*b==NULL) {
//        b++;
//    }
//    return b;
//}
//void addChildNode(int No,PatriciaTrieNode* node)
//{
////    int *dynamic;
////    int *ptr;
////    ptr=(int*)realloc(dynamic, (node->childnodenum+1)*LENint);
////    if (ptr!=NULL) {
////        dynamic=ptr;
////    }
////    else{
////        perror("Error:");
////        exit(EXIT_FAILURE);
////    }
////    dynamic[node->childnodenum++]=No;
////    
////    
////    
////    
////    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    node->childNodeList.push_back(No);
//    node->childnodenum=(int)node->childNodeList.size();
//}
//
//
//void printChildList(PatriciaTrieNode* node,FILE* fp)
//{
//    int a=node->childnodenum;
//    for(int i=0;i<a;i++) {
//        printf("%d ",node->childNodeList[i]);
//        fprintf(fp, "%d ",node->childNodeList[i]);
//    }
//    printf("\n");
//    fprintf(fp, "\n");
//}
//void printPatricianode(PatriciaTrieNode* a)
//{
//    FILE* fp=fopen("/Users/zhaowenichi/Downloads/text.txt","a");
//    if (a->key!=0) {
//        printf("Node No.:%d\n",a->No);
//        fprintf(fp, "Node No.:%d\n",a->No);
//        printf("Key is:%s\n",a->key);
//        fprintf(fp, "Key is:%s\n",a->key);
//        printf("%d child node(s):",a->childnodenum);
//        fprintf(fp, "%d child node(s):",a->childnodenum);
//        printChildList(a,fp);
//        if (a->node_flag==1)
//        {
//            printf("Kind: Root Node\n");
//            fprintf(fp, "Kind: Root Node\n");
//        }
//        else if (a->node_flag==2){
//            printf("Kind: Inner Node\n");
//            fprintf(fp,"Kind: Inner Node\n");
//        }
//        else if(a->node_flag==3){
//            printf("Kind: Leaf Node\n");
//            fprintf(fp, "Kind: Leaf Node\n");
//        }
//        else{
//            printf("Node out of tree\n");
//            fprintf(fp, "Node out of tree\n");
//        }
//        int i=0;
//        printf("\n\n");
//        fprintf(fp, "\n\n");
//        fclose(fp);
//        while (*(a->childNodes+i)!=NULL) {
//            printPatricianode(*(a->childNodes+i));
//            //a->childNodes++;
//            i++;
//        }
//    }
//}
//PatriciaTrieNode* initialPatriciaNode(int flag)
//{
//    PatriciaTrieNode* a=new PatriciaTrieNode;
//    a->key=(char* )"";
//    a->No=nodeNo++;
//    a->childNodes=(PatriciaTrieNode**)malloc(LEN);
//    a->node_flag=flag;
////    a->childNodeListp=(int*)malloc(LENint);
//    a->childnodenum=0;
//    return a;
//}
//
//void insertstring(PatriciaTrieNode* startnode,int start_pos,char* string)
//{
//    if (start_pos >= strlen(string))
//        return;
//    int i=0;
//    while(*(startnode->childNodes+i)){
//        PatriciaTrieNode* currnode=*(startnode->childNodes+i);
//        char* str_node=strcopy(currnode->key);
//        char* str_pattern=strcutmid(string, start_pos, (int)strlen(string));
//        char* substr=longestprefix(str_node, str_pattern);
//        if(str_node==NULL||strcmp(str_node,"")==0)
//        {
//            i++;
//            continue;
//        }
//        if(substr==NULL||strcmp(substr,"")==0)
//        {
//            i++;
//            continue;
//        }
//        else if(strcmp(substr, str_pattern)==0&&strcmp(substr, str_node)==0)
//            return;
//        else if(strcmp(substr, str_pattern)==0)
//        {
//            currnode->node_flag=2;
//            currnode->key=strcopy(str_pattern);
//            PatriciaTrieNode* newnode1=initialPatriciaNode(2);
//            PatriciaTrieNode* newnode2=initialPatriciaNode(3);
//            newnode1->key=strcutright(str_node, (int)strlen(str_pattern));
//            newnode1->childNodes=currnode->childNodes;
//            newnode1->childnodenum=currnode->childnodenum;
//            newnode1->childNodeList=currnode->childNodeList;
//            currnode->childNodeList.clear();
//            currnode->childNodes=(PatriciaTrieNode**)malloc(LEN);
//            currnode->childnodenum=0;
//            PatriciaTrieNode** newnodes=findFinalNode(currnode->childNodes);
//            *newnodes=newnode2;
//            *(newnodes+1)=newnode1;
//            addChildNode(newnode1->No, currnode);
//            addChildNode(newnode2->No, currnode);
//            return;
//        }
//        else if(strcmp(substr, str_node)==0)
//        {
//            int new_start_pos = start_pos + (int)strlen(substr);
//            if(currnode->node_flag==2)
//                insertstring(currnode,new_start_pos,string);
//            else
//            {
//                currnode->node_flag=2;
//                currnode->key=strcopy(substr);
//                PatriciaTrieNode** newnodes=findFinalNode(currnode->childNodes);
//                *newnodes=initialPatriciaNode(3);
//                *(newnodes+1)=initialPatriciaNode(3);
//                PatriciaTrieNode* newnode1=*(newnodes);
//                PatriciaTrieNode* newnode2=*(newnodes+1);
//                newnode2->key=strcutright(str_pattern, (int)strlen(substr));
//                addChildNode(newnode1->No, currnode);
//                addChildNode(newnode2->No, currnode);
//            }
//            return;
//        }
//        else
//        {
//            currnode->node_flag=2;
//            int biaoji=0;
//            if(currnode->childnodenum==0)
//            {biaoji=3;}
//            else
//            {biaoji=2;}
//            
//            PatriciaTrieNode* newnode1=initialPatriciaNode(biaoji);
//            PatriciaTrieNode* newnode2=initialPatriciaNode(3);
//            newnode1->key=strcutright(str_node, (int)strlen(substr));
//            newnode1->childNodes=currnode->childNodes;
//            newnode1->childnodenum=currnode->childnodenum;
//            newnode1->childNodeList=currnode->childNodeList;
//            newnode2->key=strcutright(str_pattern, (int)strlen(substr));
//            currnode->childNodeList.clear();
//            currnode->childNodes=(PatriciaTrieNode**)malloc(LEN);
//            currnode->childnodenum=0;
//            currnode->key=strcopy(substr);
//            PatriciaTrieNode** newnodes=findFinalNode(currnode->childNodes);
//            *newnodes=newnode2;
//            *(newnodes+1)=newnode1;
//            addChildNode(newnode1->No, currnode);
//            addChildNode(newnode2->No, currnode);
//            return;
//        }
//    }
//    PatriciaTrieNode** newnodes=findFinalNode(startnode->childNodes);
//    *newnodes=initialPatriciaNode(3);
//    PatriciaTrieNode* newnode1=*newnodes;
//    newnode1->key=strcutright(string, start_pos);
//    addChildNode(newnode1->No, startnode);
//    return;
//}

int main()
{
//    PatriciaTrieNode *root=initialPatriciaNode(1);
//    FILE *fp;
//    char *buf, *p;
//    if ((fp=fopen("/Users/zhaowenichi/Downloads/toStudent/text1.txt", "r"))==NULL) {
//        printf("open file error!!\n");
//        return 0;
//    }
//    
//    buf=(char*)malloc(LINE*sizeof(char));
//    
//    while(1) {
//        p=ReadData(fp, buf);
//        if(!p)
//        break;
//        insertstring(root, 0,buf);
//    }
//    vector<PatriciaTrieNode*> nodelist;
//    nodelist.push_back(root);
//    nodelist.push_back(initialPatriciaNode(3));
//    int total_element=LENint;
//    int *dynamic;
//    int *ptr;
//    int current_element=0;
//    int a=1000;
//    do {
//        
//        ptr=(int*)realloc(dynamic, (current_element+1)*LENint);
//        if (ptr!=NULL) {
//            dynamic=ptr;
//        }
//        else
//            exit(EXIT_FAILURE);
//        dynamic[current_element++]=a;
//        
//    } while (a-->=0);
//
//    a=100;
//    current_element=0;
//    while (a--) {
//        printf("%d ",dynamic[current_element++]);
//    }
//    insertstring(root, 0, (char*)"classiques.uqac.ca/");
//    insertstring(root, 0, (char*)"www.chemicalsindiacompany.com/");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/Faure_Elie/histoire_art_antique/art_antique.html");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/focillon_henri/Vie_des_formes/Vie_des_formes.html");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/Diderot_denis/entretien_philo_marechale/entretien_marechale.html");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/Diderot_denis/d_Alembert/d_alembert_1_entretien/entretien.html");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/Diderot_denis/d_Alembert/d_alembert_1_entretien/entretien.html");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/Diderot_denis/lettre_commerce_livre/lettre_com_livre.html");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/Diderot_denis/d_Alembert/d_alembert_2_reve/reve_d_alembert.html");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/Diderot_denis/d_Alembert/d_alembert_3_entretien_fin/entretien_fin.html");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/Boukharine_N/boukharine.html");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/Diderot_denis/voyage_bougainville/voyage_bougainville.html");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/gautier_theophile/gautier_theophile.html");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/lafargue_paul/determinisme_de_marx/determinisme_de_marx.html");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/lafargue_paul/La_religion_du_capital/La_religion_du_capital.html");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/keynes_john_maynard/keynes_jm.html");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/Alain/Alain.html");
//    insertstring(root, 0, (char*)"classiques.uqac.ca/classiques/bergson_henri/bergson_henri.html");

    //printPatricianode(root);
////    cout<<LEN;
//    char* bitmap;
//    bitmap=bitmap_init(bitmap);
//    bitmap_setTo1('a', bitmap);
//    
    cout<<strcmp("chaosach", "chaosac");
    return 0;
}