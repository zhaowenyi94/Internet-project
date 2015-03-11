//这是一个实验ß
//
//  main.cpp
//  C++ Project
//
//  Created by 赵闻一 on 1/9/15.
//  Copyright (c) 2015 David Zhao Studio. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc/malloc.h>
#define LEN sizeof(struct PatriciaTrieNode)
#define LENint sizeof(int)
#define SIZE sizeof(char)
#define LINE 1024
char *ReadData(FILE *fp, char *buf)
{
    return fgets(buf, LINE, fp);
}

struct PatriciaTrieNode
{
    char* key;
    //int No;
    int node_flag;
    int childnodenum;
    struct PatriciaTrieNode** childNodes;
    struct PatriciaTrieNode* parentNode;
    char bitmap[255/(8*SIZE)+1];
    //int* childNodeListp;
    int port;
};


//global variable
//int nodeNo=0;


//unsigned char *g_bitmap = NULL;
//int g_size = 0;
//int g_base = 0;


//char* bitmap_init(char* g_bitmap)
//{
//    g_bitmap = (char *)malloc((255/(8*SIZE)+1)*sizeof(char));
//    if(g_bitmap == NULL)
//        return 0;
//    int g_size = 255/(8*SIZE)+1;
//    memset(g_bitmap, 0x0, g_size);
//    return g_bitmap;
//}


struct PatriciaTrieNode* initPatriciaNode(int flag,int port)
{
    //    struct PatriciaTrieNode* a=new PatriciaTrieNode;
    struct PatriciaTrieNode* a=(struct PatriciaTrieNode *)malloc(sizeof(struct PatriciaTrieNode));
    a->key=(char* )"";
    //a->No=nodeNo++;
    a->childNodes=(struct PatriciaTrieNode**)malloc(LEN);
    a->node_flag=flag;
    //    a->childNodeListp=(int*)malloc(LENint);
    a->childnodenum=0;
    //    bitmap_init(a->bitmap);
    if(a->bitmap== NULL)
        return 0;
    int a_size = 255/(8*SIZE)+1;
    memset(a->bitmap, 0x0, a_size);
    a->port=port;
    return a;
}

char* strcutmid(char* src,int startpos,int endpos)
{
    int n=endpos-startpos;
    int m=startpos;
    int len = (int)strlen(src);
    char* dst=(char*)malloc(n+1);
    if (dst==NULL)
    {
        printf("malloc error!");
        return NULL;
    }
    char *p = src;
    char *q = dst;
    if(n>len)
        n = len-m;
    if(m<0)
        m=0;
    if(m>len)
        return NULL;
    p += m;
    while(n--)
        *(q++) = *(p++);
    *(q++)='\0';
    return dst;
}
//cut a string after one pos
char* strcutright(char* src,int startpos)
{
    return strcutmid(src, startpos, (int)strlen(src));
}


int PatriciaTrieNode_free(struct PatriciaTrieNode* node)  ////这个函数不知道需不需要，不会释放二重指针
{
    free(node->bitmap);
    return 0;
}


//the operations on the bitmap

int bitmap_setTo1(int index, char* bitmap)  //change the value on the position index from 0 to 1
{
    
    int subscript=index/(SIZE*8) ;
    int remainder = index%(SIZE*8);
    unsigned char x = (0x1<<remainder);
    if( subscript >255/(8*SIZE))
        return 0;
    bitmap[subscript] |= x;
    return 1;
}

int bitmap_setTo0(int index, char* bitmap)  //change the value on the position index from 1 to 0
{
    int subscript=index/(SIZE*8) ;
    int remainder = index%(SIZE*8);
    unsigned char x = (0x1<<remainder);
    if( subscript >255/(8*SIZE))
        return 0;
    bitmap[subscript] ^= x;
    return 1;
}


int bitmap_get(int index,char* bitmap)  //return 1 means the value in the position index is 1,return 0......is 0,return -1 means the index is out of the range
{
    //    int a=index;
    int subscript = index/(SIZE*8) ;
    int remainder = (index)%(SIZE*8);
    unsigned char x = (0x1<<remainder);
    unsigned char res;
    if( subscript > 255/(8*SIZE))
        return -1;
    res=bitmap[subscript] & x;
    return res > 0 ? 1 : 0;
}

void printBitmap(char*bitmap)
{
    int i;
    for(i=0;i<255;i++)
    {
        int a=bitmap_get(i, bitmap);
        printf("%d ",a);
    }
    printf("\n");
}

int bitmap_frontcount(int index,char* bitmap)
{
    int sum=0;
    for(int i=0;i<index;i++)
    {
        sum+=bitmap_get(i, bitmap);
        //        if(bitmap_get(i, bitmap)==1)
        //            printf("%d\n", i);
    }
    //    printf("-------------------------------");
    return sum;
}

struct PatriciaTrieNode* getNode(struct PatriciaTrieNode* node)
{
    return node;
}

struct PatriciaTrieNode* search(char* string,struct PatriciaTrieNode* node)
{
    struct PatriciaTrieNode* currnode=node;
    while(strcmp(currnode->key,"")!=0||*currnode->childNodes)
    {
        if(strcmp(currnode->key,string)<0)
        {
            char* cut=strcutmid(string, 0, (int)strlen(currnode->key));
            if(strcmp(cut,currnode->key)==0)
            {
                char* remaining=strcutright(string, (int)strlen(currnode->key));
                string="";
                string=remaining;
                int index=remaining[0];
                if(bitmap_get(index, currnode->bitmap)==1)
                {
                    int childnumber=bitmap_frontcount(index,currnode->bitmap);
                    currnode=*currnode->childNodes+childnumber;
                }
                else
                    return currnode;
            }
            else
                return currnode;
        }
        else
            return currnode;
    }
    if(!*currnode->childNodes)
        return currnode;
    else
        return NULL;
    
}


int insert(char* string,struct PatriciaTrieNode* node,int port)
{
    int sum=0;
    struct PatriciaTrieNode* testNode=search(string, node);
    struct PatriciaTrieNode* currnode=testNode;
    if(currnode->parentNode==NULL)
    {
        struct PatriciaTrieNode* newnode=initPatriciaNode(3, port);
        *currnode->childNodes=newnode;
        newnode->key=string;
        bitmap_setTo1(string[0], currnode->bitmap);
        newnode->parentNode=currnode;
        currnode->childnodenum+=1;
    }
    else
    {
        while(currnode->parentNode)
        {
            sum+=strlen(currnode->parentNode->key);
            currnode=currnode->parentNode;
        }
        char* remaining=strcutright(string,sum);
        char* testNodeKey=testNode->key;
        if(strlen(remaining)>=strlen(testNodeKey))
        {
            int i=0;
            for(i=0;i<strlen(testNodeKey);i++)
            {
                if(testNodeKey[i]!=remaining[i])
                    break;
                else
                    continue;
            }
            if(i==strlen(testNodeKey))
            {
                char* newNodeKey=strcutright(remaining,(int)strlen(testNodeKey));
                struct PatriciaTrieNode* newNode=initPatriciaNode(3,port);
                bitmap_setTo1(newNodeKey[0], testNode->bitmap);
                testNode->childnodenum+=1;
                int x=bitmap_frontcount(newNodeKey[0], testNode->bitmap);
                int childnum;
                for(childnum=testNode->childnodenum-1;childnum>=x;childnum--)
                {
                    *(testNode->childNodes+childnum)=*(testNode->childNodes+childnum-1);
                }
                *(testNode->childNodes+x-1)=newNode;
                *testNode->childNodes=newNode;
                newNode->parentNode=testNode;
                newNode->key=newNodeKey;
            }
            else if(i==0)
            {
                testNode=testNode->parentNode;
                struct PatriciaTrieNode* newNode=initPatriciaNode(3,port);
                //            *testNode->childNodes=newNode;
                newNode->parentNode=testNode;
                testNode->childnodenum+=1;
                bitmap_setTo1(remaining[0], testNode->bitmap);
                newNode->key=remaining;
                testNode->childnodenum+=1;
                int x=bitmap_frontcount(remaining[0], testNode->bitmap);
                int childnum;
                for(childnum=testNode->childnodenum-1;childnum>=x;childnum--)
                {
                    *(testNode->childNodes+childnum)=*(testNode->childNodes+childnum-1);
                }
                *(testNode->childNodes+x-1)=newNode;
            }
            else
            {
                char* newNodeKey1=strcutmid(remaining,0,i);
                char* oldNodeKey=strcutright(testNodeKey,i);
                char* newNodeKey2=strcutright(remaining, i);
                struct PatriciaTrieNode* newNode1=initPatriciaNode(2,0);
                struct PatriciaTrieNode* newNode2=initPatriciaNode(3,port);
                //*testNode->childNodes=newNode;
                testNode->key="";
                testNode->key=oldNodeKey;
                newNode1->childnodenum+=1;
                bitmap_setTo1(oldNodeKey[0], newNode1->bitmap);
                newNode1->key=newNodeKey1;
                *newNode1->childNodes=testNode;
                int index=bitmap_frontcount(newNodeKey1[0], testNode->parentNode->bitmap);
                *(testNode->parentNode->childNodes+index)=newNode1;
                newNode1->parentNode=testNode->parentNode;
                testNode->parentNode=newNode1;
                int x=bitmap_frontcount(newNodeKey2[0],newNode1->bitmap);
                int childnum;
                for(childnum=newNode1->childnodenum;childnum>0;childnum--)
                {
                    *(newNode1->childNodes+childnum)=*(newNode1->childNodes+childnum-1);
                }
                *(newNode1->childNodes+x)=newNode2;
                newNode1->childnodenum+=1;
                bitmap_setTo1(newNodeKey2[0], newNode1->bitmap);
                newNode2->parentNode=newNode1;
                newNode2->key=newNodeKey2;
            }
        }
        else
        {
            int i;
            for(i=0;i<strlen(remaining);i++)
            {
                if(testNodeKey[i]!=remaining[i])
                    break;
            }
            if(i==strlen(remaining))
            {
                char* newNodeKey=strcutright(testNodeKey,(int)strlen(remaining));
                struct PatriciaTrieNode* newNode=initPatriciaNode(3,testNode->port);
                testNode->port=port;
                newNode->parentNode=testNode;
                testNode->childnodenum+=1;
                bitmap_setTo1(newNodeKey[0], testNode->bitmap);
                newNode->key=newNodeKey;
                testNode->key="";
                testNode->key=remaining;
                int x=bitmap_frontcount(newNodeKey[0], testNode->bitmap);
                int childnum;
                if(x>0)
                {
                    for(childnum=testNode->childnodenum-1;childnum>=x;childnum--)
                    {
                        *(testNode->childNodes+childnum)=*(testNode->childNodes+childnum-1);
                    }
                    *(testNode->childNodes+x-1)=newNode;
                }
                else
                {
                    *testNode->childNodes=newNode;
                }
                
            }
            else if(i==1)
            {
                testNode=testNode->parentNode;
                struct PatriciaTrieNode* newNode=initPatriciaNode(3,port);
                //            *testNode->childNodes=newNode;
                newNode->parentNode=testNode;
                testNode->childnodenum+=1;
                bitmap_setTo1(remaining[0], testNode->bitmap);
                newNode->key=remaining;
                int x=bitmap_frontcount(remaining[0], testNode->bitmap);
                int childnum;
                for(childnum=testNode->childnodenum-1;childnum>=x;childnum--)
                {
                    *(testNode->childNodes+childnum)=*(testNode->childNodes+childnum-1);
                }
                *(testNode->childNodes+x-1)=newNode;
                
                
            }
            else
            {
                char* newNodeKey1=strcutmid(remaining,0,i);
                char* oldNodeKey=strcutright(testNodeKey,i);
                char* newNodeKey2=strcutright(remaining, i);
                struct PatriciaTrieNode* newNode1=initPatriciaNode(2,0);
                struct PatriciaTrieNode* newNode2=initPatriciaNode(3,port);
                //*testNode->childNodes=newNode;
                testNode->key="";
                testNode->key=oldNodeKey;
                newNode1->childnodenum+=1;
                bitmap_setTo1(oldNodeKey[0], newNode1->bitmap);
                newNode1->key=newNodeKey1;
                *newNode1->childNodes=testNode;
                int index=bitmap_frontcount(newNodeKey1[0], testNode->parentNode->bitmap);
                *(testNode->parentNode->childNodes+index)=newNode1;
                newNode1->parentNode=testNode->parentNode;
                testNode->parentNode=newNode1;
                int x=bitmap_frontcount(newNodeKey2[0],newNode1->bitmap);
                int childnum;
                for(childnum=newNode1->childnodenum;childnum>0;childnum--)
                {
                    *(newNode1->childNodes+childnum)=*(newNode1->childNodes+childnum-1);
                }
                *(newNode1->childNodes+x)=newNode2;
                newNode1->childnodenum+=1;
                bitmap_setTo1(newNodeKey2[0], newNode1->bitmap);
                newNode2->parentNode=newNode1;
                newNode2->key=newNodeKey2;
            }
        }
    }
    return 1;
    
}

void getPort(struct PatriciaTrieNode* node)
{
    printf("%d\n",node->port);
}

int delete(char* string,struct PatriciaTrieNode* node)
{
    int sum=0;
    struct PatriciaTrieNode* testNode=search(string, node);
    struct PatriciaTrieNode* currnode=testNode;
    while(currnode->parentNode)
    {
        sum+=strlen(currnode->parentNode->key);
        currnode=currnode->parentNode;
    }
    char* remaining=strcutright(string,sum);
    char* testNodeKey=testNode->key;
    if(strcmp(remaining, testNodeKey)<0)
    {
        printf("No compatible things!\n");
        return 0;
    }
    else
    {
        if(strcmp(remaining,testNodeKey)>0)
        {
            char* test=strcutmid(remaining,0,(int)strlen(testNodeKey));
            if(strcmp(test,testNodeKey)!=0)
            {
                printf("No compatible things!\n");
                return 0;
            }
        }
    }
    int index;
    int i;
    while(testNode->parentNode)
    {
        if(testNode->node_flag==3)
        {
            if(testNode->childnodenum==0)
            {
                getPort(testNode);
                index=bitmap_frontcount(testNode->key[0], testNode->parentNode->bitmap);
                testNode=testNode->parentNode;
                if(testNode->childnodenum>1)
                {
                    *(testNode->childNodes+index)=NULL;
                    testNode->childnodenum-=1;
                    for(i=index;i<testNode->childnodenum;i++)
                        *(testNode->childNodes+i)=*(testNode->childNodes+i+1);
                        *(testNode->childNodes+i)=NULL;
                        }
                else
                {
                    *(testNode->childNodes)=NULL;
                    testNode->childnodenum-=1;
                }
            }
            else
            {
                testNode->node_flag=2;
                getPort(testNode);
                testNode=testNode->parentNode;
            }
        }
        else
        {
            testNode=testNode->parentNode;
        }
        
    }
    return 1;
    
    
}


int main()
{
    struct PatriciaTrieNode* root=initPatriciaNode(0,0);
    insert("www.nidec.com/",root,1);
    insert("www.chemicalsindiacompany.com/",root,2);
    insert("www.edive.cz/",root,3);
    insert("neil.blog.com/",root,4);
    insert("classiques/focillon_henri/",root,5);
    insert("classiques/Faure_Elie/histoire_art_antique/",root,6);
    delete("www.nidec.com/news", root);
    delete("www.chemicalsindiacompany.com/",root);
    delete("www.edive",root);
    
    
    return 0;
}
